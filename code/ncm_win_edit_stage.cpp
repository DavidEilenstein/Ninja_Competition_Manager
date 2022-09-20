#include "ncm_win_edit_stage.h"
#include "ui_ncm_win_edit_stage.h"

NCM_WIN_Edit_Stage::NCM_WIN_Edit_Stage(NCM_OBJ_Competition comp, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_WIN_Edit_Stage)
{
    ui->setupUi(this);
}

NCM_WIN_Edit_Stage::~NCM_WIN_Edit_Stage()
{
    delete ui;
}
