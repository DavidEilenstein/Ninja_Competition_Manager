#include "ncm_win_ranking_challenge.h"
#include "ui_ncm_win_ranking_challenge.h"

NCM_WIN_Ranking_Challenge::NCM_WIN_Ranking_Challenge(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Ranking_Challenge)
{
    ui->setupUi(this);
}

NCM_WIN_Ranking_Challenge::~NCM_WIN_Ranking_Challenge()
{
    delete ui;
}
