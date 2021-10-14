#ifndef PROFILEUSER_H
#define PROFILEUSER_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

#include "gameworld.h"

namespace Ui {
class ProfileUser;
}

class ProfileUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProfileUser(QWidget *parent = nullptr);
    ~ProfileUser();

public slots:
    void startGameLevel1();
    void endGameLevel1();

signals:
    void closeWindowProfile();

private:
    Ui::ProfileUser *ui;

    GameWorld *Game;
};

#endif // PROFILEUSER_H
