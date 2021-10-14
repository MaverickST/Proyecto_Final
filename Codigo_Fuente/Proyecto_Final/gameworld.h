#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <QPixmap>

namespace Ui {
class GameWorld;
}

class GameWorld : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWorld(QWidget *parent = nullptr);
    ~GameWorld();

signals:
    void endGame();

private:
    Ui::GameWorld *ui;
};

#endif // GAMEWORLD_H
