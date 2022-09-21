/********************************************************************************
** Form generated from reading UI file 'ncm_win_edit_stage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_EDIT_STAGE_H
#define UI_NCM_WIN_EDIT_STAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_Edit_Stage
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QLineEdit *lineEdit_Name;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox_Quali_Previous_M;
    QSpinBox *spinBox_Quali_Previous_F;
    QSpinBox *spinBox_Quali_This_M;
    QSpinBox *spinBox_Quali_This_F;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBox_isFinal;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QPlainTextEdit *plainTextEdit_Challenges;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Load;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *plainTextEdit_Checkpoints;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_Edit_Stage)
    {
        if (NCM_WIN_Edit_Stage->objectName().isEmpty())
            NCM_WIN_Edit_Stage->setObjectName(QString::fromUtf8("NCM_WIN_Edit_Stage"));
        NCM_WIN_Edit_Stage->resize(677, 637);
        centralwidget = new QWidget(NCM_WIN_Edit_Stage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setSpacing(1);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(3, 3, 3, 3);
        lineEdit_Name = new QLineEdit(groupBox);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));

        gridLayout_6->addWidget(lineEdit_Name, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(3, 3, 3, 3);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        spinBox_Quali_Previous_M = new QSpinBox(groupBox_2);
        spinBox_Quali_Previous_M->setObjectName(QString::fromUtf8("spinBox_Quali_Previous_M"));
        spinBox_Quali_Previous_M->setAlignment(Qt::AlignCenter);
        spinBox_Quali_Previous_M->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Quali_Previous_M->setMaximum(999999);
        spinBox_Quali_Previous_M->setValue(1);

        gridLayout_2->addWidget(spinBox_Quali_Previous_M, 2, 2, 1, 1);

        spinBox_Quali_Previous_F = new QSpinBox(groupBox_2);
        spinBox_Quali_Previous_F->setObjectName(QString::fromUtf8("spinBox_Quali_Previous_F"));
        spinBox_Quali_Previous_F->setAlignment(Qt::AlignCenter);
        spinBox_Quali_Previous_F->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Quali_Previous_F->setMaximum(999999);
        spinBox_Quali_Previous_F->setValue(1);

        gridLayout_2->addWidget(spinBox_Quali_Previous_F, 2, 1, 1, 1);

        spinBox_Quali_This_M = new QSpinBox(groupBox_2);
        spinBox_Quali_This_M->setObjectName(QString::fromUtf8("spinBox_Quali_This_M"));
        spinBox_Quali_This_M->setAlignment(Qt::AlignCenter);
        spinBox_Quali_This_M->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Quali_This_M->setMaximum(999999);
        spinBox_Quali_This_M->setValue(15);

        gridLayout_2->addWidget(spinBox_Quali_This_M, 1, 2, 1, 1);

        spinBox_Quali_This_F = new QSpinBox(groupBox_2);
        spinBox_Quali_This_F->setObjectName(QString::fromUtf8("spinBox_Quali_This_F"));
        spinBox_Quali_This_F->setAlignment(Qt::AlignCenter);
        spinBox_Quali_This_F->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Quali_This_F->setMaximum(999999);
        spinBox_Quali_This_F->setValue(5);

        gridLayout_2->addWidget(spinBox_Quali_This_F, 1, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(3, 3, 3, 3);
        checkBox_isFinal = new QCheckBox(groupBox_5);
        checkBox_isFinal->setObjectName(QString::fromUtf8("checkBox_isFinal"));

        gridLayout_5->addWidget(checkBox_isFinal, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(3, 3, 3, 3);
        plainTextEdit_Challenges = new QPlainTextEdit(groupBox_3);
        plainTextEdit_Challenges->setObjectName(QString::fromUtf8("plainTextEdit_Challenges"));

        gridLayout_4->addWidget(plainTextEdit_Challenges, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 3, 0, 1, 1);

        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        pushButton_Save = new QPushButton(groupBox_6);
        pushButton_Save->setObjectName(QString::fromUtf8("pushButton_Save"));

        gridLayout_7->addWidget(pushButton_Save, 1, 0, 1, 1);

        pushButton_Load = new QPushButton(groupBox_6);
        pushButton_Load->setObjectName(QString::fromUtf8("pushButton_Load"));

        gridLayout_7->addWidget(pushButton_Load, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_6, 4, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        plainTextEdit_Checkpoints = new QPlainTextEdit(groupBox_4);
        plainTextEdit_Checkpoints->setObjectName(QString::fromUtf8("plainTextEdit_Checkpoints"));

        gridLayout_3->addWidget(plainTextEdit_Checkpoints, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_4, 0, 2, 5, 1);

        NCM_WIN_Edit_Stage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_Edit_Stage);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 677, 21));
        NCM_WIN_Edit_Stage->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_Edit_Stage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_Edit_Stage->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_Edit_Stage);

        QMetaObject::connectSlotsByName(NCM_WIN_Edit_Stage);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_Edit_Stage)
    {
        NCM_WIN_Edit_Stage->setWindowTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Stage Name", nullptr));
        lineEdit_Name->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Stage 2", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Qualification for the next stage from stage performance", nullptr));
        label_2->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Previous Stage", nullptr));
        label->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "This Stage", nullptr));
        label_3->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Female", nullptr));
        label_4->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Male", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Other", nullptr));
        checkBox_isFinal->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "is Final Stage", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Challenges that run parallel for alternative qualification (line by line)", nullptr));
        plainTextEdit_Challenges->setPlainText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Challegne A Max Dismount\n"
"Challenge B Long Balance\n"
"Challange C Double Spider Climb", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Data Management", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Save", nullptr));
        pushButton_Load->setText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Load", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Checkpoints of the stage (line by line)", nullptr));
        plainTextEdit_Checkpoints->setPlainText(QCoreApplication::translate("NCM_WIN_Edit_Stage", "Start\n"
"5 Step (1)\n"
"5 Step (2)\n"
"5 Step (3)\n"
"5 Step (4)\n"
"5 Step (5)\n"
"5 Step (Plattform)\n"
"Double Salmon Ladder (1st trasfer)\n"
"Double Salmon Ladder (4th ladder rung)\n"
"Double Salmon Ladder (2nd transfer)\n"
"Bar after Double Salmon Ladder\n"
"Ringslider (holded safely)\n"
"Ringslider (started sliding)\n"
"Ringslider (Plattform)\n"
"Wall (tired)\n"
"Buzzer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_Edit_Stage: public Ui_NCM_WIN_Edit_Stage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_EDIT_STAGE_H
