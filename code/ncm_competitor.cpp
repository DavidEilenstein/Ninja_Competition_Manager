#include "ncm_competitor.h"
#include "ui_ncm_competitor.h"

NCM_Competitor::NCM_Competitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_Competitor)
{
    ui->setupUi(this);
}

NCM_Competitor::~NCM_Competitor()
{
    delete ui;
}
