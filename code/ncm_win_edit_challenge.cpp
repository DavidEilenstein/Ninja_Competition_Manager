#include "ncm_win_edit_challenge.h"
#include "ui_ncm_win_edit_challenge.h"

NCM_WIN_Edit_Challenge::NCM_WIN_Edit_Challenge(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Edit_Challenge)
{
    ui->setupUi(this);

    setWindowTitle("Edit Challenge - by David Eilenstein");
    setWindowIcon(QIcon(":/img/Logo_Final.jpg"));
}

NCM_WIN_Edit_Challenge::~NCM_WIN_Edit_Challenge()
{
    delete ui;
}
