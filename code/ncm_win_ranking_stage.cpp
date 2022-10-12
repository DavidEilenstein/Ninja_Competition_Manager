#include "ncm_win_ranking_stage.h"
#include "ui_ncm_win_ranking_stage.h"

NCM_WIN_Ranking_Stage::NCM_WIN_Ranking_Stage(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Ranking_Stage)
{
    ui->setupUi(this);
    Table.set_layout(ui->gridLayout_Ranking);

    Competition = comp;
    get_data();

    connect(&TimerAutoupdate, SIGNAL(timeout()), this, SLOT(update()));
    TimerAutoupdate.start(1000);

    setWindowTitle("Ranking Stage");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));

    int size_button = 80;
    QSize RefIconSize(size_button, size_button);
    ui->pushButton_DE->setIcon(QIcon(":/img/Logo_Final.jpg"));
    ui->pushButton_DE->setIconSize(RefIconSize);
}

NCM_WIN_Ranking_Stage::~NCM_WIN_Ranking_Stage()
{
    delete ui;
}

void NCM_WIN_Ranking_Stage::get_data()
{
    if(data_loaded)
        return;

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Stage this   XXXXXXXXXXXXXXXXXXXXXX

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "This Stage - Select competitors directory",
                Competition.dir(COMP_DIR_COMPETITORS).path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    QDir DIR_Competitors_StageThis(QS_CompetitorsLoadPath);
    if(!DIR_Competitors_StageThis.exists())
        return;

    Ranking.set_stage_this_competitors(DIR_Competitors_StageThis);

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "This Stage - Select stage file",
                Competition.dir(COMP_DIR_STAGES).path(),
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    QFileInfo FI_StageFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;

    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;

    Ranking.set_stage_this(FI_StageFile);

    ui->label_Name->setText(Ranking.ranking_this().stage().name());

    //------------------------------- runs

    QDir DIR_Runs(Competition.dir(COMP_DIR_RUNS).path() + "/" + Ranking.ranking_this().stage().name());

    if(!DIR_Runs.exists())
        QDir().mkdir(DIR_Runs.path());
    if(!DIR_Runs.exists())
        return;

    Ranking.set_stage_this_runs(DIR_Runs);

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Stage previous   XXXXXXXXXXXXXXXXXXXXXX

    if(Ranking.ranking_this().stage().quali_count_previous_f() > 0 || Ranking.ranking_this().stage().quali_count_previous_m() > 0)
    {
        //------------------------------- competitors

        QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                    this,
                    "Previous Stage - Select competitors directory",
                    Competition.dir(COMP_DIR_COMPETITORS).path());

        if(QS_CompetitorsLoadPath.isEmpty())
            return;

        QDir DIR_Competitors_StagePrevious(QS_CompetitorsLoadPath);
        if(!DIR_Competitors_StagePrevious.exists())
            return;

        Ranking.set_stage_previous_competitors(DIR_Competitors_StagePrevious);

        //------------------------------- stage

        QS_StageLoadPath = QFileDialog::getOpenFileName(
                    this,
                    "Previous Stage - Select stage file",
                    Competition.dir(COMP_DIR_STAGES).path(),
                    tr("*.txt *.TXT"));

        if(QS_StageLoadPath.isEmpty())
            return;

        FI_StageFile.setFile(QS_StageLoadPath);
        if(!FI_StageFile.exists())
            return;

        if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
            return;

        Ranking.set_stage_previous(FI_StageFile);

        //------------------------------- runs

        DIR_Runs.setPath(Competition.dir(COMP_DIR_RUNS).path() + "/" + Ranking.ranking_previous().stage().name());

        if(!DIR_Runs.exists())
            QDir().mkdir(DIR_Runs.path());
        if(!DIR_Runs.exists())
            return;

        Ranking.set_stage_previous_runs(DIR_Runs);
    }

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   Challenges   XXXXXXXXXXXXXXXXXXXXXX

    Ranking.set_challenges_tries(Competition.dir(COMP_DIR_CHALLENGE_TRIES));
    Ranking.set_challenges_challenges(Competition.dir(COMP_DIR_CHALLENGES));
    Ranking.set_challenges_competitors(DIR_Competitors_StageThis);
    Ranking.set_challenges_names();

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   UI   XXXXXXXXXXXXXXXXXXXXXX

    Ranking.load_challenges();
    NCM_OBJ_Stage stage = Ranking.ranking_this().stage();
    ui->label_QualiChallenge_F->setText(QString::number(Ranking.rankings_challenges().quali_count_f()));
    ui->label_QualiChallenge_M->setText(QString::number(Ranking.rankings_challenges().quali_count_m()));
    ui->label_QualiSafe_F->setText(QString::number(stage.quali_count_this_f()));
    ui->label_QualiSafe_M->setText(QString::number(stage.quali_count_this_m()));
    ui->label_QualiSpeed_F->setText(QString::number(stage.quali_count_previous_f()));
    ui->label_QualiSpeed_M->setText(QString::number(stage.quali_count_previous_m()));

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionget_data->setEnabled(false);
}

