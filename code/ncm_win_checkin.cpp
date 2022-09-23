#include "ncm_win_checkin.h"
#include "ui_ncm_win_checkin.h"

NCM_WIN_CheckIn::NCM_WIN_CheckIn(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_CheckIn)
{
    ui->setupUi(this);

    CompetitorList.set_dir(QDir(comp.dir(COMP_DIR_COMPETITORS).path() + "/CheckedIn"));

    setWindowTitle("Checkin - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_CheckIn::~NCM_WIN_CheckIn()
{
    delete ui;
}

void NCM_WIN_CheckIn::on_pushButton_Checkin_clicked()
{
    //load competitor list

    CompetitorList.load();

    //name

    QString name = ui->lineEdit_Name->text();

    QString name_alphanumeric;
    for(int i = 0; i < name.size(); i++)
    {
        QString letter = name.at(i);
        bool letter_ok = false;
        for(int a = 0; a < QSl_AllowedChars.size() && !letter_ok; a++)
        {
            if(letter == QSl_AllowedChars[a])
            {
                letter_ok = true;
                name_alphanumeric.append(letter);
            }
        }
    }

    if(name != name_alphanumeric)
    {
        if(QMessageBox::question(
                    this,
                    "Forbidden Characters Found",
                    "The name contained non alphanumeric letters and will be replaced like this:\n" +
                    name + " -> " + name_alphanumeric + "\n"
                    "Is this okay?")
                != QMessageBox::Yes)
            return;

        ui->lineEdit_Name->setText(name_alphanumeric);
    }

    if(name_alphanumeric.isEmpty())
    {
        QMessageBox::warning(
                    this,
                    "Nameless competitor",
                    "Unless the competitor is not Voldemort, you should enter a name please");
        return;
    }

    if(CompetitorList.contains_name(name_alphanumeric))
    {
        QMessageBox::warning(
                    this,
                    "Duplicate Name",
                    "'" + name_alphanumeric + "' is allready among the checked in competitors");
        return;
    }

    //number

    int number = ui->spinBox_Number->value();

    if(CompetitorList.contains_number(number))
    {
        QMessageBox::warning(
                    this,
                    "Duplicate Number",
                    "'" + QString::number(number) + "' is allready among the checked in competitors");
        return;
    }

    //class

    bool female = ui->radioButton_Class_F->isChecked();

    //new competitor

    NCM_OBJ_Competitor competitor(name_alphanumeric, female, number);

    if(!CompetitorList.add_competitor(competitor))
    {
        QMessageBox::warning(
                    this,
                    "Chekin Fail",
                    "Competitor checkin failed");
        return;
    }

    //save

    CompetitorList.save();

    //reset ui
    ui->lineEdit_Name->setText("");
    ui->radioButton_Class_M->setChecked(true);
    ui->radioButton_Class_F->setChecked(false);
    ui->spinBox_Number->setValue(0);
}
