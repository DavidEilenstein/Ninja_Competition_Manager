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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_StarterList
{
public:
    QAction *actionget_data;
    QAction *actionreload_competitors_and_runs;
    QAction *actionUpdate;
    QAction *actionAutoupdate;
    QAction *actionChange_Table_Settings;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_DE;
    QLabel *label_Time;
    QLabel *label_Name;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_End;
    QPushButton *pushButton_BTN;
    QGridLayout *gridLayout_StarterList;
    QMenuBar *menubar;
    QMenu *menuData;
    QMenu *menuUpdate;
    QMenu *menuTable;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_StarterList)
    {
        if (NCM_WIN_StarterList->objectName().isEmpty())
            NCM_WIN_StarterList->setObjectName(QString::fromUtf8("NCM_WIN_StarterList"));
        NCM_WIN_StarterList->resize(668, 781);
        actionget_data = new QAction(NCM_WIN_StarterList);
        actionget_data->setObjectName(QString::fromUtf8("actionget_data"));
        actionreload_competitors_and_runs = new QAction(NCM_WIN_StarterList);
        actionreload_competitors_and_runs->setObjectName(QString::fromUtf8("actionreload_competitors_and_runs"));
        actionUpdate = new QAction(NCM_WIN_StarterList);
        actionUpdate->setObjectName(QString::fromUtf8("actionUpdate"));
        actionAutoupdate = new QAction(NCM_WIN_StarterList);
        actionAutoupdate->setObjectName(QString::fromUtf8("actionAutoupdate"));
        actionAutoupdate->setCheckable(true);
        actionAutoupdate->setChecked(true);
        actionChange_Table_Settings = new QAction(NCM_WIN_StarterList);
        actionChange_Table_Settings->setObjectName(QString::fromUtf8("actionChange_Table_Settings"));
        centralwidget = new QWidget(NCM_WIN_StarterList);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(false);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_DE = new QPushButton(centralwidget);
        pushButton_DE->setObjectName(QString::fromUtf8("pushButton_DE"));
        pushButton_DE->setMinimumSize(QSize(160, 80));
        pushButton_DE->setMaximumSize(QSize(160, 80));

        gridLayout_2->addWidget(pushButton_DE, 2, 0, 2, 1);

        label_Time = new QLabel(centralwidget);
        label_Time->setObjectName(QString::fromUtf8("label_Time"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_Time->sizePolicy().hasHeightForWidth());
        label_Time->setSizePolicy(sizePolicy);
        label_Time->setStyleSheet(QString::fromUtf8("font-size: 30px;"));
        label_Time->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_Time, 2, 1, 1, 1);

        label_Name = new QLabel(centralwidget);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        sizePolicy.setHeightForWidth(label_Name->sizePolicy().hasHeightForWidth());
        label_Name->setSizePolicy(sizePolicy);
        label_Name->setStyleSheet(QString::fromUtf8("font-size: 30px;"));
        label_Name->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_Name, 0, 0, 1, 4);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setStyleSheet(QString::fromUtf8("font-size: 15px;"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 3, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setStyleSheet(QString::fromUtf8("font-size: 15px;"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 3, 1, 1, 1);

        label_End = new QLabel(centralwidget);
        label_End->setObjectName(QString::fromUtf8("label_End"));
        sizePolicy.setHeightForWidth(label_End->sizePolicy().hasHeightForWidth());
        label_End->setSizePolicy(sizePolicy);
        label_End->setStyleSheet(QString::fromUtf8("font-size: 30px;"));
        label_End->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_End, 2, 2, 1, 1);

        pushButton_BTN = new QPushButton(centralwidget);
        pushButton_BTN->setObjectName(QString::fromUtf8("pushButton_BTN"));
        pushButton_BTN->setMinimumSize(QSize(160, 80));
        pushButton_BTN->setMaximumSize(QSize(160, 80));
        pushButton_BTN->setStyleSheet(QString::fromUtf8("font-size: 35px"));

        gridLayout_2->addWidget(pushButton_BTN, 2, 3, 2, 1);

        gridLayout_StarterList = new QGridLayout();
        gridLayout_StarterList->setObjectName(QString::fromUtf8("gridLayout_StarterList"));

        gridLayout_2->addLayout(gridLayout_StarterList, 1, 0, 1, 4);

        NCM_WIN_StarterList->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_StarterList);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 668, 21));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        menuUpdate = new QMenu(menubar);
        menuUpdate->setObjectName(QString::fromUtf8("menuUpdate"));
        menuTable = new QMenu(menubar);
        menuTable->setObjectName(QString::fromUtf8("menuTable"));
        NCM_WIN_StarterList->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_StarterList);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_StarterList->setStatusBar(statusbar);

        menubar->addAction(menuData->menuAction());
        menubar->addAction(menuUpdate->menuAction());
        menubar->addAction(menuTable->menuAction());
        menuData->addAction(actionget_data);
        menuData->addAction(actionreload_competitors_and_runs);
        menuUpdate->addAction(actionUpdate);
        menuUpdate->addAction(actionAutoupdate);
        menuTable->addAction(actionChange_Table_Settings);

        retranslateUi(NCM_WIN_StarterList);

        QMetaObject::connectSlotsByName(NCM_WIN_StarterList);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_StarterList)
    {
        NCM_WIN_StarterList->setWindowTitle(QCoreApplication::translate("NCM_WIN_StarterList", "MainWindow", nullptr));
        actionget_data->setText(QCoreApplication::translate("NCM_WIN_StarterList", "get data", nullptr));
        actionreload_competitors_and_runs->setText(QCoreApplication::translate("NCM_WIN_StarterList", "reload competitors and runs", nullptr));
        actionUpdate->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Update", nullptr));
#if QT_CONFIG(shortcut)
        actionUpdate->setShortcut(QCoreApplication::translate("NCM_WIN_StarterList", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAutoupdate->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Autoupdate", nullptr));
        actionChange_Table_Settings->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Change Table Settings", nullptr));
        pushButton_DE->setText(QString());
        label_Time->setText(QCoreApplication::translate("NCM_WIN_StarterList", "--:--", nullptr));
        label_Name->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Stage name", nullptr));
        label_4->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Approximate stage end", nullptr));
        label_5->setText(QCoreApplication::translate("NCM_WIN_StarterList", "Current Time", nullptr));
        label_End->setText(QCoreApplication::translate("NCM_WIN_StarterList", "--:--", nullptr));
        pushButton_BTN->setText(QCoreApplication::translate("NCM_WIN_StarterList", "\360\237\220\273\360\237\220\257\360\237\220\261\342\200\215\360\237\221\244", nullptr));
        menuData->setTitle(QCoreApplication::translate("NCM_WIN_StarterList", "Data", nullptr));
        menuUpdate->setTitle(QCoreApplication::translate("NCM_WIN_StarterList", "Update", nullptr));
        menuTable->setTitle(QCoreApplication::translate("NCM_WIN_StarterList", "Table", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_StarterList: public Ui_NCM_WIN_StarterList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_STARTERLIST_H
