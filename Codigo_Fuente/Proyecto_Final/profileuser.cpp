#include "profileuser.h"
#include "ui_profileuser.h"

ProfileUser::ProfileUser(string username, string password, int level, int lives, int score1, int score2, int score3,QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);

    //Inicializacion de atributos de usuario
    mUsername         = username;
    mPassword         = password;
    mLevel            =    level;
    mLives            =    lives;
    mScoreFirstLevel  =   score1;
    mScoreSecondLevel =   score2;
    mScoreThirdLevel  =   score3;

    showInformation();

    connect(ui->pB_StartLevel1, &QPushButton::clicked, this, &ProfileUser::startGameLevel1);
    connect(ui->pB_closeProfile, &QPushButton::clicked, this, &ProfileUser::closeWindowProfile);
}

ProfileUser::~ProfileUser(){
    delete ui;
}

void ProfileUser::showInformation(){
    //Enviamos el nombre de usuario
    ui->Label_Username->setText(mUsername.c_str());

    //Envimos en numero de vidas
    ui->lcd_Lives->display(mLives);

    //Enviamos el Score de cada nivel
    ui->Label_Score1->setText(QString::number(mScoreFirstLevel));
    ui->Label_Score2->setText(QString::number(mScoreSecondLevel));
    ui->Label_Score3->setText(QString::number(mScoreThirdLevel));

    if(mLevel == 1){
        ui->pB_StartLevel2->setEnabled(false);
        ui->pB_StartLevel3->setEnabled(false);
    }else if(mLevel == 2){
        ui->pB_StartLevel2->setEnabled(true);
        ui->pB_StartLevel3->setEnabled(false);
    }else if(mLevel == 3){
        ui->pB_StartLevel3->setEnabled(true);
    }
}

void ProfileUser::startGameLevel1(){
    // Se crea y muestra la partida, el mundo, ya jugar se ha dicho
    Game = new GameWorld;
    Game->show();

    connect(Game, &GameWorld::endGame, this, &ProfileUser::endGameLevel1);

    this->setVisible(false);

}

void ProfileUser::endGameLevel1(){
    // Se cierra y elimina la ventana del juego.
    Game->close();
    delete Game;
    this->setVisible(true);
}
