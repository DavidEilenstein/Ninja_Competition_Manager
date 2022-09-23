#include "ncm_win_ranking_challenge.h"
#include "ui_ncm_win_ranking_challenge.h"

NCM_WIN_Ranking_Challenge::NCM_WIN_Ranking_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Ranking_Challenge)
{
    ui->setupUi(this);

    setWindowTitle("Ranking Challenge - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_Ranking_Challenge::~NCM_WIN_Ranking_Challenge()
{
    delete ui;
}
