/********************************************************************************
** Form generated from reading UI file 'ncm_win_starterlist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_STARTERLIST_H
#define UI_NCM_WIN_STARTERLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_StarterList
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_StarterList)
    {
        if (NCM_WIN_StarterList->objectName().isEmpty())
            NCM_WIN_StarterList->setObjectName(QString::fromUtf8("NCM_WIN_StarterList"));
        NCM_WIN_StarterList->resize(800, 600);
        menubar = new QMenuBar(NCM_WIN_StarterList);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        NCM_WIN_StarterList->setMenuBar(menubar);
        centralwidget = new QWidget(NCM_WIN_StarterList);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NCM_WIN_StarterList->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(NCM_WIN_StarterList);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_StarterList->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_StarterList);

        QMetaObject::connectSlotsByName(NCM_WIN_StarterList);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_StarterList)
    {
        NCM_WIN_StarterList->setWindowTitle(QCoreApplication::translate("NCM_WIN_StarterList", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_StarterList: public Ui_NCM_WIN_StarterList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_STARTERLIST_H
