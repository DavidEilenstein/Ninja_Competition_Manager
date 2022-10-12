#include "ncm_win_edit_challenge.h"
#include "ui_ncm_win_edit_challenge.h"

NCM_WIN_Edit_Challenge::NCM_WIN_Edit_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Edit_Challenge)
{
    ui->setupUi(this);

    Competition = comp;

    setWindowTitle("Edit Challenge");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_Edit_Challenge::~NCM_WIN_Edit_Challenge()
{
    delete ui;
}

void NCM_WIN_Edit_Challenge::on_pushButton_Load_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Load Challenge",
                Competition.dir(COMP_DIR_CHALLENGES).path());
    if(path.isEmpty())
        return;

    Challenge.set_file(QFileInfo(path));
    Challenge.load();

    ui->lineEdit_Name->setText(Challenge.name());
    ui->lineEdit_Unit->setText(Challenge.unit());
    ui->radioButton_Order_MoreIsBetter->setChecked(Challenge.order_more_is_better());
    ui->radioButton_Order_LessIsBetter->setChecked(!Challenge.order_more_is_better());
    ui->spinBox_Quali_F->setValue(Challenge.quali_count_f());
    ui->spinBox_Quali_M->setValue(Challenge.quali_count_m());
}

void NCM_WIN_Edit_Challenge::on_pushButton_Save_clicked()
{
    Challenge.set_name(ui->lineEdit_Name->text());
    Challenge.set_unit(ui->lineEdit_Unit->text());
    Challenge.set_order(ui->radioButton_Order_MoreIsBetter->isChecked());
    Challenge.set_quali_count(
                ui->spinBox_Quali_F->value(),
                ui->spinBox_Quali_M->value());

    QString path = QFileDialog::getSaveFileName(
                this,
                "Save Challenge",
                Competition.dir(COMP_DIR_CHALLENGES).path() + "/" + Challenge.name() + ".txt");
    if(path.isEmpty())
        return;

    Challenge.set_file(QFileInfo(path));
    Challenge.save();
}

