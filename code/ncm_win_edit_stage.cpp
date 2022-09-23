#include "ncm_win_edit_stage.h"
#include "ui_ncm_win_edit_stage.h"

NCM_WIN_Edit_Stage::NCM_WIN_Edit_Stage(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Edit_Stage)
{
    ui->setupUi(this);

    Competition = comp;

    setWindowTitle("Edit Stage - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_Edit_Stage::~NCM_WIN_Edit_Stage()
{
    delete ui;
}

void NCM_WIN_Edit_Stage::on_pushButton_Load_clicked()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                "Load Stage",
                Competition.dir(COMP_DIR_STAGES).path());
    if(path.isEmpty())
        return;

    Stage.set_file(QFileInfo(path));
    Stage.load();

    ui->lineEdit_Name->setText(Stage.name());
    ui->checkBox_isFinal->setChecked(Stage.is_final());
    ui->plainTextEdit_Checkpoints->setPlainText(Stage.checkpoints_as_string_line_by_line());
    ui->plainTextEdit_Challenges->setPlainText(Stage.challenge_names_as_string_line_by_line());
    ui->spinBox_Quali_This_F->setValue(Stage.quali_count_this_f());
    ui->spinBox_Quali_This_M->setValue(Stage.quali_count_this_m());
    ui->spinBox_Quali_Previous_F->setValue(Stage.quali_count_previous_f());
    ui->spinBox_Quali_Previous_M->setValue(Stage.quali_count_previous_m());
}

void NCM_WIN_Edit_Stage::on_pushButton_Save_clicked()
{
    Stage.set_name(ui->lineEdit_Name->text());
    Stage.set_final(ui->checkBox_isFinal->isChecked());
    Stage.set_challenges(ui->plainTextEdit_Challenges->toPlainText().split("\n"));
    Stage.set_checkpoints(ui->plainTextEdit_Checkpoints->toPlainText().split("\n"));
    Stage.set_quali_counts(
                ui->spinBox_Quali_This_F->value(),
                ui->spinBox_Quali_This_M->value(),
                ui->spinBox_Quali_Previous_F->value(),
                ui->spinBox_Quali_Previous_M->value());

    QString path = QFileDialog::getSaveFileName(
                this,
                "Save Stage",
                Competition.dir(COMP_DIR_STAGES).path() + "/" + Stage.name() + ".txt");
    if(path.isEmpty())
        return;

    Stage.set_file(QFileInfo(path));
    Stage.save();
}
