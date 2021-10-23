#include "profileuser.h"
#include "ui_profileuser.h"

ProfileUser::ProfileUser(QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);
}

ProfileUser::ProfileUser(User * User_,QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);

    mUser = User_;
    showInformation();
    connect(ui->pB_StartLevel1, &QPushButton::clicked, this, &ProfileUser::startGameLevel1);
    connect(ui->pB_closeProfile, &QPushButton::clicked, this, &ProfileUser::closeWindowProfile);
}

/*ProfileUser::ProfileUser(string username, string password, int level, int lives, int score1, int score2, int score3,QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){


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
}*/

ProfileUser::~ProfileUser(){
    delete ui;
}

void ProfileUser::showInformation(){
    //Enviamos el nombre de usuario
    ui->Label_Username->setText((mUser->username()).c_str());

    //Envimos en numero de vidas
    ui->lcd_Lives->display(mUser->lives());

    //Enviamos el Score de cada nivel
    ui->Label_Score1->setText(QString::number(mUser->scoreFirstLevel()));
    ui->Label_Score2->setText(QString::number(mUser->scoreSecondLevel()));
    ui->Label_Score3->setText(QString::number(mUser->scoreThirdLevel()));

    if(mUser->level() == 1){
        ui->pB_StartLevel2->setEnabled(false);
        ui->pB_StartLevel3->setEnabled(false);
    }else if(mUser->level() == 2){
        ui->pB_StartLevel2->setEnabled(true);
        ui->pB_StartLevel3->setEnabled(false);
    }else if(mUser->level() == 3){
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
