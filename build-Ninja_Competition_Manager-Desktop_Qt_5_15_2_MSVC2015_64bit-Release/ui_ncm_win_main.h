/********************************************************************************
** Form generated from reading UI file 'ncm_win_main.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_MAIN_H
#define UI_NCM_WIN_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_Main
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_Satges;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_Stage_Edit;
    QPushButton *pushButton_Stage_ResultEntering;
    QPushButton *pushButton_Stage_Ranking;
    QPushButton *pushButton_Stage_StarterList;
    QGroupBox *groupBox_Comp;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_Comp_Load;
    QLineEdit *lineEdit_ComPath;
    QPushButton *pushButton_Comp_Create;
    QPushButton *pushButton_Comp_Select;
    QGroupBox *groupBox_Challenges;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_Challenges_ResultEntering;
    QPushButton *pushButton_Challenges_Ranking;
    QPushButton *pushButton_Challenges_Edit;
    QLabel *label;
    QGroupBox *groupBox_Checkin;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Checkin;
    QGroupBox *groupBox_Links;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_DavidEilenstein;
    QPushButton *pushButton_Tutorial;
    QPushButton *pushButton_Updates;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_Main)
    {
        if (NCM_WIN_Main->objectName().isEmpty())
            NCM_WIN_Main->setObjectName(QString::fromUtf8("NCM_WIN_Main"));
        NCM_WIN_Main->resize(560, 613);
        centralwidget = new QWidget(NCM_WIN_Main);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_Satges = new QGroupBox(centralwidget);
        groupBox_Satges->setObjectName(QString::fromUtf8("groupBox_Satges"));
        groupBox_Satges->setEnabled(false);
        groupBox_Satges->setAlignment(Qt::AlignCenter);
        groupBox_Satges->setCheckable(false);
        gridLayout_4 = new QGridLayout(groupBox_Satges);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton_Stage_Edit = new QPushButton(groupBox_Satges);
        pushButton_Stage_Edit->setObjectName(QString::fromUtf8("pushButton_Stage_Edit"));
        pushButton_Stage_Edit->setMinimumSize(QSize(0, 40));
        pushButton_Stage_Edit->setSizeIncrement(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Stage_Edit, 1, 0, 1, 1);

        pushButton_Stage_ResultEntering = new QPushButton(groupBox_Satges);
        pushButton_Stage_ResultEntering->setObjectName(QString::fromUtf8("pushButton_Stage_ResultEntering"));
        pushButton_Stage_ResultEntering->setMinimumSize(QSize(0, 40));
        pushButton_Stage_ResultEntering->setSizeIncrement(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Stage_ResultEntering, 3, 0, 1, 1);

        pushButton_Stage_Ranking = new QPushButton(groupBox_Satges);
        pushButton_Stage_Ranking->setObjectName(QString::fromUtf8("pushButton_Stage_Ranking"));
        pushButton_Stage_Ranking->setMinimumSize(QSize(0, 40));
        pushButton_Stage_Ranking->setSizeIncrement(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Stage_Ranking, 4, 0, 1, 1);

        pushButton_Stage_StarterList = new QPushButton(groupBox_Satges);
        pushButton_Stage_StarterList->setObjectName(QString::fromUtf8("pushButton_Stage_StarterList"));
        pushButton_Stage_StarterList->setMinimumSize(QSize(0, 40));
        pushButton_Stage_StarterList->setSizeIncrement(QSize(0, 40));

        gridLayout_4->addWidget(pushButton_Stage_StarterList, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox_Satges, 3, 0, 1, 1);

        groupBox_Comp = new QGroupBox(centralwidget);
        groupBox_Comp->setObjectName(QString::fromUtf8("groupBox_Comp"));
        groupBox_Comp->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(groupBox_Comp);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_Comp_Load = new QPushButton(groupBox_Comp);
        pushButton_Comp_Load->setObjectName(QString::fromUtf8("pushButton_Comp_Load"));
        pushButton_Comp_Load->setMinimumSize(QSize(0, 40));
        pushButton_Comp_Load->setMaximumSize(QSize(16777215, 40));

        gridLayout_2->addWidget(pushButton_Comp_Load, 0, 2, 1, 1);

        lineEdit_ComPath = new QLineEdit(groupBox_Comp);
        lineEdit_ComPath->setObjectName(QString::fromUtf8("lineEdit_ComPath"));
        lineEdit_ComPath->setMinimumSize(QSize(0, 40));
        lineEdit_ComPath->setMaximumSize(QSize(16777215, 40));
        lineEdit_ComPath->setReadOnly(false);

        gridLayout_2->addWidget(lineEdit_ComPath, 2, 0, 1, 3);

        pushButton_Comp_Create = new QPushButton(groupBox_Comp);
        pushButton_Comp_Create->setObjectName(QString::fromUtf8("pushButton_Comp_Create"));
        pushButton_Comp_Create->setMinimumSize(QSize(0, 40));
        pushButton_Comp_Create->setSizeIncrement(QSize(0, 40));

        gridLayout_2->addWidget(pushButton_Comp_Create, 0, 1, 1, 1);

        pushButton_Comp_Select = new QPushButton(groupBox_Comp);
        pushButton_Comp_Select->setObjectName(QString::fromUtf8("pushButton_Comp_Select"));
        pushButton_Comp_Select->setMinimumSize(QSize(0, 40));
        pushButton_Comp_Select->setSizeIncrement(QSize(0, 40));

        gridLayout_2->addWidget(pushButton_Comp_Select, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_Comp, 1, 0, 1, 2);

        groupBox_Challenges = new QGroupBox(centralwidget);
        groupBox_Challenges->setObjectName(QString::fromUtf8("groupBox_Challenges"));
        groupBox_Challenges->setEnabled(false);
        groupBox_Challenges->setAlignment(Qt::AlignCenter);
        groupBox_Challenges->setCheckable(false);
        groupBox_Challenges->setChecked(false);
        gridLayout_5 = new QGridLayout(groupBox_Challenges);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_Challenges_ResultEntering = new QPushButton(groupBox_Challenges);
        pushButton_Challenges_ResultEntering->setObjectName(QString::fromUtf8("pushButton_Challenges_ResultEntering"));
        pushButton_Challenges_ResultEntering->setMinimumSize(QSize(0, 40));
        pushButton_Challenges_ResultEntering->setSizeIncrement(QSize(0, 40));

        gridLayout_5->addWidget(pushButton_Challenges_ResultEntering, 3, 0, 1, 1);

        pushButton_Challenges_Ranking = new QPushButton(groupBox_Challenges);
        pushButton_Challenges_Ranking->setObjectName(QString::fromUtf8("pushButton_Challenges_Ranking"));
        pushButton_Challenges_Ranking->setMinimumSize(QSize(0, 40));
        pushButton_Challenges_Ranking->setSizeIncrement(QSize(0, 40));

        gridLayout_5->addWidget(pushButton_Challenges_Ranking, 4, 0, 1, 1);

        pushButton_Challenges_Edit = new QPushButton(groupBox_Challenges);
        pushButton_Challenges_Edit->setObjectName(QString::fromUtf8("pushButton_Challenges_Edit"));
        pushButton_Challenges_Edit->setMinimumSize(QSize(0, 40));
        pushButton_Challenges_Edit->setSizeIncrement(QSize(0, 40));

        gridLayout_5->addWidget(pushButton_Challenges_Edit, 1, 0, 1, 1);

        label = new QLabel(groupBox_Challenges);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 40));
        label->setSizeIncrement(QSize(0, 40));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox_Challenges, 3, 1, 1, 1);

        groupBox_Checkin = new QGroupBox(centralwidget);
        groupBox_Checkin->setObjectName(QString::fromUtf8("groupBox_Checkin"));
        groupBox_Checkin->setEnabled(false);
        groupBox_Checkin->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(groupBox_Checkin);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_Checkin = new QPushButton(groupBox_Checkin);
        pushButton_Checkin->setObjectName(QString::fromUtf8("pushButton_Checkin"));
        pushButton_Checkin->setMinimumSize(QSize(0, 40));
        pushButton_Checkin->setSizeIncrement(QSize(0, 40));

        gridLayout_3->addWidget(pushButton_Checkin, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_Checkin, 2, 0, 1, 2);

        groupBox_Links = new QGroupBox(centralwidget);
        groupBox_Links->setObjectName(QString::fromUtf8("groupBox_Links"));
        groupBox_Links->setAlignment(Qt::AlignCenter);
        gridLayout_6 = new QGridLayout(groupBox_Links);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        pushButton_DavidEilenstein = new QPushButton(groupBox_Links);
        pushButton_DavidEilenstein->setObjectName(QString::fromUtf8("pushButton_DavidEilenstein"));
        pushButton_DavidEilenstein->setMinimumSize(QSize(170, 100));
        pushButton_DavidEilenstein->setMaximumSize(QSize(170, 100));

        gridLayout_6->addWidget(pushButton_DavidEilenstein, 0, 1, 1, 1);

        pushButton_Tutorial = new QPushButton(groupBox_Links);
        pushButton_Tutorial->setObjectName(QString::fromUtf8("pushButton_Tutorial"));
        pushButton_Tutorial->setMinimumSize(QSize(170, 100));
        pushButton_Tutorial->setMaximumSize(QSize(170, 100));

        gridLayout_6->addWidget(pushButton_Tutorial, 0, 0, 1, 1);

        pushButton_Updates = new QPushButton(groupBox_Links);
        pushButton_Updates->setObjectName(QString::fromUtf8("pushButton_Updates"));
        pushButton_Updates->setMinimumSize(QSize(170, 100));
        pushButton_Updates->setMaximumSize(QSize(170, 100));

        gridLayout_6->addWidget(pushButton_Updates, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_Links, 0, 0, 1, 2);

        NCM_WIN_Main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_Main);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 560, 21));
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
        groupBox_Satges->setTitle(QCoreApplication::translate("NCM_WIN_Main", "Stages", nullptr));
        pushButton_Stage_Edit->setText(QCoreApplication::translate("NCM_WIN_Main", "Edit", nullptr));
        pushButton_Stage_ResultEntering->setText(QCoreApplication::translate("NCM_WIN_Main", "Result Entering", nullptr));
        pushButton_Stage_Ranking->setText(QCoreApplication::translate("NCM_WIN_Main", "Ranking", nullptr));
        pushButton_Stage_StarterList->setText(QCoreApplication::translate("NCM_WIN_Main", "Starter List", nullptr));
        groupBox_Comp->setTitle(QCoreApplication::translate("NCM_WIN_Main", "Competition", nullptr));
        pushButton_Comp_Load->setText(QCoreApplication::translate("NCM_WIN_Main", "Load", nullptr));
        pushButton_Comp_Create->setText(QCoreApplication::translate("NCM_WIN_Main", "Create", nullptr));
        pushButton_Comp_Select->setText(QCoreApplication::translate("NCM_WIN_Main", "Select", nullptr));
        groupBox_Challenges->setTitle(QCoreApplication::translate("NCM_WIN_Main", "Challenges", nullptr));
        pushButton_Challenges_ResultEntering->setText(QCoreApplication::translate("NCM_WIN_Main", "Result Entering", nullptr));
        pushButton_Challenges_Ranking->setText(QCoreApplication::translate("NCM_WIN_Main", "Ranking", nullptr));
        pushButton_Challenges_Edit->setText(QCoreApplication::translate("NCM_WIN_Main", "Edit", nullptr));
        label->setText(QString());
        groupBox_Checkin->setTitle(QCoreApplication::translate("NCM_WIN_Main", "Checkin", nullptr));
        pushButton_Checkin->setText(QCoreApplication::translate("NCM_WIN_Main", "Checkin", nullptr));
        groupBox_Links->setTitle(QCoreApplication::translate("NCM_WIN_Main", "Links", nullptr));
        pushButton_DavidEilenstein->setText(QString());
        pushButton_Tutorial->setText(QString());
        pushButton_Updates->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_Main: public Ui_NCM_WIN_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_MAIN_H
