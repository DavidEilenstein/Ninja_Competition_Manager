/********************************************************************************
** Form generated from reading UI file 'ncm_win_resultentering_challenge.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_RESULTENTERING_CHALLENGE_H
#define UI_NCM_WIN_RESULTENTERING_CHALLENGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_ResultEntering_Challenge
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_ResultEntering_Challenge)
    {
        if (NCM_WIN_ResultEntering_Challenge->objectName().isEmpty())
            NCM_WIN_ResultEntering_Challenge->setObjectName(QString::fromUtf8("NCM_WIN_ResultEntering_Challenge"));
        NCM_WIN_ResultEntering_Challenge->resize(800, 600);
        menubar = new QMenuBar(NCM_WIN_ResultEntering_Challenge);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        NCM_WIN_ResultEntering_Challenge->setMenuBar(menubar);
        centralwidget = new QWidget(NCM_WIN_ResultEntering_Challenge);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NCM_WIN_ResultEntering_Challenge->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(NCM_WIN_ResultEntering_Challenge);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_ResultEntering_Challenge->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_ResultEntering_Challenge);

        QMetaObject::connectSlotsByName(NCM_WIN_ResultEntering_Challenge);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_ResultEntering_Challenge)
    {
        NCM_WIN_ResultEntering_Challenge->setWindowTitle(QCoreApplication::translate("NCM_WIN_ResultEntering_Challenge", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_ResultEntering_Challenge: public Ui_NCM_WIN_ResultEntering_Challenge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_RESULTENTERING_CHALLENGE_H
