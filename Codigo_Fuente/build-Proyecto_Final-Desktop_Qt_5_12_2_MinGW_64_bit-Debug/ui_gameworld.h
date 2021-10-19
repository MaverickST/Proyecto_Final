/********************************************************************************
** Form generated from reading UI file 'gameworld.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWORLD_H
#define UI_GAMEWORLD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWorld
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QPushButton *pB_StartGame;
    QPushButton *pB_ExitGame;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GameWorld)
    {
        if (GameWorld->objectName().isEmpty())
            GameWorld->setObjectName(QString::fromUtf8("GameWorld"));
        GameWorld->resize(800, 600);
        centralwidget = new QWidget(GameWorld);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 800, 600));
        pB_StartGame = new QPushButton(centralwidget);
        pB_StartGame->setObjectName(QString::fromUtf8("pB_StartGame"));
        pB_StartGame->setGeometry(QRect(690, 10, 80, 21));
        pB_ExitGame = new QPushButton(centralwidget);
        pB_ExitGame->setObjectName(QString::fromUtf8("pB_ExitGame"));
        pB_ExitGame->setGeometry(QRect(690, 40, 80, 21));
        GameWorld->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GameWorld);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        GameWorld->setMenuBar(menubar);
        statusbar = new QStatusBar(GameWorld);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GameWorld->setStatusBar(statusbar);

        retranslateUi(GameWorld);

        QMetaObject::connectSlotsByName(GameWorld);
    } // setupUi

    void retranslateUi(QMainWindow *GameWorld)
    {
        GameWorld->setWindowTitle(QApplication::translate("GameWorld", "MainWindow", nullptr));
        pB_StartGame->setText(QApplication::translate("GameWorld", "Start", nullptr));
        pB_ExitGame->setText(QApplication::translate("GameWorld", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameWorld: public Ui_GameWorld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWORLD_H
