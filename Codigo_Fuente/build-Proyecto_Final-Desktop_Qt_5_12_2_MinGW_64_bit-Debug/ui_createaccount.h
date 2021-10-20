/********************************************************************************
** Form generated from reading UI file 'createaccount.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCOUNT_H
#define UI_CREATEACCOUNT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createAccount
{
public:
    QWidget *centralwidget;
    QPushButton *PB_Create;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *Username;
    QLabel *Label_Status;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *Password;
    QPushButton *PB_Exit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *createAccount)
    {
        if (createAccount->objectName().isEmpty())
            createAccount->setObjectName(QString::fromUtf8("createAccount"));
        createAccount->resize(400, 350);
        centralwidget = new QWidget(createAccount);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        PB_Create = new QPushButton(centralwidget);
        PB_Create->setObjectName(QString::fromUtf8("PB_Create"));
        PB_Create->setGeometry(QRect(110, 250, 161, 21));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 91, 281, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        Username = new QLineEdit(horizontalLayoutWidget);
        Username->setObjectName(QString::fromUtf8("Username"));

        horizontalLayout->addWidget(Username);

        Label_Status = new QLabel(centralwidget);
        Label_Status->setObjectName(QString::fromUtf8("Label_Status"));
        Label_Status->setGeometry(QRect(80, 180, 221, 31));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(60, 140, 281, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        Password = new QLineEdit(horizontalLayoutWidget_2);
        Password->setObjectName(QString::fromUtf8("Password"));

        horizontalLayout_2->addWidget(Password);

        PB_Exit = new QPushButton(centralwidget);
        PB_Exit->setObjectName(QString::fromUtf8("PB_Exit"));
        PB_Exit->setGeometry(QRect(310, 10, 71, 21));
        createAccount->setCentralWidget(centralwidget);
        menubar = new QMenuBar(createAccount);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 20));
        createAccount->setMenuBar(menubar);
        statusbar = new QStatusBar(createAccount);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        createAccount->setStatusBar(statusbar);

        retranslateUi(createAccount);

        QMetaObject::connectSlotsByName(createAccount);
    } // setupUi

    void retranslateUi(QMainWindow *createAccount)
    {
        createAccount->setWindowTitle(QApplication::translate("createAccount", "MainWindow", nullptr));
        PB_Create->setText(QApplication::translate("createAccount", "Create", nullptr));
        label->setText(QApplication::translate("createAccount", "Username", nullptr));
        Label_Status->setText(QString());
        label_2->setText(QApplication::translate("createAccount", "Password", nullptr));
        PB_Exit->setText(QApplication::translate("createAccount", "Exiit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createAccount: public Ui_createAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCOUNT_H
