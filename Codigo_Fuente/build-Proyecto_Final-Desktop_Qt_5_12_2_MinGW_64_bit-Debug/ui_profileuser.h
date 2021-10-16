/********************************************************************************
** Form generated from reading UI file 'profileuser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEUSER_H
#define UI_PROFILEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileUser
{
public:
    QWidget *centralwidget;
    QPushButton *pB_StartLevel2;
    QPushButton *pB_StartLevel1;
    QPushButton *pB_StartLevel3;
    QPushButton *pB_closeProfile;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProfileUser)
    {
        if (ProfileUser->objectName().isEmpty())
            ProfileUser->setObjectName(QString::fromUtf8("ProfileUser"));
        ProfileUser->resize(800, 600);
        centralwidget = new QWidget(ProfileUser);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pB_StartLevel2 = new QPushButton(centralwidget);
        pB_StartLevel2->setObjectName(QString::fromUtf8("pB_StartLevel2"));
        pB_StartLevel2->setGeometry(QRect(40, 200, 80, 21));
        pB_StartLevel1 = new QPushButton(centralwidget);
        pB_StartLevel1->setObjectName(QString::fromUtf8("pB_StartLevel1"));
        pB_StartLevel1->setGeometry(QRect(40, 170, 80, 21));
        pB_StartLevel3 = new QPushButton(centralwidget);
        pB_StartLevel3->setObjectName(QString::fromUtf8("pB_StartLevel3"));
        pB_StartLevel3->setGeometry(QRect(40, 230, 80, 21));
        pB_closeProfile = new QPushButton(centralwidget);
        pB_closeProfile->setObjectName(QString::fromUtf8("pB_closeProfile"));
        pB_closeProfile->setGeometry(QRect(650, 30, 80, 21));
        ProfileUser->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProfileUser);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        ProfileUser->setMenuBar(menubar);
        statusbar = new QStatusBar(ProfileUser);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ProfileUser->setStatusBar(statusbar);

        retranslateUi(ProfileUser);

        QMetaObject::connectSlotsByName(ProfileUser);
    } // setupUi

    void retranslateUi(QMainWindow *ProfileUser)
    {
        ProfileUser->setWindowTitle(QApplication::translate("ProfileUser", "MainWindow", nullptr));
        pB_StartLevel2->setText(QApplication::translate("ProfileUser", "Level 2", nullptr));
        pB_StartLevel1->setText(QApplication::translate("ProfileUser", "Level 1", nullptr));
        pB_StartLevel3->setText(QApplication::translate("ProfileUser", "Level 3", nullptr));
        pB_closeProfile->setText(QApplication::translate("ProfileUser", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProfileUser: public Ui_ProfileUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEUSER_H
