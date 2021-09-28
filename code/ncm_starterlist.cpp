#include "ncm_starterlist.h"
#include "ui_ncm_starterlist.h"

NCM_StarterList::NCM_StarterList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_StarterList)
{
    ui->setupUi(this);
}

NCM_StarterList::~NCM_StarterList()
{
    delete ui;
}
