#include "ncm_ranking.h"
#include "ui_ncm_ranking.h"

NCM_Ranking::NCM_Ranking(QDir competition_dir, QStringList competitor_classes, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_Ranking)
{
    ui->setupUi(this);

    QSL_CompetitorClasses = competitor_classes;

    DIR_Competition = competition_dir;

    DIR_Competitors.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]);
    if(!DIR_Competitors.exists())
        QDir().mkdir(DIR_Competitors.path());

    DIR_SpecialPrices.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SPECIAL_PRICES]);
    if(!DIR_SpecialPrices.exists())
        QDir().mkdir(DIR_SpecialPrices.path());

    DIR_Screenshots.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SCREENSHOTS]);
    if(!DIR_Screenshots.exists())
        QDir().mkdir(DIR_Screenshots.path());

    FI_SickestMove.setFile(DIR_SpecialPrices.path() + "/" + QS_FileName_SpecialPrice_SickestMove);
    FI_FailOfTheDay.setFile(DIR_SpecialPrices.path() + "/" + QS_FileName_SpecialPrice_FailOfTheDay);

    init_tables();

    get_data_dialog();

    connect(&timer_autoupdate, SIGNAL(timeout()), this, SLOT(update_ranking()));

    setWindowTitle("Ranking - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));

    int size_button = 80;
    QSize RefIconSize(size_button, size_button);
    ui->pushButton_DavidEilenstein->setIcon(QIcon(":/logo/Logo_Final.jpg"));
    ui->pushButton_DavidEilenstein->setIconSize(RefIconSize);
}

NCM_Ranking::~NCM_Ranking()
{
    delete ui;
}

void NCM_Ranking::table_dims_dialog()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    bool ok;

    int n_tables = QInputDialog::getInt(
                this,
                "Table count",
                "How many ranking list tables do you want to have side by side in layout?",
                count_tables,
                1,
                99,
                1,
                &ok);
    if(!ok)
        return;

    int n_rows = QInputDialog::getInt(
                this,
                "Row count",
                "How many rows shall a table (exept the last one) have at maximum?",
                count_rows_per_table,
                1,
                99999,
                1,
                &ok);
    if(!ok)
        return;

    count_tables = n_tables;
    count_rows_per_table = n_rows;

    init_tables();
}

void NCM_Ranking::init_tables()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    //qDebug() << "start init_tables";

    //qDebug() << "stop timer_autoupdate";
    if(timer_autoupdate.isActive())
        timer_autoupdate.stop();

    //qDebug() << "clear vTables";
    for(size_t i = 0; i < vTables.size(); i++)
        delete vTables[i];
    vTables.clear();

    //qDebug() << "clear vTableWidget";
    for(size_t i = 0; i < vTableWidget.size(); i++)
        delete vTableWidget[i];
    vTableWidget.clear();

    //qDebug() << "clear horizontalLayout_StarterLists";
    if(ui->horizontalLayout_Rankings != NULL)
    {
        QLayoutItem* item;
        while((item = ui->horizontalLayout_Rankings->takeAt(0)) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }

    //qDebug() << "refill tables";
    vTables.resize(count_tables);
    vTableWidget.resize(count_tables);
    for(int i = 0; i < count_tables; i++)
    {
        vTableWidget[i] = new QTableWidget(this);
        ui->horizontalLayout_Rankings->layout()->addWidget(vTableWidget[i]);

        vTables[i] = new NCM_Table;
        vTables[i]->set_TW(vTableWidget[i]);
        vTables[i]->clear_data();

        QHeaderView *verticalHeader = vTableWidget[i]->verticalHeader();
        verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
        verticalHeader->setDefaultSectionSize(20);
    }


    //qDebug() << "finish init_tables";
}

void NCM_Ranking::get_data_dialog()
{
    if(state_data_loaded)
        return;

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory for this stage",
                DIR_Competitors.path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    DIR_CompetitorsThisStage.setPath(QS_CompetitorsLoadPath);
    if(!DIR_CompetitorsThisStage.exists())
        return;

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select stage file",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_STAGES],
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    FI_StageFile.setFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;
    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;
    QS_StageName = FI_StageFile.baseName();
    ui->label_StageName->setText(QS_StageName);

    //------------------------------- output

    DIR_Runs.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_RUNS] + "/" + QS_StageName);
    if(!DIR_Runs.exists())
        QDir().mkdir(DIR_Runs.path());

    DIR_CompetitorsNextStage.setPath(DIR_Competitors.path() + "/" + QS_StageName + "_Survivors");

    //------------------------------- load if everything is correct

    if(!load_stage())
        return;

    if(!update_ranking())
        return;

    state_data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionSelect_Data->setEnabled(false);
    ui->actionUpdate_now->setEnabled(true);
    ui->actionUpdate_automatically->setEnabled(true);
    ui->actionChange_table_layout->setEnabled(true);
    ui->actionExport_Competitor_List_from_current_ranking->setEnabled(true);

    auto_update(true);
}

