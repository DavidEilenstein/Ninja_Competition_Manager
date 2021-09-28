#include "ncm_mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NCM_MainWindow w;
    w.show();
    return a.exec();
}
