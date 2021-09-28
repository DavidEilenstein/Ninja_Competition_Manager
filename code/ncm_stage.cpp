#include "ncm_stage.h"
#include "ui_ncm_stage.h"

NCM_Stage::NCM_Stage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_Stage)
{
    ui->setupUi(this);
}

NCM_Stage::~NCM_Stage()
{
    delete ui;
}

void NCM_Stage::on_plainTextEdit_StageCode_textChanged()
{
    saved = false;
}
