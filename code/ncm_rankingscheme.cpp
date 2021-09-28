#include "ncm_rankingscheme.h"
#include "ui_ncm_rankingscheme.h"

NCM_RankingScheme::NCM_RankingScheme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_RankingScheme)
{
    ui->setupUi(this);
}

NCM_RankingScheme::~NCM_RankingScheme()
{
    delete ui;
}
