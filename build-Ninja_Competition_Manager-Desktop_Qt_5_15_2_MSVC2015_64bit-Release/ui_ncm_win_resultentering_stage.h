/********************************************************************************
** Form generated from reading UI file 'ncm_win_resultentering_stage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_RESULTENTERING_STAGE_H
#define UI_NCM_WIN_RESULTENTERING_STAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_ResultEntering_Stage
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_ResultEntering_Stage)
    {
        if (NCM_WIN_ResultEntering_Stage->objectName().isEmpty())
            NCM_WIN_ResultEntering_Stage->setObjectName(QString::fromUtf8("NCM_WIN_ResultEntering_Stage"));
        NCM_WIN_ResultEntering_Stage->resize(800, 600);
        menubar = new QMenuBar(NCM_WIN_ResultEntering_Stage);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        NCM_WIN_ResultEntering_Stage->setMenuBar(menubar);
        centralwidget = new QWidget(NCM_WIN_ResultEntering_Stage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        NCM_WIN_ResultEntering_Stage->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(NCM_WIN_ResultEntering_Stage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_ResultEntering_Stage->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_ResultEntering_Stage);

        QMetaObject::connectSlotsByName(NCM_WIN_ResultEntering_Stage);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_ResultEntering_Stage)
    {
        NCM_WIN_ResultEntering_Stage->setWindowTitle(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_ResultEntering_Stage: public Ui_NCM_WIN_ResultEntering_Stage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_RESULTENTERING_STAGE_H