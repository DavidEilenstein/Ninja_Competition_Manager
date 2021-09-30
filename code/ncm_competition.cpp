#include "ncm_competition.h"
#include "ui_ncm_competition.h"

NCM_Competition::NCM_Competition(QDir *pMasterDir, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_Competition)
{
    ui->setupUi(this);

    pDIR_Master = pMasterDir;
    DIR_Competition.setPath(pDIR_Master->path() + "/Competition_Default");

    vDIR_CompetitionSubdirs.resize(COMP_DIR_NUMBER_OF);
    for(int i = 0; i < COMP_DIR_NUMBER_OF; i++)
        vDIR_CompetitionSubdirs[i].setPath(DIR_Competition.path() + QSL_CompDirs[i]);
}

NCM_Competition::NCM_Competition()
{

}





NCM_Competition::~NCM_Competition()
{
    delete ui;
}



void NCM_Competition::create_dialogue()
{
    this->exec();
}

bool NCM_Competition::load_dialogue()
{
    //----------------------------------------------------- load dir

    QString LoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select directory to load competition folder from",
                pDIR_Master->path() + "/Competition_CompName");

    if(LoadPath.isEmpty())
        return false;

    //----------------------------------------------------- dir pathes

    DIR_Competition.setPath(LoadPath);
    if(!DIR_Competition.exists())
    {
        QMessageBox::warning(
                    this,
                    "Competition does not exists",
                    "This competition does not exists!");
        return false;
    }
    qDebug() << DIR_Competition;

    vDIR_CompetitionSubdirs.resize(COMP_DIR_NUMBER_OF);
    for(int i = 0; i < COMP_DIR_NUMBER_OF; i++)
    {
        vDIR_CompetitionSubdirs[i].setPath(DIR_Competition.path() + "/" + QSL_CompDirs[i]);
        if(!vDIR_CompetitionSubdirs[i].exists())
            QDir().mkdir(vDIR_CompetitionSubdirs[i].path());
    }

    //----------------------------------------------------- load competitor classes

    ifstream IS_competitor_classes;
    IS_competitor_classes.open(QString(vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_CompetitorClasses).toStdString());
    if(!IS_competitor_classes.is_open())
    {
        QMessageBox::warning(
                    this,
                    "File missing",
                    "File\n" + vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_CompetitorClasses + "\nis missing.");
        return false;
    }

    string ST_line;
    QSL_CompetitorClasses.clear();
    while(getline(IS_competitor_classes, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        if(!QS_Line.isEmpty())
            QSL_CompetitorClasses.append(QS_Line);
    }
    IS_competitor_classes.close();
    qDebug() << QSL_CompetitorClasses;

    //----------------------------------------------------- load competitor classes

    ifstream IS_StagesCount;
    IS_StagesCount.open(QString(vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_StagesCount).toStdString());
    if(!IS_StagesCount.is_open())
    {
        QMessageBox::warning(
                    this,
                    "File missing",
                    "File\n" + vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_StagesCount + "\nis missing.");
        return false;
    }

    while(getline(IS_StagesCount, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        if(!QS_Line.isEmpty())
        {
            bool ok;
            int count = QS_Line.toInt(&ok);
            if(ok)
                stages_count = count;
        }
    }
    IS_StagesCount.close();
    qDebug() << stages_count;

    //----------------------------------------------------- finish stuff

    pDIR_Master->setPath(DIR_Competition.path());
    pDIR_Master->cdUp();

    valid = true;
    return true;
}

void NCM_Competition::on_pushButton_Create_clicked()
{
    valid = true;
    save();
    this->close();
}

void NCM_Competition::on_pushButton_Cancel_clicked()
{
    this->close();
}

bool NCM_Competition::save()
{
    if(!valid)
        return false;

    QString SavePath = QFileDialog::getExistingDirectory(
                this,
                "Select directory to save competition folder in",
                pDIR_Master->path());

    if(SavePath.isEmpty())
        return false;

    //----------------------------------------------------- dir pathes

    DIR_Competition.setPath(SavePath + "/" + QS_CompetitionName);
    if(DIR_Competition.exists())
    {
        QMessageBox::warning(
                    this,
                    "Competition allready exists",
                    "This competition allready exists!\nIf you want to work with an existing one, please select 'load competition' in main window instead.");
        return false;
    }

    if(!DIR_Competition.exists())
        QDir().mkdir(DIR_Competition.path());

    vDIR_CompetitionSubdirs.resize(COMP_DIR_NUMBER_OF);
    for(int i = 0; i < COMP_DIR_NUMBER_OF; i++)
    {
        vDIR_CompetitionSubdirs[i].setPath(DIR_Competition.path() + "/" + QSL_CompDirs[i]);
        if(!vDIR_CompetitionSubdirs[i].exists())
            QDir().mkdir(vDIR_CompetitionSubdirs[i].path());
    }

    //----------------------------------------------------- competitor classes

    ofstream OF_competitorclasses;
    OF_competitorclasses.open(QString(vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_CompetitorClasses).toStdString());
    if(!OF_competitorclasses.is_open())
    {
        QMessageBox::warning(
                    this,
                    "Save Error",
                    "Can't save file: " + QS_FileName_CompetitorClasses);
        return false;
    }
    for(int i = 0; i < QSL_CompetitorClasses.size(); i++)
        OF_competitorclasses << QSL_CompetitorClasses[i].toStdString() << "\n";
    OF_competitorclasses.close();

    //----------------------------------------------------- stages count

    ofstream OF_stages_count;
    OF_stages_count.open(QString(vDIR_CompetitionSubdirs[COMP_DIR_GENERAL].path() + "/" + QS_FileName_StagesCount).toStdString());
    if(!OF_stages_count.is_open())
    {
        QMessageBox::warning(
                    this,
                    "Save Error",
                    "Can't save file: " + QS_FileName_StagesCount);
        return false;
    }
    OF_stages_count << stages_count << "\n";
    OF_stages_count.close();

    //----------------------------------------------------- finish stuff

    pDIR_Master->setPath(DIR_Competition.path());
    pDIR_Master->cdUp();

    return true;
}

void NCM_Competition::on_lineEdit_CompetitionName_textChanged(const QString &arg1)
{
    QS_CompetitionName = arg1;
}

void NCM_Competition::on_spinBox_StageCount_valueChanged(int arg1)
{
    stages_count = arg1;
}

void NCM_Competition::on_plainTextEdit_CompetitorCalsses_textChanged()
{
    QStringList QSL_Lines = ui->plainTextEdit_CompetitorCalsses->toPlainText().split("\n");
    QSL_CompetitorClasses.clear();
    for(int i = 0; i < QSL_Lines.size(); i++)
        if(!QSL_Lines[i].isEmpty())
            QSL_CompetitorClasses.append(QSL_Lines[i]);
}