bool NCM_Ranking::load_competitors()
{
    for(size_t i = 0; i < vCompetitorsAll.size(); i++)
        delete vCompetitorsAll[i];
    vCompetitorsAll.clear();

    DIR_CompetitorsThisStage.setPath(DIR_CompetitorsThisStage.path());

    QFileInfoList FIL_Competitors = DIR_CompetitorsThisStage.entryInfoList();
    for(int i = 0; i < FIL_Competitors.size(); i++)
    {
        //qDebug() << "try to load" << FIL_Competitors[i].absoluteFilePath();
        if(FIL_Competitors[i].exists())
            if(FIL_Competitors[i].suffix() == "txt" || FIL_Competitors[i].suffix() == "TXT")
                if(FIL_Competitors[i].baseName().startsWith("Competitor_"))
                {
                    NCM_Competitor *competitor = new NCM_Competitor(DIR_CompetitorsThisStage);
                    if(competitor->load(FIL_Competitors[i].absoluteFilePath()))
                        vCompetitorsAll.push_back(competitor);
                    else
                        delete competitor;
                }
    }

    //qDebug() << vCompetitorsAll.size() << "competitors found";
    return true;
}

bool NCM_Ranking::load_runs()
{
    for(size_t i = 0; i < vRunsCompleted.size(); i++)
        delete vRunsCompleted[i];
    vRunsCompleted.clear();

    DIR_Runs.setPath(DIR_Runs.path());

    QFileInfoList FIL_Runs = DIR_Runs.entryInfoList();
    for(int i = 0; i < FIL_Runs.size(); i++)
        if(FIL_Runs[i].exists())
            if(FIL_Runs[i].suffix() == "txt" || FIL_Runs[i].suffix() == "TXT")
                if(FIL_Runs[i].baseName().startsWith("Run_"))
                {
                    NCM_Run *run = new NCM_Run(DIR_Competition, QS_StageName);
                    if(run->load(FIL_Runs[i].absoluteFilePath()))
                        vRunsCompleted.push_back(run);
                    else
                        delete run;
                }

    //qDebug() << vRunsCompleted.size() << "runs loaded";
    return true;
}

