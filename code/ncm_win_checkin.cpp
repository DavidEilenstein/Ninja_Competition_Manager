#include "ncm_win_checkin.h"
#include "ui_ncm_win_checkin.h"

NCM_WIN_CheckIn::NCM_WIN_CheckIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_CheckIn)
{
    ui->setupUi(this);
}

NCM_WIN_CheckIn::~NCM_WIN_CheckIn()
{
    delete ui;
}
