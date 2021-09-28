#include "ncm_run.h"
#include "ui_ncm_run.h"

NCM_Run::NCM_Run(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_Run)
{
    ui->setupUi(this);
}

NCM_Run::~NCM_Run()
{
    delete ui;
}
