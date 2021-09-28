#include "ncm_competitorlist.h"
#include "ui_ncm_competitorlist.h"

NCM_CompetitorList::NCM_CompetitorList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_CompetitorList)
{
    ui->setupUi(this);
}

NCM_CompetitorList::~NCM_CompetitorList()
{
    delete ui;
}
