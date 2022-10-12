#include "ncm_win_resultentering_stage.h"
#include "ui_ncm_win_resultentering_stage.h"

NCM_WIN_ResultEntering_Stage::NCM_WIN_ResultEntering_Stage(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_ResultEntering_Stage)
{
    ui->setupUi(this);

    Competition = comp;

    get_data();

    setWindowTitle("Result Entering Stage");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_ResultEntering_Stage::~NCM_WIN_ResultEntering_Stage()
{
    delete ui;
}

void NCM_WIN_ResultEntering_Stage::get_data()
{
    if(data_loaded)
        return;

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory",
                Competition.dir(COMP_DIR_COMPETITORS).path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    QDir DIR_Competitors(QS_CompetitorsLoadPath);
    if(!DIR_Competitors.exists())
        return;

    Competitors_All.set_dir(DIR_Competitors);

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select stage file",
                Competition.dir(COMP_DIR_STAGES).path(),
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    QFileInfo FI_StageFile(QS_StageLoadPath);
    if(!FI_StageFile.exists())
        return;

    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return;

    Stage.set_file(FI_StageFile);
    Stage.load();
    ui->comboBox_Checkpoint->addItems(Stage.checkpoints());

    //------------------------------- runs

    QDir DIR_Runs(Competition.dir(COMP_DIR_RUNS).path() + "/" + Stage.name());

    if(!DIR_Runs.exists())
        QDir().mkdir(DIR_Runs.path());
    if(!DIR_Runs.exists())
        return;

    Runs.set_dir(DIR_Runs);

    //------------------------------- load if everything is correct

    load_competitors();
    load_runs();
    calc_competitors_allowed();

    data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionData_Dialog->setEnabled(false);
}

void NCM_WIN_ResultEntering_Stage::load_competitors()
{
    Competitors_All.load();
}

void NCM_WIN_ResultEntering_Stage::load_runs()
{
    Runs.load();
}

void NCM_WIN_ResultEntering_Stage::calc_competitors_allowed()
{
    Competitors_Allowed = ui->checkBox_Rerun->isChecked() ? Competitors_All : Competitors_All.subtract(Runs.competitors_list());

    ui->comboBox_Competitor->clear();
    ui->comboBox_Competitor->addItems(Competitors_Allowed.names());
    ui->comboBox_Competitor->setCurrentIndex(0);

    ui->pushButton_SaveRun->setEnabled(Competitors_Allowed.size() > 0);
}

void NCM_WIN_ResultEntering_Stage::on_pushButton_SaveRun_clicked()
{
    NCM_OBJ_Run run(
                Stage,
                Competitors_Allowed.get_competitor(ui->comboBox_Competitor->currentIndex()),
                ui->comboBox_Checkpoint->currentIndex(),
                ui->spinBox_min->value(),
                int(ui->doubleSpinBox_s->value()),
                (ui->doubleSpinBox_s->value() - int(ui->doubleSpinBox_s->value())) * 1000);

    if(Runs.contains_runner_name(run.competitor().name()))
    {
        if(QMessageBox::question(
                    this,
                    "Replace Run?",
                    "The previously entered run of " + run.competitor().name() + " will be replaced with no backup."
                    "<br>Do you want to replace it?")
                == QMessageBox::Yes)
            Runs.replace_run(run);
    }
    else
    {
        Runs.add_run(run);
    }

    Runs.save();

    if(ui->checkBox_BestTrick->isChecked())
    {
        ofstream OF_BestTrick;
        OF_BestTrick.open(Competition.path_best_trick().toStdString());
        if(!OF_BestTrick.is_open())
            return;

        OF_BestTrick << run.competitor().name().toStdString();
        OF_BestTrick.close();
    }

    if(ui->checkBox_WorstFail->isChecked())
    {
        ofstream OF_WorstFail;
        OF_WorstFail.open(Competition.path_worst_fail().toStdString());
        if(!OF_WorstFail.is_open())
            return;

        OF_WorstFail << run.competitor().name().toStdString();
        OF_WorstFail.close();
    }

    ui->checkBox_BestTrick->setChecked(false);
    ui->checkBox_WorstFail->setChecked(false);
    ui->comboBox_Competitor->setCurrentIndex(0);
    ui->comboBox_Checkpoint->setCurrentIndex(0);
    ui->spinBox_min->setValue(0);
    ui->doubleSpinBox_s->setValue(0);

    calc_competitors_allowed();
}

void NCM_WIN_ResultEntering_Stage::on_actionData_Dialog_triggered()
{
    get_data();
}

void NCM_WIN_ResultEntering_Stage::on_checkBox_Rerun_clicked()
{
    calc_competitors_allowed();
}

void NCM_WIN_ResultEntering_Stage::on_actionreload_competitors_and_runs_triggered()
{
    load_competitors();
    load_runs();
    calc_competitors_allowed();
}

void NCM_WIN_ResultEntering_Stage::on_spinBox_decimals_valueChanged(int arg1)
{
    ui->doubleSpinBox_s->setDecimals(arg1);
}
