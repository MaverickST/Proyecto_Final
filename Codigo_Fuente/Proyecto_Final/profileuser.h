#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <string>
#include <fstream>

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
    explicit ProfileUser(User *&_User,QWidget *parent = nullptr);

    ~ProfileUser();

    void showInformation();
    void updateUsers();

    void setObjectsValues(const QMap<string, double> &objectsValues);

    void setSpritesWorld(const QMap<string, string> &spritesWorld);

public slots:
    void startGame();
    void endGame();

signals:
    void closeWindowProfile();

private slots:
    void on_pB_closeProfile_clicked();

private:
    Ui::ProfileUser *ui;

    GameWorld *Game;
    User *mUser;

    QMap<string, double> mObjectsValues;

    QMap<string, string> mSpritesWorld;
};

#endif // PROFILEUSER_H
