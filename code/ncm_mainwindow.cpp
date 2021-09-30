#include "ncm_mainwindow.h"
#include "ui_ncm_mainwindow.h"

NCM_MainWindow::NCM_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NCM_MainWindow)
{
    ui->setupUi(this);

    DIR_Settings.setPath(QDir().homePath() + "/Ninja_Competition_Manager");
    DIR_Master.setPath(DIR_Settings.path());
    FI_Settings.setFile(DIR_Settings.path() + "/Settings.txt");
    settings_load();
}

NCM_MainWindow::~NCM_MainWindow()
{
    settings_save();
    delete competition;
    delete ui;
}

void NCM_MainWindow::settings_load()
{
    if(FI_Settings.exists())
    {
        ifstream IS_settings;
        IS_settings.open(FI_Settings.absoluteFilePath().toStdString());

        string ST_line;
        getline(IS_settings, ST_line);
        QString QS_Line = QString::fromStdString(ST_line);

        DIR_Master.setPath(QS_Line);
    }

    settings_save();
}

void NCM_MainWindow::settings_save()
{
    if(!DIR_Settings.exists())
        QDir().mkdir(DIR_Settings.path());

    ofstream OF_settings;
    OF_settings.open(FI_Settings.absoluteFilePath().toStdString());
    if(!OF_settings.is_open())
        return;

    OF_settings << DIR_Master.path().toStdString() << "\n";
    OF_settings.close();
}


void NCM_MainWindow::on_pushButton_CompetitionCreate_clicked()
{
    competition = new NCM_Competition(&DIR_Master);
    competition->create_dialogue();

    if(!competition->is_valid())
    {
        delete competition;
        return;
    }

    ui->lineEdit_CompetitionPath->setText(competition->dir_competition().path());
    ui->groupBox_Competition->setEnabled(false);
    ui->groupBox_Modules->setEnabled(true);

    settings_save();
}

void NCM_MainWindow::on_pushButton_CompetitionLoad_clicked()
{
    competition = new NCM_Competition(&DIR_Master);
    competition->load_dialogue();

    qDebug() << "comp valid?" << competition->is_valid();
    if(!competition->is_valid())
    {
        delete competition;
        return;
    }

    ui->lineEdit_CompetitionPath->setText(competition->dir_competition().path());
    ui->groupBox_Competition->setEnabled(false);
    ui->groupBox_Modules->setEnabled(true);

    settings_save();
}

void NCM_MainWindow::on_pushButton_EditStages_clicked()
{
    if(!competition->is_valid())
        return;

    NCM_Stage stage(competition->dir_competition(), competition->competitor_classes());
    this->close();
    stage.exec();
}

void NCM_MainWindow::on_pushButton_Checkin_clicked()
{
    if(!competition->is_valid())
        return;

    pCheckIn = new NCM_CheckIn(competition->dir_competition(), competition->competitor_classes());
    this->close();
    pCheckIn->show();
}

void NCM_MainWindow::on_pushButton_ResultsEntering_clicked()
{
    if(!competition->is_valid())
        return;

    pResultEntering = new NCM_ResultEntering(competition->dir_competition());
    this->close();
    pResultEntering->show();
}

void NCM_MainWindow::on_pushButton_StarterList_clicked()
{

}

void NCM_MainWindow::on_pushButton_Ranking_clicked()
{

}
