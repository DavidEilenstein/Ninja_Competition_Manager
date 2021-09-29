#include "ncm_resultentering.h"
#include "ui_ncm_resultentering.h"

NCM_ResultEntering::NCM_ResultEntering(QDir competition_dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_ResultEntering)
{
    ui->setupUi(this);

    DIR_Competition = competition_dir;
}

NCM_ResultEntering::~NCM_ResultEntering()
{
    delete ui;
}

void NCM_ResultEntering::on_actionStage_and_competitor_selection_triggered()
{

}

void NCM_ResultEntering::on_pushButton_SaveRun_clicked()
{

}