void NCM_WIN_Ranking_Stage::table_dims_dialog()
{
    //wait for update to finish
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    bool ok;

    int n_tables = QInputDialog::getInt(
                this,
                "Table count",
                "How many ranking tables do you want to have side by side in layout?",
                Table.count_tables(),
                1,
                10,
                1,
                &ok);
    if(!ok)
        return;

    int n_rows = QInputDialog::getInt(
                this,
                "Row count",
                "How many rows shall a table (exept the last one) have at maximum?",
                Table.count_rowsPerTable(),
                1,
                1000,
                1,
                &ok);
    if(!ok)
        return;

    Table.set_table_count(n_tables);
    Table.set_table_rows(n_rows);
}

void NCM_WIN_Ranking_Stage::update()
{
    if(!data_loaded)
        return;

    if(update_running)
        return;

    update_running = true;

    //update
    Ranking.update();

    //update time
    ui->label_Time->setText(QDateTime::currentDateTime().time().toString());

    //--------------------------------------------------------------------------------------- table

    //clear Podium
    ui->label_Podium_F1->setText("");
    ui->label_Podium_F2->setText("");
    ui->label_Podium_F3->setText("");
    ui->label_Podium_M1->setText("");
    ui->label_Podium_M2->setText("");
    ui->label_Podium_M3->setText("");

    //data
    size_t n_cols = COL_NUMBER_OF;
    size_t n_rows = Ranking.ranking_this().runs().size();
    vector<vector<QString>> vvQS_TableContent_c_r(n_cols, vector<QString>(n_rows, "..."));

    //row names
    QStringList QSL_NamesRows;

    //checkpoint names
    QStringList QSL_Checkpoints = Ranking.ranking_this().stage().checkpoints();
    size_t n_cp = QSL_Checkpoints.size();
    if(n_cp > 0)
        QSL_Checkpoints[int(n_cp - 1)] = QS_Buzzer;

    //checkpoint stats
    vector<vector<size_t>> vvCheckpointFailHist(2, vector<size_t>(n_cp, 0));

    //loop runs
    for(size_t r = 0; r < n_rows; r++)
    {
        //run/competitor
        NCM_OBJ_Run run = Ranking.ranking_this().runs().get_run(r);
        NCM_OBJ_Competitor competitor = run.competitor();

        //row name
        QSL_NamesRows.append(QString::number(Ranking.ranking_this().pos_current_overall(competitor)));

        //competitor info
        vvQS_TableContent_c_r[COL_NAME][r]      = competitor.name();

        //run data
        size_t checkpoint                       = run.checkpoint_reached();
        vvCheckpointFailHist[competitor.female()][checkpoint]++;
        vvQS_TableContent_c_r[COL_POINT][r]     = QSL_Checkpoints[int(checkpoint)];
        vvQS_TableContent_c_r[COL_TIME][r]      = run.time_ms_text();

        //position
        size_t pos_current    = Ranking.ranking_this().pos_current_class(competitor);
        size_t pos_worst      = Ranking.ranking_this().pos_worst_class(competitor);
        QString class_symbol = competitor.competitor_class_symbol();
        vvQS_TableContent_c_r[COL_POS][r] = class_symbol + " " + QString::number(pos_current) + ".";
        if(pos_current != pos_worst)
            vvQS_TableContent_c_r[COL_POS][r].append(" - " + QString::number(pos_worst) + ".");

        //Podium
        if(competitor.female())
        {
            if(pos_current == 1)
                ui->label_Podium_F1->setText(ui->label_Podium_F1->text().isEmpty() ? competitor.name() : ui->label_Podium_F1->text() + " & " + competitor.name());
            else if(pos_current == 2)
                ui->label_Podium_F2->setText(ui->label_Podium_F2->text().isEmpty() ? competitor.name() : ui->label_Podium_F2->text() + " & " + competitor.name());
            else if(pos_current == 3)
                ui->label_Podium_F3->setText(ui->label_Podium_F3->text().isEmpty() ? competitor.name() : ui->label_Podium_F3->text() + " & " + competitor.name());
        }
        else
        {
            if(pos_current == 1)
                ui->label_Podium_M1->setText(ui->label_Podium_M1->text().isEmpty() ? competitor.name() : ui->label_Podium_M1->text() + " & " + competitor.name());
            else if(pos_current == 2)
                ui->label_Podium_M2->setText(ui->label_Podium_M2->text().isEmpty() ? competitor.name() : ui->label_Podium_M2->text() + " & " + competitor.name());
            else if(pos_current == 3)
                ui->label_Podium_M3->setText(ui->label_Podium_M3->text().isEmpty() ? competitor.name() : ui->label_Podium_M3->text() + " & " + competitor.name());
        }

        //quali
        vvQS_TableContent_c_r[COL_QUALI][r] = QSL_QualiState[int(Ranking.quali_state(competitor))];
    }

    //checkpoint statistic

    //cumulate
    vector<vector<size_t>> vvCheckpointReachHistCum = vvCheckpointFailHist;
    for(size_t cla = 0; cla < 2; cla++)
        for(int cp = n_cp - 2; cp >= 0; cp--)
            vvCheckpointReachHistCum[cla][cp] += vvCheckpointReachHistCum[cla][cp + 1];

    //reach
    vector<vector<double>> vvCheckpointReach(2, vector<double>(n_cp, 0.0));
    for(size_t cla = 0; cla < 2; cla++)
        if(vvCheckpointReachHistCum[cla][0] > 0)
            for(size_t cp = 0; cp < n_cp; cp++)
                vvCheckpointReach[cla][cp] = double(vvCheckpointReachHistCum[cla][cp]) / double(vvCheckpointReachHistCum[cla][0]);

    //clear
    vector<vector<double>> vvCheckpointClear(2, vector<double>(n_cp, 1));
    for(size_t cla = 0; cla < 2; cla++)
        for(size_t cp = 0; cp < n_cp; cp++)
            if(vvCheckpointReachHistCum[cla][cp] > 0)
                vvCheckpointClear[cla][cp] = 1.0 - double(vvCheckpointFailHist[cla][cp]) / double(vvCheckpointReachHistCum[cla][cp]);

    //set stats to table
    for(size_t r = 0; r < n_rows; r++)
    {
        NCM_OBJ_Run run = Ranking.ranking_this().runs().get_run(r);
        bool female = run.competitor().female();
        size_t cp = run.checkpoint_reached();
        vvQS_TableContent_c_r[COL_CLEAR][r] = QString::number(int(vvCheckpointClear[female][cp] * 100)) + "%";
        vvQS_TableContent_c_r[COL_REACH][r] = QString::number(int(vvCheckpointReach[female][cp] * 100)) + "%";
    }

    //set table data
    Table.set_data(vvQS_TableContent_c_r, QSL_NamesColumns, QSL_NamesRows, false, true);

    //--------------------------------------------------------------------------------------- special prices

    QFileInfo FI_BestTrick(Competition.path_best_trick());
    if(FI_BestTrick.exists())
    {
        ifstream IS_BestTrick;
        IS_BestTrick.open(FI_BestTrick.absoluteFilePath().toStdString());

        if(IS_BestTrick.is_open())
        {
            string ST_line;
            getline(IS_BestTrick, ST_line);
            QString QS_Line = QString::fromStdString(ST_line);
            ui->label_BestTrick->setText(QS_Line);
            IS_BestTrick.close();
        }
    }

    QFileInfo FI_WorstFail(Competition.path_worst_fail());
    if(FI_WorstFail.exists())
    {
        ifstream IS_WorstFail;
        IS_WorstFail.open(FI_WorstFail.absoluteFilePath().toStdString());

        if(IS_WorstFail.is_open())
        {
            string ST_line;
            getline(IS_WorstFail, ST_line);
            QString QS_Line = QString::fromStdString(ST_line);
            ui->label_WorstFail->setText(QS_Line);
            IS_WorstFail.close();
        }
    }

    //take screenshot once per minute
    if(ui->actionAutosave_Screenshot_once_per_minute->isChecked())
        if(QDateTime::currentDateTime().time().second() <= 1)
            this->grab().save(Competition.dir(COMP_DIR_SCREENSHOTS).path() + "/Ranking - " + Ranking.ranking_this().stage().name() + ".png");

    update_running = false;
}

