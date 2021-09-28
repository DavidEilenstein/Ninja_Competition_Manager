#include "ncm_competitorclass.h"
#include "ui_ncm_competitorclass.h"

NCM_CompetitorClass::NCM_CompetitorClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_CompetitorClass)
{
    ui->setupUi(this);
}

NCM_CompetitorClass::~NCM_CompetitorClass()
{
    delete ui;
}
