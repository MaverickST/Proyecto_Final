#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <string>

#include "gameworld.h"
#include "user.h"
using namespace std;

namespace Ui {
class ProfileUser;
}

class ProfileUser : public QMainWindow{
    Q_OBJECT

public:
    explicit ProfileUser(QWidget *parent = nullptr);
    explicit ProfileUser(User *User_,QWidget *parent = nullptr);
    ~ProfileUser();
    void showInformation();

public slots:
    void startGameLevel1();
    void endGameLevel1();

signals:
    void closeWindowProfile();

private:
    Ui::ProfileUser *ui;

    GameWorld *Game;
    User *mUser;
};

#endif // PROFILEUSER_H
