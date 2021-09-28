#include "ncm_liveranking.h"
#include "ui_ncm_liveranking.h"

NCM_LiveRanking::NCM_LiveRanking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_LiveRanking)
{
    ui->setupUi(this);
}

NCM_LiveRanking::~NCM_LiveRanking()
{
    delete ui;
}
