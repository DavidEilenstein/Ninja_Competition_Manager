/********************************************************************************
** Form generated from reading UI file 'ncm_win_checkin.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_CHECKIN_H
#define UI_NCM_WIN_CHECKIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_CheckIn
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_CheckIn)
    {
        if (NCM_WIN_CheckIn->objectName().isEmpty())
            NCM_WIN_CheckIn->setObjectName(QString::fromUtf8("NCM_WIN_CheckIn"));
        NCM_WIN_CheckIn->resize(800, 600);
        menubar = new QMenuBar(NCM_WIN_CheckIn);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        NCM_WIN_CheckIn->setMenuBar(menubar);
        centralwidget = new QWidget(NCM_WIN_CheckIn);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NCM_WIN_CheckIn->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(NCM_WIN_CheckIn);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_CheckIn->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_CheckIn);

        QMetaObject::connectSlotsByName(NCM_WIN_CheckIn);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_CheckIn)
    {
        NCM_WIN_CheckIn->setWindowTitle(QCoreApplication::translate("NCM_WIN_CheckIn", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_CheckIn: public Ui_NCM_WIN_CheckIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_CHECKIN_H
