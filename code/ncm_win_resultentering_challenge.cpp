#include "ncm_win_resultentering_challenge.h"
#include "ui_ncm_win_resultentering_challenge.h"

NCM_WIN_ResultEntering_Challenge::NCM_WIN_ResultEntering_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_ResultEntering_Challenge)
{
    ui->setupUi(this);
}

NCM_WIN_ResultEntering_Challenge::~NCM_WIN_ResultEntering_Challenge()
{
    delete ui;
}
