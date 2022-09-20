#include "ncm_win_ranking_stage.h"
#include "ui_ncm_win_ranking_stage.h"

NCM_WIN_Ranking_Stage::NCM_WIN_Ranking_Stage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Ranking_Stage)
{
    ui->setupUi(this);
}

NCM_WIN_Ranking_Stage::~NCM_WIN_Ranking_Stage()
{
    delete ui;
}
