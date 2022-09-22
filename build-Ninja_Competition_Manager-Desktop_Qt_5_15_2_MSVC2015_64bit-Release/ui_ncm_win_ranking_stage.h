/********************************************************************************
** Form generated from reading UI file 'ncm_win_ranking_stage.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_RANKING_STAGE_H
#define UI_NCM_WIN_RANKING_STAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_Ranking_Stage
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QLabel *label_10;
    QLabel *label_6;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_Ranking_Stage)
    {
        if (NCM_WIN_Ranking_Stage->objectName().isEmpty())
            NCM_WIN_Ranking_Stage->setObjectName(QString::fromUtf8("NCM_WIN_Ranking_Stage"));
        NCM_WIN_Ranking_Stage->resize(844, 613);
        centralwidget = new QWidget(NCM_WIN_Ranking_Stage);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(160, 80));
        pushButton->setMaximumSize(QSize(160, 80));

        gridLayout_2->addWidget(pushButton, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(1, 1, 1, 1);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font-size: 20px;"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 3, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(1);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(1, 1, 1, 1);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("font-size: 20px;"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 3, 2, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(160, 80));
        pushButton_2->setMaximumSize(QSize(160, 80));
        pushButton_2->setStyleSheet(QString::fromUtf8("font-size: 30px;"));

        gridLayout_2->addWidget(pushButton_2, 3, 3, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 4, 1, 1);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 12, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 9, 1, 1);

        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 10, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 6, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 7, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 11, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 2, 0, 1, 4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 4);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("font-size: 30px;"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 4);

        NCM_WIN_Ranking_Stage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_Ranking_Stage);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 844, 26));
        NCM_WIN_Ranking_Stage->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_Ranking_Stage);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_Ranking_Stage->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_Ranking_Stage);

        QMetaObject::connectSlotsByName(NCM_WIN_Ranking_Stage);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_Ranking_Stage)
    {
        NCM_WIN_Ranking_Stage->setWindowTitle(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "MainWindow", nullptr));
        pushButton->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "Best Trick", nullptr));
        label_7->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "Name", nullptr));
        groupBox->setTitle(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "Worst Fail", nullptr));
        label_8->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "Name", nullptr));
        pushButton_2->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\220\273\360\237\220\257\360\237\220\261\342\200\215\360\237\221\244", nullptr));
        groupBox_3->setTitle(QString());
        label_3->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\244\223=current", nullptr));
        label_4->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\245\207\360\237\245\210\360\237\245\211=podium", nullptr));
        label_5->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\220\261\342\200\215\360\237\221\244=end", nullptr));
        label_10->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\221\275=speedy", nullptr));
        label_6->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\230\215=challange", nullptr));
        label_9->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\222\200=out", nullptr));
        label_2->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "\360\237\230\216=safe", nullptr));
        label->setText(QCoreApplication::translate("NCM_WIN_Ranking_Stage", "Stage Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_Ranking_Stage: public Ui_NCM_WIN_Ranking_Stage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_RANKING_STAGE_H
