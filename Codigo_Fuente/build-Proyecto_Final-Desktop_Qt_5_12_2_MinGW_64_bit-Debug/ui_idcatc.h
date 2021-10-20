/********************************************************************************
** Form generated from reading UI file 'idcatc.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDCATC_H
#define UI_IDCATC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IDCATC
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pB_Login;
    QPushButton *pB_Multi;
    QPushButton *pB_createAccount;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Text_Username;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *Text_Password;
    QLabel *Label_Status;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IDCATC)
    {
        if (IDCATC->objectName().isEmpty())
            IDCATC->setObjectName(QString::fromUtf8("IDCATC"));
        IDCATC->resize(600, 410);
        centralwidget = new QWidget(IDCATC);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(180, 340, 201, 31));
        progressBar->setValue(24);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(180, 250, 201, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pB_Login = new QPushButton(verticalLayoutWidget);
        pB_Login->setObjectName(QString::fromUtf8("pB_Login"));

        verticalLayout->addWidget(pB_Login);

        pB_Multi = new QPushButton(verticalLayoutWidget);
        pB_Multi->setObjectName(QString::fromUtf8("pB_Multi"));

        verticalLayout->addWidget(pB_Multi);

        pB_createAccount = new QPushButton(verticalLayoutWidget);
        pB_createAccount->setObjectName(QString::fromUtf8("pB_createAccount"));

        verticalLayout->addWidget(pB_createAccount);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 70, 321, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        Text_Username = new QLineEdit(horizontalLayoutWidget);
        Text_Username->setObjectName(QString::fromUtf8("Text_Username"));

        horizontalLayout->addWidget(Text_Username);

        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(120, 140, 321, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        Text_Password = new QLineEdit(horizontalLayoutWidget_2);
        Text_Password->setObjectName(QString::fromUtf8("Text_Password"));

        horizontalLayout_2->addWidget(Text_Password);

        Label_Status = new QLabel(centralwidget);
        Label_Status->setObjectName(QString::fromUtf8("Label_Status"));
        Label_Status->setGeometry(QRect(120, 210, 321, 20));
        IDCATC->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IDCATC);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 20));
        IDCATC->setMenuBar(menubar);
        statusbar = new QStatusBar(IDCATC);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        IDCATC->setStatusBar(statusbar);

        retranslateUi(IDCATC);

        QMetaObject::connectSlotsByName(IDCATC);
    } // setupUi

    void retranslateUi(QMainWindow *IDCATC)
    {
        IDCATC->setWindowTitle(QApplication::translate("IDCATC", "IDCATC", nullptr));
        pB_Login->setText(QApplication::translate("IDCATC", "Login", nullptr));
        pB_Multi->setText(QApplication::translate("IDCATC", "Multiplayer", nullptr));
        pB_createAccount->setText(QApplication::translate("IDCATC", "Create an account", nullptr));
        label->setText(QApplication::translate("IDCATC", "Username", nullptr));
        label_2->setText(QApplication::translate("IDCATC", "Password", nullptr));
        Label_Status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IDCATC: public Ui_IDCATC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDCATC_H
