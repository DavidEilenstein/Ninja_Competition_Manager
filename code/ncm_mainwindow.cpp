#include "ncm_mainwindow.h"
#include "ui_ncm_mainwindow.h"

NCM_MainWindow::NCM_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NCM_MainWindow)
{
    ui->setupUi(this);
}

NCM_MainWindow::~NCM_MainWindow()
{
    delete ui;
}

