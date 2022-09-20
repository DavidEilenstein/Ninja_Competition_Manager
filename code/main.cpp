#include "ncm_win_main.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NCM_WIN_Main w;
    w.show();
    return a.exec();
}
