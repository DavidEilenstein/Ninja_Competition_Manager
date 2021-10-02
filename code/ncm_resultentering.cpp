#include "ncm_resultentering.h"
#include "ui_ncm_resultentering.h"

NCM_ResultEntering::NCM_ResultEntering(QDir competition_dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_ResultEntering)
{
    ui->setupUi(this);

    DIR_Competition = competition_dir;

    DIR_Competitors.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]);
    if(!DIR_Competitors.exists())
        QDir().mkdir(DIR_Competitors.path());

    DIR_SpecialPrices.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SPECIAL_PRICES]);
    if(!DIR_SpecialPrices.exists())
        QDir().mkdir(DIR_SpecialPrices.path());

    FI_SickestMove.setFile(DIR_SpecialPrices.path() + "/" + QS_FileName_SpecialPrice_SickestMove);
    FI_FailOfTheDay.setFile(DIR_SpecialPrices.path() + "/" + QS_FileName_SpecialPrice_FailOfTheDay);

    get_data_dialog();

    setWindowTitle("Result entering - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));
}

NCM_ResultEntering::~NCM_ResultEntering()
{
    delete ui;
}

void NCM_ResultEntering::get_data_dialog()
{
    if(state_data_loaded)
        return;

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory",
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

    //------------------------------- output

    DIR_Runs_Out.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_RUNS] + "/" + QS_StageName);
    if(!DIR_Runs_Out.exists())
        QDir().mkdir(DIR_Runs_Out.path());

    //------------------------------- load if everything is correct

    if(!load_competitors())
        return;

    if(!load_runs())
        return;

    if(!load_checkpoints())
            return;

    if(!calc_competitors_not_run_yet())
        return;

    state_data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionStage_and_competitor_selection->setEnabled(false);
}

bool NCM_ResultEntering::load_competitors()
{
    if(state_data_loaded)
        return false;

    vCompetitorsAll.clear();
    QFileInfoList FIL_Competitors = DIR_CompetitorsThisStage.entryInfoList();
    for(int i = 0; i < FIL_Competitors.size(); i++)
    {
        qDebug() << "try to load" << FIL_Competitors[i].absoluteFilePath();
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

    qDebug() << vCompetitorsAll.size() << "competitors found";
    return true;
}

bool NCM_ResultEntering::load_runs()
{
    if(state_data_loaded)
        return false;

    vRunsCompleted.clear();
    QFileInfoList FIL_Runs = DIR_Runs_Out.entryInfoList();
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

    qDebug() << vRunsCompleted.size() << "runs loaded";
    return true;
}

bool NCM_ResultEntering::load_checkpoints()
{
    if(state_data_loaded)
        return false;

    ifstream IS_StageCode;
    IS_StageCode.open(FI_StageFile.absoluteFilePath().toStdString());

    if(!IS_StageCode.is_open())
        return false;

    QSL_Checkpoints.clear();

    string ST_line;
    bool obstacle_section_started = false;
    while(getline(IS_StageCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);

        if(obstacle_section_started)
        {
            if(!QS_Line.isEmpty())
                if(QS_Line != QS_LineSpace)
                    QSL_Checkpoints.push_back(QS_Line);
        }
        else
        {
            if(QS_Line == QSL_Stage_Keywords[STAGE_KEYWORD_OBSTACLES])
                obstacle_section_started = true;
        }
    }

    IS_StageCode.close();

    ui->comboBox_Checkpoint->addItems(QSL_Checkpoints);

    qDebug() << QSL_Checkpoints.size() << "checkpoints found";
    return true;
}

bool NCM_ResultEntering::calc_competitors_not_run_yet()
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

    ui->comboBox_Competitor->clear();
    ui->comboBox_Competitor->addItems(QSL_CompetitorsNotRunYet);

    qDebug() << QSL_CompetitorsNotRunYet.size() << "competitors not run yet";
    return true;
}

void NCM_ResultEntering::on_actionStage_and_competitor_selection_triggered()
{
    get_data_dialog();
}

void NCM_ResultEntering::on_pushButton_SaveRun_clicked()
{
    NCM_Run *run = new NCM_Run(DIR_Competition, QS_StageName);

    QString QS_NameOfCompetitor = ui->comboBox_Competitor->currentText();
    bool competitor_found = false;
    for(size_t i = 0; i < vCompetitorsAll.size() && !competitor_found; i++)
        if(vCompetitorsAll[i]->name() == QS_NameOfCompetitor)
        {
            competitor_found = true;
            run->set_competitor(vCompetitorsAll[i]);
        }

    if(!competitor_found)
    {
        QMessageBox::warning(
                    this,
                    "Competitor unkown",
                    "The selected competitor '" + QS_NameOfCompetitor + "' was not found in the list of competitors!");
        delete run;
        return;
    }

    run->set_checkpoint_reached(ui->comboBox_Checkpoint->currentText());
    int time_ms = ((ui->doubleSpinBox_Minutes->value() * 60.0) + ui->doubleSpinBox_Seconds->value()) * 1000;
    run->set_time(time_ms);

    run->save();
    vRunsCompleted.push_back(run);

    calc_competitors_not_run_yet();

    if(ui->checkBox_SickestMove->isChecked())
    {
        ofstream OF_SickestMove;
        OF_SickestMove.open(FI_SickestMove.absoluteFilePath().toStdString());
        if(!OF_SickestMove.is_open())
            return;

        OF_SickestMove << run->name().toStdString();
        OF_SickestMove.close();
    }

    if(ui->checkBox_FailOfTheDay->isChecked())
    {
        ofstream OF_FailOfTheDay;
        OF_FailOfTheDay.open(FI_FailOfTheDay.absoluteFilePath().toStdString());
        if(!OF_FailOfTheDay.is_open())
            return;

        OF_FailOfTheDay << run->name().toStdString();
        OF_FailOfTheDay.close();
    }

    ui->checkBox_SickestMove->setChecked(false);
    ui->checkBox_FailOfTheDay->setChecked(false);
    ui->comboBox_Competitor->setCurrentIndex(0);
    ui->comboBox_Checkpoint->setCurrentIndex(0);
    ui->doubleSpinBox_Minutes->setValue(0);
    ui->doubleSpinBox_Seconds->setValue(0);
}
