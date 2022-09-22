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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_ResultEntering_Stage
{
public:
    QAction *actionData_Dialog;
    QAction *actionreload_competitors_and_runs;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_2;
    QCheckBox *checkBox_BestTrick;
    QLabel *label;
    QCheckBox *checkBox_WorstFail;
    QLabel *label_4;
    QComboBox *comboBox_Checkpoint;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *spinBox_s;
    QLabel *label_5;
    QSpinBox *spinBox_ms;
    QSpinBox *spinBox_min;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QPushButton *pushButton_SaveRun;
    QComboBox *comboBox_Competitor;
    QCheckBox *checkBox_Rerun;
    QMenuBar *menubar;
    QMenu *menuData;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_ResultEntering_Stage)
    {
        if (NCM_WIN_ResultEntering_Stage->objectName().isEmpty())
            NCM_WIN_ResultEntering_Stage->setObjectName(QString::fromUtf8("NCM_WIN_ResultEntering_Stage"));
        NCM_WIN_ResultEntering_Stage->resize(416, 197);
        actionData_Dialog = new QAction(NCM_WIN_ResultEntering_Stage);
        actionData_Dialog->setObjectName(QString::fromUtf8("actionData_Dialog"));
        actionreload_competitors_and_runs = new QAction(NCM_WIN_ResultEntering_Stage);
        actionreload_competitors_and_runs->setObjectName(QString::fromUtf8("actionreload_competitors_and_runs"));
        centralwidget = new QWidget(NCM_WIN_ResultEntering_Stage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(false);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        checkBox_BestTrick = new QCheckBox(centralwidget);
        checkBox_BestTrick->setObjectName(QString::fromUtf8("checkBox_BestTrick"));

        gridLayout->addWidget(checkBox_BestTrick, 3, 2, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        checkBox_WorstFail = new QCheckBox(centralwidget);
        checkBox_WorstFail->setObjectName(QString::fromUtf8("checkBox_WorstFail"));

        gridLayout->addWidget(checkBox_WorstFail, 3, 1, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        comboBox_Checkpoint = new QComboBox(centralwidget);
        comboBox_Checkpoint->setObjectName(QString::fromUtf8("comboBox_Checkpoint"));

        gridLayout->addWidget(comboBox_Checkpoint, 1, 1, 1, 4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        spinBox_s = new QSpinBox(centralwidget);
        spinBox_s->setObjectName(QString::fromUtf8("spinBox_s"));
        spinBox_s->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_s->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_s->setMaximum(59);

        gridLayout_2->addWidget(spinBox_s, 0, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        spinBox_ms = new QSpinBox(centralwidget);
        spinBox_ms->setObjectName(QString::fromUtf8("spinBox_ms"));
        spinBox_ms->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_ms->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_ms->setMaximum(999);

        gridLayout_2->addWidget(spinBox_ms, 0, 4, 1, 1);

        spinBox_min = new QSpinBox(centralwidget);
        spinBox_min->setObjectName(QString::fromUtf8("spinBox_min"));
        spinBox_min->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_min->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_min->setMaximum(999);

        gridLayout_2->addWidget(spinBox_min, 0, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 3, 1, 1);


        gridLayout->addLayout(gridLayout_2, 2, 1, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 3, 1, 2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 5);

        pushButton_SaveRun = new QPushButton(centralwidget);
        pushButton_SaveRun->setObjectName(QString::fromUtf8("pushButton_SaveRun"));

        gridLayout->addWidget(pushButton_SaveRun, 6, 0, 1, 5);

        comboBox_Competitor = new QComboBox(centralwidget);
        comboBox_Competitor->setObjectName(QString::fromUtf8("comboBox_Competitor"));

        gridLayout->addWidget(comboBox_Competitor, 0, 1, 1, 3);

        checkBox_Rerun = new QCheckBox(centralwidget);
        checkBox_Rerun->setObjectName(QString::fromUtf8("checkBox_Rerun"));

        gridLayout->addWidget(checkBox_Rerun, 0, 4, 1, 1);

        NCM_WIN_ResultEntering_Stage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_ResultEntering_Stage);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 416, 21));
        menuData = new QMenu(menubar);
        menuData->setObjectName(QString::fromUtf8("menuData"));
        NCM_WIN_ResultEntering_Stage->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_ResultEntering_Stage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_ResultEntering_Stage->setStatusBar(statusbar);

        menubar->addAction(menuData->menuAction());
        menuData->addAction(actionData_Dialog);
        menuData->addAction(actionreload_competitors_and_runs);

        retranslateUi(NCM_WIN_ResultEntering_Stage);

        QMetaObject::connectSlotsByName(NCM_WIN_ResultEntering_Stage);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_ResultEntering_Stage)
    {
        NCM_WIN_ResultEntering_Stage->setWindowTitle(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "MainWindow", nullptr));
        actionData_Dialog->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Data Dialog", nullptr));
        actionreload_competitors_and_runs->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "reload competitors and runs", nullptr));
        label_3->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Time of failure or buzzer", nullptr));
        label_2->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Checkpoint reached", nullptr));
        checkBox_BestTrick->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Best trick \360\237\244\231", nullptr));
        label->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Competitor", nullptr));
        checkBox_WorstFail->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Worst fail \360\237\222\251", nullptr));
        label_4->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Special prices", nullptr));
        spinBox_s->setSuffix(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", " s", nullptr));
        label_5->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", ":", nullptr));
        spinBox_ms->setSuffix(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", " ms", nullptr));
        spinBox_min->setSuffix(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", " min", nullptr));
        label_6->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", ":", nullptr));
        pushButton_SaveRun->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Save Run", nullptr));
        checkBox_Rerun->setText(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Allow rerun", nullptr));
        menuData->setTitle(QCoreApplication::translate("NCM_WIN_ResultEntering_Stage", "Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_ResultEntering_Stage: public Ui_NCM_WIN_ResultEntering_Stage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_RESULTENTERING_STAGE_H
