/********************************************************************************
** Form generated from reading UI file 'ncm_win_main.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_MAIN_H
#define UI_NCM_WIN_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_Main
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_Main)
    {
        if (NCM_WIN_Main->objectName().isEmpty())
            NCM_WIN_Main->setObjectName(QString::fromUtf8("NCM_WIN_Main"));
        NCM_WIN_Main->resize(800, 600);
        centralwidget = new QWidget(NCM_WIN_Main);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NCM_WIN_Main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_Main);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        NCM_WIN_Main->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_Main);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_Main->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_Main);

        QMetaObject::connectSlotsByName(NCM_WIN_Main);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_Main)
    {
        NCM_WIN_Main->setWindowTitle(QCoreApplication::translate("NCM_WIN_Main", "NCM_WIN_Main", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_Main: public Ui_NCM_WIN_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_MAIN_H
