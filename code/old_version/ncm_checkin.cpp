#include "ncm_checkin.h"
#include "ui_ncm_checkin.h"

NCM_CheckIn::NCM_CheckIn(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_CheckIn)
{
    ui->setupUi(this);

    QSL_CompetitorClasses = competitor_classes;
    DIR_Competition = CompetitionDir;

    DIR_Competitors.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]);
    if(!DIR_Competitors.exists())
        QDir().mkdir(DIR_Competitors.path());

    DIR_Competitors_CheckedIn.setPath(DIR_Competitors.path() + "/CheckedIn");
    if(!DIR_Competitors_CheckedIn.exists())
        QDir().mkdir(DIR_Competitors_CheckedIn.path());

    QStringList QSL_CompClasses_PlusUndefined = QSL_CompetitorClasses;
    QSL_CompClasses_PlusUndefined.append("[please select competitor class]");
    ui->comboBox_CompClass->addItems(QSL_CompClasses_PlusUndefined);
    ui->comboBox_CompClass->setCurrentIndex(QSL_CompetitorClasses.size());

    load();

    setWindowTitle("Competitor checkin - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));
}

NCM_CheckIn::~NCM_CheckIn()
{
    save();
    delete ui;
}

void NCM_CheckIn::load()
{
    vCompetitors.clear();
    QFileInfoList FIL_Competitors = DIR_Competitors_CheckedIn.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Filter::NoSymLinks);
    for(int i = 0; i < FIL_Competitors.size(); i++)
        if(FIL_Competitors[i].exists())
            if(FIL_Competitors[i].suffix() == "txt" || FIL_Competitors[i].suffix() == "TXT")
                if(FIL_Competitors[i].baseName().startsWith("Competitor_"))
                {
                    NCM_Competitor *competitor = new NCM_Competitor(DIR_Competitors_CheckedIn);
                    if(competitor->load(FIL_Competitors[i].absoluteFilePath()))
                        vCompetitors.push_back(competitor);
                    else
                        delete competitor;
                }
}

void NCM_CheckIn::save()
{
    for(size_t i = 0; i < vCompetitors.size(); i++)
        vCompetitors[i]->save();
}

void NCM_CheckIn::on_pushButton_CheckIn_clicked()
{
    NCM_Competitor *competitor = new NCM_Competitor(
                DIR_Competitors_CheckedIn,
                ui->lineEdit_Name->text(),
                ui->comboBox_CompClass->currentText(),
                ui->spinBox_StartNumber->value());

    if(competitor->name().isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "Nameless competitor",
                    "Unless the competitor is not voldemort, you should enter a name please");
        delete competitor;
        return;
    }

    bool duplicate_number = false;
    for(size_t i = 0; i < vCompetitors.size(); i++)
        if(vCompetitors[i]->number() == competitor->number())
            duplicate_number = true;

    if(duplicate_number)
    {
        QMessageBox::warning(
                    this,
                    "Starter number duplicate",
                    "Starter number is allready taken. Please enter another number.");
        delete competitor;
        return;
    }

    if(competitor->number() <= 0)
    {
        QMessageBox::warning(
                    this,
                    "Invalid starter number",
                    "Please chose a starter number above 0.");
        delete competitor;
        return;
    }

    bool duplicate_name = false;
    for(size_t i = 0; i < vCompetitors.size(); i++)
        if(vCompetitors[i]->name() == competitor->name())
            duplicate_name = true;

    if(duplicate_name)
    {
        QMessageBox::warning(
                    this,
                    "Starter name duplicate",
                    "Starter name is allready taken. Please enter another name or add something to it.");
        delete competitor;
        return;
    }

    bool competitor_class_valid = false;
    for(int i = 0; i < QSL_CompetitorClasses.size(); i++)
        if(QSL_CompetitorClasses[i] == competitor->competitor_class())
            competitor_class_valid = true;

    if(!competitor_class_valid)
    {
        QMessageBox::warning(
                    this,
                    "Competitor class invalid",
                    "Competitor class is invalid. Please check, if the selected class is in the list of allowed classes in the competition");
        delete competitor;
        return;
    }

    vCompetitors.push_back(competitor);
    competitor->save();

    ui->spinBox_StartNumber->setValue(0);
    ui->lineEdit_Name->setText("");
    ui->comboBox_CompClass->setCurrentIndex(QSL_CompetitorClasses.size());
}
