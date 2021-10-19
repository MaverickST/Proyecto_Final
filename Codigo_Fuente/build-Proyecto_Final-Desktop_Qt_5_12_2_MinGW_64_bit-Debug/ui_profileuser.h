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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
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
    QPushButton *pB_closeProfile;
    QLabel *label;
    QLabel *Label_Username;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLCDNumber *lcd_Lives;
    QPushButton *pB_StartLevel1;
    QPushButton *pB_StartLevel2;
    QPushButton *pB_StartLevel3;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *Label_Score1;
    QLabel *Label_Score2;
    QLabel *Label_Score3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProfileUser)
    {
        if (ProfileUser->objectName().isEmpty())
            ProfileUser->setObjectName(QString::fromUtf8("ProfileUser"));
        ProfileUser->resize(800, 300);
        centralwidget = new QWidget(ProfileUser);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pB_closeProfile = new QPushButton(centralwidget);
        pB_closeProfile->setObjectName(QString::fromUtf8("pB_closeProfile"));
        pB_closeProfile->setGeometry(QRect(660, 10, 80, 21));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 61, 16));
        Label_Username = new QLabel(centralwidget);
        Label_Username->setObjectName(QString::fromUtf8("Label_Username"));
        Label_Username->setGeometry(QRect(70, 10, 181, 16));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 40, 160, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        lcd_Lives = new QLCDNumber(horizontalLayoutWidget);
        lcd_Lives->setObjectName(QString::fromUtf8("lcd_Lives"));

        horizontalLayout->addWidget(lcd_Lives);

        pB_StartLevel1 = new QPushButton(centralwidget);
        pB_StartLevel1->setObjectName(QString::fromUtf8("pB_StartLevel1"));
        pB_StartLevel1->setGeometry(QRect(510, 150, 158, 21));
        pB_StartLevel2 = new QPushButton(centralwidget);
        pB_StartLevel2->setObjectName(QString::fromUtf8("pB_StartLevel2"));
        pB_StartLevel2->setGeometry(QRect(510, 190, 158, 21));
        pB_StartLevel3 = new QPushButton(centralwidget);
        pB_StartLevel3->setObjectName(QString::fromUtf8("pB_StartLevel3"));
        pB_StartLevel3->setGeometry(QRect(510, 230, 158, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 110, 31, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 150, 161, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 190, 161, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(60, 230, 161, 16));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(340, 110, 71, 16));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(120, 110, 31, 16));
        Label_Score1 = new QLabel(centralwidget);
        Label_Score1->setObjectName(QString::fromUtf8("Label_Score1"));
        Label_Score1->setGeometry(QRect(280, 150, 171, 20));
        Label_Score2 = new QLabel(centralwidget);
        Label_Score2->setObjectName(QString::fromUtf8("Label_Score2"));
        Label_Score2->setGeometry(QRect(280, 180, 171, 20));
        Label_Score3 = new QLabel(centralwidget);
        Label_Score3->setObjectName(QString::fromUtf8("Label_Score3"));
        Label_Score3->setGeometry(QRect(280, 220, 161, 20));
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
        pB_closeProfile->setText(QApplication::translate("ProfileUser", "Logout", nullptr));
        label->setText(QApplication::translate("ProfileUser", "Welcome", nullptr));
        Label_Username->setText(QString());
        label_2->setText(QApplication::translate("ProfileUser", "Your Lives", nullptr));
        pB_StartLevel1->setText(QApplication::translate("ProfileUser", "Level 1", nullptr));
        pB_StartLevel2->setText(QApplication::translate("ProfileUser", "Level 2", nullptr));
        pB_StartLevel3->setText(QApplication::translate("ProfileUser", "Level 3", nullptr));
        label_3->setText(QApplication::translate("ProfileUser", "PLAY", nullptr));
        label_5->setText(QApplication::translate("ProfileUser", "Level #1: It's just the beginning.", nullptr));
        label_6->setText(QApplication::translate("ProfileUser", "Level #2: You almost got it.", nullptr));
        label_7->setText(QApplication::translate("ProfileUser", "Level #2: Good Job.", nullptr));
        label_8->setText(QApplication::translate("ProfileUser", "HIGH SCORE", nullptr));
        label_9->setText(QApplication::translate("ProfileUser", "LEVEL", nullptr));
        Label_Score1->setText(QString());
        Label_Score2->setText(QString());
        Label_Score3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProfileUser: public Ui_ProfileUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEUSER_H
