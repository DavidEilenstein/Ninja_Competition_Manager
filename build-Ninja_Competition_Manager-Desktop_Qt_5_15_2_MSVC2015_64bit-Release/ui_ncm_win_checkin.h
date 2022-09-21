/********************************************************************************
** Form generated from reading UI file 'ncm_win_checkin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NCM_WIN_CHECKIN_H
#define UI_NCM_WIN_CHECKIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NCM_WIN_CheckIn
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_Name;
    QLabel *label_3;
    QSpinBox *spinBox_Number;
    QFrame *line;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButton_Checkin;
    QRadioButton *radioButton_Class_F;
    QRadioButton *radioButton_Class_M;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NCM_WIN_CheckIn)
    {
        if (NCM_WIN_CheckIn->objectName().isEmpty())
            NCM_WIN_CheckIn->setObjectName(QString::fromUtf8("NCM_WIN_CheckIn"));
        NCM_WIN_CheckIn->resize(421, 169);
        centralwidget = new QWidget(NCM_WIN_CheckIn);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_Name = new QLineEdit(centralwidget);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));

        gridLayout->addWidget(lineEdit_Name, 0, 1, 1, 4);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 0));
        label_3->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinBox_Number = new QSpinBox(centralwidget);
        spinBox_Number->setObjectName(QString::fromUtf8("spinBox_Number"));
        spinBox_Number->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_Number->setMaximum(999999);

        gridLayout->addWidget(spinBox_Number, 2, 1, 1, 4);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 3, 0, 1, 5);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(50, 0));
        label_2->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(50, 0));
        label->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_Checkin = new QPushButton(centralwidget);
        pushButton_Checkin->setObjectName(QString::fromUtf8("pushButton_Checkin"));

        gridLayout->addWidget(pushButton_Checkin, 4, 0, 1, 5);

        radioButton_Class_F = new QRadioButton(centralwidget);
        radioButton_Class_F->setObjectName(QString::fromUtf8("radioButton_Class_F"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButton_Class_F->sizePolicy().hasHeightForWidth());
        radioButton_Class_F->setSizePolicy(sizePolicy);

        gridLayout->addWidget(radioButton_Class_F, 1, 1, 1, 1);

        radioButton_Class_M = new QRadioButton(centralwidget);
        radioButton_Class_M->setObjectName(QString::fromUtf8("radioButton_Class_M"));
        sizePolicy.setHeightForWidth(radioButton_Class_M->sizePolicy().hasHeightForWidth());
        radioButton_Class_M->setSizePolicy(sizePolicy);
        radioButton_Class_M->setChecked(true);

        gridLayout->addWidget(radioButton_Class_M, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 3, 1, 2);

        NCM_WIN_CheckIn->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NCM_WIN_CheckIn);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 421, 21));
        NCM_WIN_CheckIn->setMenuBar(menubar);
        statusbar = new QStatusBar(NCM_WIN_CheckIn);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        NCM_WIN_CheckIn->setStatusBar(statusbar);

        retranslateUi(NCM_WIN_CheckIn);

        QMetaObject::connectSlotsByName(NCM_WIN_CheckIn);
    } // setupUi

    void retranslateUi(QMainWindow *NCM_WIN_CheckIn)
    {
        NCM_WIN_CheckIn->setWindowTitle(QCoreApplication::translate("NCM_WIN_CheckIn", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "Number", nullptr));
        label_2->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "Class", nullptr));
        label->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "Name", nullptr));
        pushButton_Checkin->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "Checkin", nullptr));
        radioButton_Class_F->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "\342\231\200", nullptr));
        radioButton_Class_M->setText(QCoreApplication::translate("NCM_WIN_CheckIn", "\342\231\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NCM_WIN_CheckIn: public Ui_NCM_WIN_CheckIn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NCM_WIN_CHECKIN_H