void NCM_WIN_Ranking_Stage::update_auto(bool activate)
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
        {
            ui->actionAutoupdate->setChecked(false);
            return;
        }

        TimerAutoupdate.start(int(time_s * 1000));
    }
    else
    {
        TimerAutoupdate.stop();
    }

    ui->actionUpdate->setEnabled(!activate);
}

void NCM_WIN_Ranking_Stage::on_actionget_data_triggered()
{
    get_data();
}

void NCM_WIN_Ranking_Stage::on_actionChange_Table_Settings_triggered()
{
    table_dims_dialog();
}

void NCM_WIN_Ranking_Stage::on_actionUpdate_triggered()
{
    ui->actionAutoupdate->setChecked(false);
    while (update_running)
    {
        //just chill
    }

    update();
}

void NCM_WIN_Ranking_Stage::on_actionAutoupdate_triggered(bool checked)
{
    update_auto(checked);
}

void NCM_WIN_Ranking_Stage::on_actionexport_starter_list_next_stage_triggered()
{
    //qualified competitors
    NCM_OBJ_Competitor_List competitors_qualified = Ranking.competitors_qualified();

    //new starter number
    size_t n_runs = Ranking.ranking_this().runs().size();
    for(size_t r = 0; r < n_runs; r++)
        competitors_qualified.change_starter_number(Ranking.ranking_this().run(r).competitor(), n_runs - r);

    //target dir
    QDir DIR_Target(Competition.dir(COMP_DIR_COMPETITORS).path() + "/CompetitorsPassed " + Ranking.ranking_this().stage().name());
    int number = 2;
    while(DIR_Target.exists())
    {
        DIR_Target.setPath(Competition.dir(COMP_DIR_COMPETITORS).path() + "/CompetitorsPassed " + Ranking.ranking_this().stage().name() + "_Save" + QString::number(number));
        number++;
    }
    QDir().mkdir(DIR_Target.path());
    if(number != 2)
        QMessageBox::information(
                    this,
                    "Save directory correction",
                    Competition.dir(COMP_DIR_COMPETITORS).path() + "/CompetitorsPassed " + Ranking.ranking_this().stage().name() + "\n\n" +
                    "This directory allready exists.\n"
                    "The new competitor list is saved here instead:\n\n" +
                    DIR_Target.path());

    //save
    competitors_qualified.save(DIR_Target);

    //finish
    QMessageBox::information(
                this,
                "Saved competitor list",
                "The competitor list for the next stage was saved succsessfully in:\n" + DIR_Target.path());
}
