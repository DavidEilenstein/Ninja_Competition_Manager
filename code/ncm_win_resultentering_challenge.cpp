#include "ncm_win_resultentering_challenge.h"
#include "ui_ncm_win_resultentering_challenge.h"

NCM_WIN_ResultEntering_Challenge::NCM_WIN_ResultEntering_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_ResultEntering_Challenge)
{
    ui->setupUi(this);

    Competition = comp;

    get_data();

    setWindowTitle("Result Entering Challenge - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_ResultEntering_Challenge::~NCM_WIN_ResultEntering_Challenge()
{
    delete ui;
}

void NCM_WIN_ResultEntering_Challenge::get_data()
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

    //------------------------------- challenge

    QString QS_ChallengeLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select Challenge file",
                Competition.dir(COMP_DIR_CHALLENGES).path(),
                tr("*.txt *.TXT"));

    if(QS_ChallengeLoadPath.isEmpty())
        return;

    QFileInfo FI_ChallengeFile(QS_ChallengeLoadPath);
    if(!FI_ChallengeFile.exists())
        return;

    if(FI_ChallengeFile.suffix() != "txt" && FI_ChallengeFile.suffix() != "TXT")
        return;

    Challenge.set_file(FI_ChallengeFile);
    Challenge.load();
    ui->label_Name->setText(Challenge.name());
    ui->doubleSpinBox_Score->setSuffix(Challenge.unit());

    //------------------------------- tries

    QDir DIR_Tries(Competition.dir(COMP_DIR_CHALLENGE_TRIES).path() + "/" + Challenge.name());

    if(!DIR_Tries.exists())
        QDir().mkdir(DIR_Tries.path());
    if(!DIR_Tries.exists())
        return;

    Tries.set_dir(DIR_Tries);

    //------------------------------- load if everything is correct

    load_competitors();
    load_tries();
    calc_competitors_allowed();

    data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionData_Dialog->setEnabled(false);
}

void NCM_WIN_ResultEntering_Challenge::load_competitors()
{
    Competitors_All.load();
}

void NCM_WIN_ResultEntering_Challenge::load_tries()
{
    Tries.load();
}

void NCM_WIN_ResultEntering_Challenge::calc_competitors_allowed()
{
    Competitors_Allowed = ui->checkBox_AllowReTries->isChecked() ? Competitors_All : Competitors_All.subtract(Tries.competitors_list());

    ui->comboBox_Competitor->clear();
    ui->comboBox_Competitor->addItems(Competitors_Allowed.names());
    ui->comboBox_Competitor->setCurrentIndex(0);

    ui->pushButton_Save->setEnabled(Competitors_Allowed.size() > 0);
}

void NCM_WIN_ResultEntering_Challenge::on_pushButton_Save_clicked()
{
    NCM_OBJ_Try challengetry(
                Challenge,
                Competitors_Allowed.get_competitor(ui->comboBox_Competitor->currentIndex()),
                ui->doubleSpinBox_Score->value());

    if(Tries.contains_tryer_name(challengetry.competitor().name()))
    {
        if(QMessageBox::question(
                    this,
                    "Replace Try?",
                    "The previously entered try of " + challengetry.competitor().name() + " will be replaced with no backup."
                    "<br>Do you want to replace it?")
                == QMessageBox::Yes)
            Tries.replace_try(challengetry);
    }
    else
    {
        Tries.add_try(challengetry);
    }

    Tries.save();

    ui->comboBox_Competitor->setCurrentIndex(0);
    ui->doubleSpinBox_Score->setValue(0);

    calc_competitors_allowed();
}

void NCM_WIN_ResultEntering_Challenge::on_actionData_Dialog_triggered()
{
    get_data();
}

void NCM_WIN_ResultEntering_Challenge::on_actionReload_Competitors_and_Tries_triggered()
{
    load_competitors();
    load_tries();
    calc_competitors_allowed();
}

void NCM_WIN_ResultEntering_Challenge::on_checkBox_AllowReTries_clicked()
{
    calc_competitors_allowed();
}