bool NCM_Ranking::load_stage()
{
    if(state_data_loaded)
        return false;

    ifstream IS_StageCode;
    IS_StageCode.open(FI_StageFile.absoluteFilePath().toStdString());

    if(!IS_StageCode.is_open())
        return false;

    QSL_Stage_Code.clear();

    string ST_line;
    while(getline(IS_StageCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        QSL_Stage_Code.push_back(QS_Line);
    }

    IS_StageCode.close();

    if(!stage_code_parse())
        return false;

    return true;
}

bool NCM_Ranking::load_special_prices()
{
    if(FI_FailOfTheDay.exists())
    {
        ifstream IS_FailOFTheDay;
        IS_FailOFTheDay.open(FI_FailOfTheDay.absoluteFilePath().toStdString());

        if(!IS_FailOFTheDay.is_open())
            return false;

        string ST_line;
        getline(IS_FailOFTheDay, ST_line);
        QString QS_Line = QString::fromStdString(ST_line);
        ui->label_FailOfTheDay->setText(QS_Line);
        IS_FailOFTheDay.close();
    }

    if(FI_SickestMove.exists())
    {
        ifstream IS_SickestMove;
        IS_SickestMove.open(FI_SickestMove.absoluteFilePath().toStdString());

        if(!IS_SickestMove.is_open())
            return false;

        string ST_line;
        getline(IS_SickestMove, ST_line);
        QString QS_Line = QString::fromStdString(ST_line);
        ui->label_MostEpicMove->setText(QS_Line);
        IS_SickestMove.close();
    }

    return true;
}

bool NCM_Ranking::stage_code_parse()
{
    QSL_Checkpoints.clear();
    vQualiGuarantee_CompetitorClasses.clear();
    vQualiGuarantee_GuranteeCount.clear();
    //vQualiGuarantee_GuaranteeMode.clear();
    //QualiGuarantee_SpeedPreviousStage_Mode = QUALI_GUARANTEE_INCLUSIVE;
    QualiGuarantee_SpeedPreviousStage_Count = 0;
    quali_mode = QUALI_ALL;
    quali_number = 0;

    bool obstacle_section_started = false;
    for(int i = 0; i < QSL_Stage_Code.size(); i++)
    {
        QStringList QSL_Blocks = QSL_Stage_Code[i].split(QS_Separator);
        if(QSL_Blocks.size() > 0)
        {
            QString QS_1stBlock = QSL_Blocks.first();
            if(QS_1stBlock != QS_LineSpace && QS_1stBlock != "")
            {
                if(!obstacle_section_started)
                {
                    int keyword_index = -1;
                    for(int k = 0; k < QSL_Stage_Keywords.size() && keyword_index < 0; k++)
                        if(QS_1stBlock == QSL_Stage_Keywords[k])
                            keyword_index = k;

                    if(keyword_index >= 0) //valid keyword found
                    {
                        switch (keyword_index) {

                        case STAGE_KEYWORD_NAME:
                        {
                            if(QSL_Blocks.size() >= 2)
                                QS_StageName = QSL_Blocks[1];
                        }
                            break;

                        case STAGE_KEYWORD_QUALI:
                        {
                            if(QSL_Blocks.size() >= 2)
                            {
                                int quali_mode_index = -1;
                                for(int q = 0; q < QSL_Quali.size() && quali_mode_index < 0; q++)
                                    if(QSL_Blocks[1] == QSL_Quali[q])
                                        quali_mode_index = q;

                                if(quali_mode_index >= 0 && quali_mode_index < QUALI_NUMBER_OF)
                                {
                                    if(quali_mode_index == QUALI_NUMBER)
                                    {
                                        if(QSL_Blocks.size() >= 3)
                                        {
                                            bool ok;
                                            int number = QSL_Blocks[2].toInt(&ok);
                                            if(ok && number >= 0)
                                            {
                                                quali_mode = quali_mode_index;
                                                quali_number = number;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        quali_mode = quali_mode_index;
                                        quali_number = 0;
                                    }
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_QUALI_GUARANTEE_CLASS:
                        {
                            if(QSL_Blocks.size() == 3)
                            {
                                int class_index = -1;
                                for(int c = 0; c < QSL_CompetitorClasses.size() && class_index < 0; c++)
                                    if(QSL_Blocks[1] == QSL_CompetitorClasses[c])
                                        class_index = c;

                                bool duplicate_found = false;
                                for(size_t i = 0; i < vQualiGuarantee_CompetitorClasses.size(); i++)
                                    if(vQualiGuarantee_CompetitorClasses[i] == class_index)
                                        duplicate_found = true;

                                if(!duplicate_found)
                                {
                                    if(class_index >= 0 && class_index < QSL_CompetitorClasses.size())
                                    {
                                        bool ok;
                                        int number = QSL_Blocks[2].toInt(&ok);

                                        if(ok && number >= 0)
                                        {
                                            vQualiGuarantee_CompetitorClasses.push_back(class_index);
                                            vQualiGuarantee_GuranteeCount.push_back(number);
                                        }
                                    }
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_QUALI_GUARANTEE_SPEED:
                        {
                            if(QSL_Blocks.size() == 2)
                            {
                                bool ok;
                                int number = QSL_Blocks[1].toInt(&ok);

                                if(ok && number >= 0)
                                {
                                    QualiGuarantee_SpeedPreviousStage_Count = number;

                                    /*
                                    int inclusion_index = -1;
                                    for(int j = 0; j < QSL_QualiGuaranteeMode.size() && inclusion_index < 0; j++)
                                        if(QSL_Blocks[2] == QSL_QualiGuaranteeMode[j])
                                            inclusion_index = j;

                                    if(inclusion_index >= 0 && inclusion_index < QUALI_GUARANTEE_NUMBER_OF)
                                    {
                                        QualiGuarantee_SpeedPreviousStage_Mode = inclusion_index;
                                        QualiGuarantee_SpeedPreviousStage_Count = number;
                                    }
                                    */
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_OBSTACLES:
                        {
                            QSL_Checkpoints.clear();
                            obstacle_section_started = true;
                        }
                            break;

                        default:
                            break;
                        }
                    }
                }
                else
                {
                    QSL_Checkpoints.push_back(QS_1stBlock);
                }
            }
        }
    }

    return true;
}

bool NCM_Ranking::calc_checkpoint_stats()
{
    int n_runs = vRunsCompleted.size();
    int n_cp = QSL_Checkpoints.size();

    vFailsAtCheckpoint.clear();
    vFailsAtCheckpoint.resize(n_cp, 0);
    QSL_CheckpointsClearRate.clear();
    QSL_CheckpointsReachRate.clear();
    QSL_CheckpointsWithRates.clear();

    //count fails at checkpoints
    for(int r = 0; r < n_runs; r++)
    {
        QString QS_Reached = vRunsCompleted[r]->checkpoint_reached();
        bool checkpoint_identified = false;
        for(int cp = 0; cp < n_cp && !checkpoint_identified; cp++)
            if(QS_Reached == QSL_Checkpoints[cp])
            {
                checkpoint_identified = true;
                vFailsAtCheckpoint[cp]++;
            }
    }

    //calc clear and reach rates
    int fails_until_cp = 0;
    for(int cp = 0; cp < n_cp; cp++)
    {
        int fails_at_cp = vFailsAtCheckpoint[cp];
        int cp_reached = n_runs - fails_until_cp;

        if(n_runs > 0)
            QSL_CheckpointsReachRate.append(QString::number((100 * cp_reached) / n_runs) + "%");
        else
            QSL_CheckpointsReachRate.append("-%");

        if(cp == n_cp - 1)//Buzzer / last checkpoint
            QSL_CheckpointsClearRate.append(QS_Buzzer);
        else if(cp_reached > 0)//clear rate can be calced
            QSL_CheckpointsClearRate.append(QString::number(100 - (100 * fails_at_cp) / cp_reached) + "%");
        else//no one reached the checkpoint
            QSL_CheckpointsClearRate.append("-%");

        QSL_CheckpointsWithRates.append(QSL_Checkpoints[cp] + " - " + QSL_CheckpointsReachRate[cp] + "/" + QSL_CheckpointsClearRate[cp]);

        fails_until_cp += fails_at_cp;
    }

    return true;
}

bool NCM_Ranking::calc_competitors_not_run_yet()
{
    QSL_CompetitorsNotRunYet.clear();
    for(size_t c = 0; c < vCompetitorsAll.size(); c++)
    {
        QString QS_NameOfCompetitor = vCompetitorsAll[c]->name();

        bool allready_run = false;
        for(size_t r = 0; r < vRunsCompleted.size() && !allready_run; r++)
            if(QS_NameOfCompetitor == vRunsCompleted[r]->name())
                allready_run = true;

        if(!allready_run)
            QSL_CompetitorsNotRunYet.append(QS_NameOfCompetitor);
    }



    //qDebug() << QSL_CompetitorsNotRunYet.size() << "competitors not run yet";
    return true;
}

bool NCM_Ranking::calc_ranking()
{
    //base counts
    size_t n_all = vCompetitorsAll.size();
    size_t n_run = vRunsCompleted.size();

    //statistics needed to calc position
    size_t n_to_go = n_all - n_run;
    vector<int> vCompetitorCount_All_byCompClass(QSL_CompetitorClasses.size(), 0);
    vector<int> vCompetitorCount_Runs_byCompClass(QSL_CompetitorClasses.size(), 0);
    vector<int> vCompetitorCount_ToGo_byCompClass(QSL_CompetitorClasses.size(), 0);

    //loop all competitors
    for(size_t ca = 0; ca < vCompetitorsAll.size(); ca++)
    {
        int comp_class_index = -1;
        for(int cc = 0; cc < QSL_CompetitorClasses.size() && comp_class_index < 0; cc++)
            if(QSL_CompetitorClasses[cc] == vCompetitorsAll[ca]->competitor_class())
                comp_class_index = cc;

        if(comp_class_index >= 0)
            vCompetitorCount_All_byCompClass[comp_class_index]++;
    }

    //resize info containers
    vRankingOfRuns_All.resize(n_run);
    vRankingOfRuns_InClass.resize(n_run);
    vRankingOfRuns_WorstPossible_All.resize(n_run);
    vRankingOfRuns_WorstPossible_InClass.resize(n_run); //TO DO
    vBuzzer.resize(n_run);

    //loop runs and calc placement
    for(size_t run_calc = 0; run_calc < n_run; run_calc++)
    {
        int comp_class_index = -1;
        for(int cc = 0; cc < QSL_CompetitorClasses.size() && comp_class_index < 0; cc++)
            if(QSL_CompetitorClasses[cc] == vRunsCompleted[run_calc]->competitor_class())
                comp_class_index = cc;

        if(comp_class_index >= 0)
        {
            size_t runs_better_in_class = 0;
            size_t runs_better_all = 0;

            int checkpoint_reached_calc = -1;
            for(int c = 0; c < QSL_Checkpoints.size(); c++)
                if(QSL_Checkpoints[c] == vRunsCompleted[run_calc]->checkpoint_reached())
                    checkpoint_reached_calc = c;

            //buzzered?
            vBuzzer[run_calc] = (checkpoint_reached_calc == QSL_Checkpoints.size() - 1);

            for(size_t run_compare = 0; run_compare < n_run; run_compare++)
            {
                if(run_calc != run_compare)
                {
                    int checkpoint_reached_compare = -1;
                    for(int c = 0; c < QSL_Checkpoints.size(); c++)
                        if(QSL_Checkpoints[c] == vRunsCompleted[run_compare]->checkpoint_reached())
                            checkpoint_reached_compare = c;

                    if(checkpoint_reached_calc >= 0 && checkpoint_reached_compare >= 0)
                    {
                        bool same_class = (vRunsCompleted[run_calc]->competitor_class() == vRunsCompleted[run_compare]->competitor_class());

                        if(checkpoint_reached_compare < checkpoint_reached_calc)
                        {
                            //compared came not as far as calc
                        }
                        else if(checkpoint_reached_compare == checkpoint_reached_calc)
                        {
                            //compared came as far as calc
                            //--> time decides
                            if(vRunsCompleted[run_compare]->time_in_ms() < vRunsCompleted[run_calc]->time_in_ms())
                            {
                                //compared was faster than calc
                                runs_better_all++;
                                if(same_class)
                                    runs_better_in_class++;
                            }
                            else
                            {
                                //compared was slower than or equal to calc
                            }
                        }
                        else
                        {
                            //compared came farer as calc
                            runs_better_all++;
                            if(same_class)
                                runs_better_in_class++;
                        }
                    }
                }
            }

            vRankingOfRuns_All[run_calc] = runs_better_all + 1;
            vRankingOfRuns_InClass[run_calc] = runs_better_in_class + 1;
            vRankingOfRuns_WorstPossible_All[run_calc] = vRankingOfRuns_All[run_calc] + n_to_go;
            vRankingOfRuns_WorstPossible_InClass[run_calc] = vRankingOfRuns_InClass[run_calc] + vCompetitorCount_ToGo_byCompClass[comp_class_index];
        }
    }


    //loop runs
    for(size_t rc = 0; rc < vRunsCompleted.size(); rc++)
    {
        int comp_class_index = -1;
        for(int cc = 0; cc < QSL_CompetitorClasses.size() && comp_class_index < 0; cc++)
            if(QSL_CompetitorClasses[cc] == vRunsCompleted[rc]->competitor_class())
                comp_class_index = cc;

        if(comp_class_index >= 0)
            vCompetitorCount_Runs_byCompClass[comp_class_index]++;
    }

    //runs to go
    for(size_t cc = 0; cc < vCompetitorCount_Runs_byCompClass.size(); cc++)
        vCompetitorCount_ToGo_byCompClass[cc] = vCompetitorCount_All_byCompClass[cc] - vCompetitorCount_Runs_byCompClass[cc];

    //calc quali state
    vQualiStates.clear();
    vQualiStates.resize(n_run, QUALI_STATE_UNDEFINED);
    for(size_t r = 0; r < vRunsCompleted.size(); r++)
    {
        //name
        QString QS_CompetitorName = vRunsCompleted[r]->name();

        //get comp class
        int comp_class_index = -1;
        QString QS_CompClassName = "";
        for(int cc = 0; cc < QSL_CompetitorClasses.size() && comp_class_index < 0; cc++)
            if(QSL_CompetitorClasses[cc] == vRunsCompleted[r]->competitor_class())
            {
                comp_class_index = cc;
                QS_CompClassName = QSL_CompetitorClasses[cc];
            }

        //class determinded succesfully
        if(comp_class_index >= 0)
        {
            //------------------------------- safe quali by speed

            //rank in last stage (according to starting order)
            int placement_last_stage_all = -1;
            for(size_t ca = 0; ca < vCompetitorsAll.size() && placement_last_stage_all < 0; ca++)
                if(vCompetitorsAll[ca]->name() == QS_CompetitorName)
                    placement_last_stage_all = int(n_all) - int(ca);

            //speed rule applies?
            bool quali_speed_safe = (placement_last_stage_all <= QualiGuarantee_SpeedPreviousStage_Count);
            //qDebug() << QS_CompetitorName << QS_CompClassName << placement_last_stage_all << QualiGuarantee_SpeedPreviousStage_Count << quali_speed_safe;


            //------------------------------- buzzer

            bool buzzered = vBuzzer[r];

            //------------------------------- safe regular quali

            //placememnt overall
            int placement_all = vRankingOfRuns_All[r];

            //regular quali
            int regular_quali_spots_worse_than_current_placement = quali_number - placement_all;
            bool quali_regular_safe = regular_quali_spots_worse_than_current_placement >= int(n_to_go);
            bool quali_regular_current = placement_all <= quali_number;


            //------------------------------- quali by class

            //placement in class
            int placement_in_class = vRankingOfRuns_InClass[r];
            //int class_all = vCompetitorCount_All_byCompClass[comp_class_index];
            int class_to_go = vCompetitorCount_ToGo_byCompClass[comp_class_index];
            //int class_run = vCompetitorCount_Runs_byCompClass[comp_class_index];

            //check if there are guarantee rules for this class
            bool guaranatee_rule_by_class = false;
            int guaranteed_count = 0;
            //int guarantee_mode = 0;
            qDebug() << vQualiGuarantee_CompetitorClasses.size() << QS_CompClassName;
            for(size_t grc = 0; grc < vQualiGuarantee_CompetitorClasses.size(); grc++)
                if(QS_CompClassName == QSL_CompetitorClasses[vQualiGuarantee_CompetitorClasses[grc]])
                {
                    guaranatee_rule_by_class = true;
                    guaranteed_count = vQualiGuarantee_GuranteeCount[grc];
                    //guarantee_mode = vQualiGuarantee_GuaranteeMode[grc];
                }

            //class quali
            bool quali_class_safe = false;
            bool quali_class_current = false;
            qDebug() << "rule found class" << guaranatee_rule_by_class;
            if(guaranatee_rule_by_class)
            {
                int class_quali_spots_worse_than_current_placement = guaranteed_count - placement_in_class;
                quali_class_safe = class_quali_spots_worse_than_current_placement >= int(class_to_go);
                quali_class_current = placement_in_class <= guaranteed_count;
                qDebug() << QS_CompetitorName << QS_CompClassName << class_quali_spots_worse_than_current_placement << placement_in_class << guaranteed_count << class_to_go << quali_class_safe << quali_class_current;
            }


            //------------------------------- worst possible placement

            //int worst_possible_placement_all = vRankingOfRuns_WorstPossible_All[r];
            int worst_possible_placement_class = vRankingOfRuns_WorstPossible_InClass[r];


            //------------------------------- calc quali state

            switch (quali_mode)
            {

            case QUALI_ALL:
            {
                vQualiStates[r] = QUALI_STATE_SAFE_REGULAR;
            }
                break;

            case QUALI_NUMBER:
            {
                if(quali_speed_safe)            vQualiStates[r] = QUALI_STATE_SAFE_SPEED;
                else if (quali_regular_safe)    vQualiStates[r] = QUALI_STATE_SAFE_REGULAR;
                else if (quali_class_safe)      vQualiStates[r] = QUALI_STATE_SAFE_CLASS;
                else if (quali_regular_current) vQualiStates[r] = QUALI_STATE_CURRENT_REGULAR;
                else if (quali_class_current)   vQualiStates[r] = QUALI_STATE_CURRENT_CLASS;
                else                            vQualiStates[r] = QUALI_STATE_OUT;
            }
                break;

            case QUALI_BUZZER:
            {
                if(buzzered)    vQualiStates[r] = QUALI_STATE_SAFE_REGULAR;
                else            vQualiStates[r] = QUALI_STATE_OUT;
            }
                break;

            case QUALI_FINAL:
            {
                if(worst_possible_placement_class <= 1)         vQualiStates[r] = QUALI_STATE_END_1ST;
                else if(worst_possible_placement_class <= 2)    vQualiStates[r] = QUALI_STATE_END_2ND;
                else if(worst_possible_placement_class <= 3)    vQualiStates[r] = QUALI_STATE_END_3RD;
                else                                            vQualiStates[r] = QUALI_STATE_END;
            }
                break;

            default:
                vQualiStates[r] = QUALI_STATE_UNDEFINED;
                break;
            }
        }
    }

    return true;
}

bool NCM_Ranking::update_ranking()
{
    if(state_update_running)
        return false;

    state_update_running = true;
    state_data_loaded = false;

    if(!load_competitors())
    {
        state_update_running = false;
        return false;
    }

    if(!load_runs())
    {
        state_update_running = false;
        return false;
    }

    if(!calc_competitors_not_run_yet())
    {
        state_update_running = false;
        return false;
    }

    if(!calc_checkpoint_stats())
    {
        state_update_running = false;
        return false;
    }

    state_data_loaded = true;

    if(!calc_ranking())
    {
        state_update_running = false;
        return false;
    }

    if(!load_special_prices())
    {
        state_update_running = false;
        return false;
    }

    //update ranking
    if(ui->tabWidget_Ranking->currentIndex() == 0)
        update_ranking_table();
    else
        update_ranking_plot();

    state_update_running = false;
    return true;
}

bool NCM_Ranking::update_ranking_table()
{
    //row names
    //qDebug() << "row names";
    vector<QStringList> vQSL_Names_Rows(count_tables);
    for(size_t i = 0; i < vRunsCompleted.size(); i++)
    {
        size_t index_table = min(size_t(count_tables - 1), size_t(i / count_rows_per_table));
        vQSL_Names_Rows[index_table].append(QString::number(i + 1));
    }

    //resize data container
    //qDebug() << "resize data container";
    vector<vector<vector<QString>>> vvvQS_Data(count_tables);
    for(int t = 0; t < count_tables; t++)
    {
        vvvQS_Data[t].resize(QSL_Names_Columns.size());
        for(size_t c = 0; c < vvvQS_Data[t].size(); c++)
        {
            vvvQS_Data[t][c].resize(vQSL_Names_Rows[t].size(), "???");
        }
    }

    //loop runs
    //qDebug() << "loop competitors";
    for(size_t r = 0; r < vRunsCompleted.size(); r++)
    {
        qDebug() << "run" << r << vRunsCompleted[r]->name() << "-------------";

        //checkpoint reached
        int checkpoint_reached = -1;
        for(int c = 0; c < QSL_Checkpoints.size(); c++)
            if(QSL_Checkpoints[c] == vRunsCompleted[r]->checkpoint_reached())
                checkpoint_reached = c;

        //placment all
        int placement_real = vRankingOfRuns_All[r];
        int placement_duplicate_appearance = 0;
        for(size_t d = 0; d < r; d++)
            if(placement_real == vRankingOfRuns_All[d])
                placement_duplicate_appearance++;
        int placement_used_for_table = placement_real + placement_duplicate_appearance;
        //qDebug() << "placement" << placement_real << placement_used_for_table;

        //target table
        size_t index_table = min(size_t(count_tables - 1), size_t((placement_used_for_table - 1) / count_rows_per_table));
        //qDebug() << "table index" << index_table;

        //row index
        size_t row_index = placement_used_for_table - 1;
        for(size_t t = 0; t < index_table; t++)
            row_index -= vQSL_Names_Rows[t].size();
        //qDebug() << "row index" << row_index;

        //write to table data
        if(row_index < vvvQS_Data[index_table][0].size())
        {
            //time
            int time_ms = vRunsCompleted[r]->time_in_ms();
            int time_s = time_ms / 1000;
            int time_min = time_s / 60;
            int time_display_min = time_min;
            int time_display_sec = time_s % 60;
            int time_display_ms = time_ms % 1000;
            QString QS_time = QString::number(time_display_min) + ":";
            if(time_display_sec < 10)
                QS_time.append("0");
            QS_time.append(QString::number(time_display_sec) + ".");
            if(time_display_ms < 100)
                QS_time.append("0");
            if(time_display_ms < 10)
                QS_time.append("0");
            QS_time.append(QString::number(time_display_ms));

            //qDebug() << "write datat to table";
            vQSL_Names_Rows[index_table][row_index]                 = QString::number(placement_real);
            vvvQS_Data[index_table][COLUMN_NAME][row_index]         = vRunsCompleted[r]->name();
            vvvQS_Data[index_table][COLUMN_CLASS][row_index]        = vRunsCompleted[r]->competitor_class();
            vvvQS_Data[index_table][COLUMN_CHECKPOINT][row_index]   = QSL_Checkpoints[checkpoint_reached];
            vvvQS_Data[index_table][COLUMN_REACH][row_index]        = QSL_CheckpointsReachRate[checkpoint_reached];
            vvvQS_Data[index_table][COLUMN_CLEAR][row_index]        = QSL_CheckpointsClearRate[checkpoint_reached];
            vvvQS_Data[index_table][COLUMN_TIME][row_index]         = QS_time;
            vvvQS_Data[index_table][COLUMN_QUALI][row_index]        = QSL_QualiState[vQualiStates[r]];
            //vvvQS_Data[index_table][COLUMN_SAFE_CLASS][row_index]   = QString::number(vRankingOfRuns_WorstPossible_InClass[r]);
            //vvvQS_Data[index_table][COLUMN_SAFE_ALL][row_index]     = QString::number(vRankingOfRuns_WorstPossible_All[r]);
        }
    }

    //write data to table
    //qDebug() << "write data to table";
    for(int t = 0; t < count_tables; t++)
        vTables[t]->set_data(
                    vvvQS_Data[t],
                    QSL_Names_Columns,
                    vQSL_Names_Rows[t],
                    false,
                    true);

    return true;
}

bool NCM_Ranking::update_ranking_plot()
{
    return true;
}

void NCM_Ranking::on_actionSelect_Data_triggered()
{
    get_data_dialog();
}

void NCM_Ranking::on_actionUpdate_now_triggered()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    update_ranking();
}

void NCM_Ranking::auto_update(bool activate)
{
    if(activate)
    {
        bool ok;
        double time_s = QInputDialog::getDouble(
                    this,
                    "Autoupdate interval",
                    "Please select the interval for autoupdateing ranking in seconds.",
                    1,
                    0.1,
                    300,
                    2,
                    &ok);
        if(!ok)
            return;

        timer_autoupdate.start(int(time_s * 1000));
    }
    else
    {
        timer_autoupdate.stop();
    }

    ui->actionUpdate_now->setEnabled(!activate);
}

void NCM_Ranking::on_actionUpdate_automatically_triggered(bool checked)
{
    auto_update(checked);
}

void NCM_Ranking::on_actionChange_table_layout_triggered()
{
    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }

    table_dims_dialog();
    update_ranking();
}



void NCM_Ranking::on_actionExport_Competitor_List_from_current_ranking_triggered()
{
    if(!state_data_loaded)
        return;

    //wait for update to finish
    ui->actionUpdate_automatically->setChecked(false);
    while (state_update_running)
    {
        //just chill
    }


    //target dir
    QDir DIR_Target = DIR_CompetitorsNextStage;
    int number = 2;
    while(DIR_Target.exists())
    {
        DIR_Target.setPath(DIR_CompetitorsNextStage.path() + "_Save" + QString::number(number));
        number++;
    }
    QDir().mkdir(DIR_Target.path());
    if(DIR_Target.path() != DIR_CompetitorsNextStage.path())
        QMessageBox::information(
                    this,
                    "Save directory correction",
                    DIR_CompetitorsNextStage.path() + "\n\nThis directory allready exists.\nThe new competitor list is saved here instead:\n\n" + DIR_Target.path());

    //run count
    size_t n_runs = vRunsCompleted.size();

    //sort runs by placement (best to worst)
    vector<int> vRunIndices_SortedByPlacement(n_runs, 0);
    vector<int> vRunExported(n_runs, int(false));
    for(int place = 1; place <= int(n_runs); place++)
    {
        bool place_found = false;
        for(size_t run = 0; run < n_runs && !place_found; run++)
        {
            if(vRunExported[run] == int(false))
            {
                if(vRankingOfRuns_All[run] <= place)
                {
                    vRunIndices_SortedByPlacement[place - 1] = run;
                    place_found = true;
                    vRunExported[run] = int(true);
                }
            }
        }
    }

    //loop sorted runs, check quali state and export
    int starting_number_next_stage = 1;
    for(int r_by_place = n_runs - 1; r_by_place >= 0; r_by_place--)  //worst run to best run
    {
        qDebug() << "-------------------";
        qDebug() << r_by_place;
        size_t r = vRunIndices_SortedByPlacement[r_by_place];
        qDebug() << r;

        if(vQualiStates[r] == QUALI_STATE_SAFE_CLASS || vQualiStates[r] == QUALI_STATE_SAFE_SPEED || vQualiStates[r] == QUALI_STATE_SAFE_REGULAR || vQualiStates[r] == QUALI_STATE_CURRENT_CLASS || vQualiStates[r] == QUALI_STATE_CURRENT_REGULAR)
        {
            NCM_Competitor competitor(DIR_Target);
            competitor.set_name(vRunsCompleted[r]->name());
            competitor.set_competitor_class(vRunsCompleted[r]->competitor_class());
            competitor.set_starter_number(starting_number_next_stage);
            competitor.save();

            starting_number_next_stage++;
        }
    }

    QMessageBox::information(
                this,
                "Saved competitor list",
                "The competitor list for the next stage was saved succsessfully in:\n" + DIR_Target.path());
}

void NCM_Ranking::on_pushButton_DavidEilenstein_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.instagram.com/eilenstyle"));
}

void NCM_Ranking::on_actionSave_Screenshot_triggered()
{
    QString QS_SavePath = DIR_Screenshots.path() + "/" + QS_StageName + "_Ranking.png";
    ui->centralwidget->grab().save(QS_SavePath);
    QMessageBox::information(
                this,
                "Screenshot saved",
                "Screenshot of current ranking saved as:\n" + QS_SavePath);
}
