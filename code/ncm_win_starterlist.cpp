#include "ncm_win_starterlist.h"
#include "ui_ncm_win_starterlist.h"

NCM_WIN_StarterList::NCM_WIN_StarterList(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_StarterList)
{
    ui->setupUi(this);
}

NCM_WIN_StarterList::~NCM_WIN_StarterList()
{
    delete ui;
}
