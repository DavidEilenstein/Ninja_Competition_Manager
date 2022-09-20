#include "ncm_win_main.h"
#include "ui_ncm_win_main.h"

NCM_WIN_Main::NCM_WIN_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NCM_WIN_Main)
{
    ui->setupUi(this);
}

NCM_WIN_Main::~NCM_WIN_Main()
{
    delete ui;
}

