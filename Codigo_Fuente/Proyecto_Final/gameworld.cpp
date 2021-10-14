#include "gameworld.h"
#include "ui_gameworld.h"

GameWorld::GameWorld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWorld)
{
    ui->setupUi(this);
}

GameWorld::~GameWorld()
{
    delete ui;
}
