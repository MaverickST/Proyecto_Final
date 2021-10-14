#include "profileuser.h"
#include "ui_profileuser.h"

ProfileUser::ProfileUser(QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);

    connect(ui->pB_StartLevel1, &QPushButton::clicked, this, &ProfileUser::startGameLevel1);
    connect(ui->pB_closeProfile, &QPushButton::clicked, this, &ProfileUser::closeWindowProfile);
}

ProfileUser::~ProfileUser()
{
    delete ui;
}

void ProfileUser::startGameLevel1()
{
    // Se crea y muestra la partida, el mundo, ya jugar se ha dicho
    Game = new GameWorld;
    Game->show();

    connect(Game, &GameWorld::endGame, this, &ProfileUser::endGameLevel1);

    this->setVisible(false);

}

void ProfileUser::endGameLevel1()
{
    // Se cierra y elimina la ventana del juego.
    Game->close();
    delete Game;
    this->setVisible(true);
}
