#include "ncm_win_main.h"
#include "ui_ncm_win_main.h"

NCM_WIN_Main::NCM_WIN_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NCM_WIN_Main)
{
    ui->setupUi(this);

    DIR_Settings.setPath(QDir().homePath() + "/Ninja_Competition_Manager");
    FI_Settings.setFile(DIR_Settings.path() + "/Settings.txt");
    settings_load();

    setWindowTitle("Ninja competition manager - by David Eilenstein (" + QS_VersionNumber + ")");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));
}

NCM_WIN_Main::~NCM_WIN_Main()
{
    delete ui;
}

void NCM_WIN_Main::settings_load()
{
    if(FI_Settings.exists())
    {
        ifstream IS_settings;
        IS_settings.open(FI_Settings.absoluteFilePath().toStdString());

        string ST_line;
        getline(IS_settings, ST_line);
        QString QS_Line = QString::fromStdString(ST_line);

        Competition.set_path_competition((QS_Line));
        ui->lineEdit_ComPath->setText(QS_Line);
    }

    settings_save();
}

void NCM_WIN_Main::settings_save()
{
    if(!DIR_Settings.exists())
        QDir().mkdir(DIR_Settings.path());

    ofstream OF_settings;
    OF_settings.open(FI_Settings.absoluteFilePath().toStdString());
    if(!OF_settings.is_open())
        return;

    OF_settings << Competition.dir_competition().path().toStdString() << "\n";
    OF_settings.close();
}

void NCM_WIN_Main::enable_ui()
{
    if(!Competition.is_valid())
    {
        QMessageBox::warning(
                    this,
                    "Competition invalid",
                    "Some directories are missing");
        return;
    }

    ui->groupBox_Checkin->setEnabled(true);
    ui->groupBox_Satges->setEnabled(true);
    //ui->groupBox_Challenges->setEnabled(true);
    ui->groupBox_Comp->setEnabled(false);

    settings_save();
}

void NCM_WIN_Main::on_pushButton_Comp_Select_clicked()
{
    QString path = QFileDialog::getExistingDirectory(
                this,
                "Create new competition",
                Competition.dir_competition().path());

    if(path.isEmpty())
        return;

    ui->lineEdit_ComPath->setText(path);
}

void NCM_WIN_Main::on_pushButton_Comp_Create_clicked()
{
    Competition.set_path_competition(ui->lineEdit_ComPath->text());
    Competition.create();

    enable_ui();
}

void NCM_WIN_Main::on_pushButton_Comp_Load_clicked()
{
    Competition.set_path_competition(ui->lineEdit_ComPath->text());
    Competition.load();

    enable_ui();
}

void NCM_WIN_Main::on_pushButton_Checkin_clicked()
{
    if(!Competition.is_valid())
        return;

    win_checkin = new NCM_WIN_CheckIn(Competition);
    this->close();
    win_checkin->show();
}

void NCM_WIN_Main::on_pushButton_Stage_Edit_clicked()
{
    if(!Competition.is_valid())
        return;

    win_edit_stage = new NCM_WIN_Edit_Stage(Competition);
    this->close();
    win_edit_stage->show();
}

void NCM_WIN_Main::on_pushButton_Stage_StarterList_clicked()
{
    if(!Competition.is_valid())
        return;

    win_starterlist = new NCM_WIN_StarterList(Competition);
    this->close();
    win_starterlist->show();
}

void NCM_WIN_Main::on_pushButton_Stage_ResultEntering_clicked()
{
    if(!Competition.is_valid())
        return;

    win_resultentering_stage = new NCM_WIN_ResultEntering_Stage(Competition);
    this->close();
    win_resultentering_stage->show();
}

void NCM_WIN_Main::on_pushButton_Stage_Ranking_clicked()
{
    if(!Competition.is_valid())
        return;

    win_ranking_stage = new NCM_WIN_Ranking_Stage(Competition);
    this->close();
    win_ranking_stage->show();
}

void NCM_WIN_Main::on_pushButton_Challenges_Edit_clicked()
{
    if(!Competition.is_valid())
        return;

    win_edit_challenge = new NCM_WIN_Edit_Challenge(Competition);
    this->close();
    win_edit_challenge->show();
}

void NCM_WIN_Main::on_pushButton_Challenges_ResultEntering_clicked()
{
    if(!Competition.is_valid())
        return;

    win_resultentering_challenge = new NCM_WIN_ResultEntering_Challenge(Competition);
    this->close();
    win_resultentering_challenge->show();
}

void NCM_WIN_Main::on_pushButton_Challenges_Ranking_clicked()
{
    if(!Competition.is_valid())
        return;

    win_ranking_challenge = new NCM_WIN_Ranking_Challenge(Competition);
    this->close();
    win_ranking_challenge->show();
}
