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
    // Variables del nivel 1
    string strPath = "../Proyecto_final/:Sprites/";

    string _nameSpBackground = ":/Sprites/carretera2.jpg";

    string _nameSpDecor1 = ":/Sprites/arbol1.png";
    double _wDecor1 = 40,_hDecor1 = 50;
    string _nameSpDecor2 = ":/Sprites/arbusto3.png";
    double _wDecor2 = 30,_hDecor2 = 30;
    double _velDecor = 3, _numMaxDecor = 56;

    string _nameSpEnemy = ":/Sprites/auto4.png";
    double _wEnemy = 50, _hEnemy = 30;
    double _velEnemy = 8, _probSpawnEnemy = 100;

    string _nameSpObstacle = ":/Sprites/cono1.png";
    double _wObstacle = 20, _hObstacle = 20;
    double _velObstacle = 3, _probSpawnObst = 180;

    Game = new GameWorld(_nameSpBackground, _nameSpDecor1, _wDecor1, _hDecor1, _nameSpDecor2,
                         _wDecor2, _hDecor2, _velDecor, _numMaxDecor, _nameSpEnemy, _wEnemy,
                         _hEnemy, _velEnemy, _probSpawnEnemy, _nameSpObstacle, _wObstacle,
                         _hObstacle, _velObstacle, _probSpawnObst);
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

