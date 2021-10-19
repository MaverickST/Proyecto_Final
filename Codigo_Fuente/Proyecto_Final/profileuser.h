#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <string>
#include "gameworld.h"
using namespace std;
namespace Ui {
class ProfileUser;
}

class ProfileUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileUser(string, string, int, int, int, int ,int ,QWidget *parent = nullptr);
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

    //Declaracion de atributos de usuarios
    string mUsername         = "";
    string mPassword         = "";
    int    mLevel            =  0;
    int    mLives            =  0;
    int    mScoreFirstLevel  =  0;
    int    mScoreSecondLevel =  0;
    int    mScoreThirdLevel  =  0;
};

#endif // PROFILEUSER_H
