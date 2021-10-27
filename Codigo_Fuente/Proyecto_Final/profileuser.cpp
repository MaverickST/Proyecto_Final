#include "profileuser.h"
#include "ui_profileuser.h"

#define PATH_TO_USERS     "../Proyecto_Final/Users/Users.txt"
#define PATH_TO_USERS_TMP "../Proyecto_Final/Users/UsersTMP.txt"

ProfileUser::ProfileUser(QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);
}

ProfileUser::ProfileUser(User *&_User,QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);

    mUser = _User;
    showInformation();
    connect(ui->pB_StartLevel1, &QPushButton::clicked, this, &ProfileUser::startGameLevel1);
    connect(ui->pB_closeProfile, &QPushButton::clicked, this, &ProfileUser::closeWindowProfile);
}

ProfileUser::~ProfileUser(){
    delete ui;
}

void ProfileUser::showInformation(){
    //Enviamos el nombre de usuario
    ui->Label_Username->setText((mUser->username()).c_str());

    //Evaluamos si las vidas del usuario son igules a 0
    if(mUser->lives() == 0){
        //En este caso se reiicia el modo campaña y el usuario perdera todo su avance
        mUser->setLives(5);
        mUser->setLevel(1);
        mUser->setScoreFirstLevel(0);
        mUser->setScoreSecondLevel(0);
        mUser->setScoreThirdLevel(0);
    }

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

void ProfileUser::updateUsers(){
    ifstream inFile;
    ofstream outFile, Temp;

    inFile.open(PATH_TO_USERS);

    //Atributos de usuario
    string Username ,Password, Level, Lives, ScoreFirstLevel
            , ScoreSecondLevel, ScoreThirdLevel;
    string updatedUsersTMP = "";

    while(!inFile.eof()){
        inFile >> Username >> Password >> Level >> Lives >> ScoreFirstLevel >> ScoreSecondLevel >> ScoreThirdLevel;
        //Se evalua si el usuario leido es el usuario con sesion activa
        if(Username == mUser->username()){
            //Si es el usuario activo, se actualiza el archivo .txt de usuarios
            updatedUsersTMP = updatedUsersTMP + Username + "   " + Password + "   " + to_string(mUser->level()) +
                    "   " + to_string(mUser->lives()) + "   " + to_string(mUser->scoreFirstLevel()) + "   " +
                    to_string(mUser->scoreSecondLevel()) + "   " +
                    to_string(mUser->scoreThirdLevel()) + "\n";
        }else{
            //Si no lo es, se respeta los datos de los demas usuarios
            updatedUsersTMP = updatedUsersTMP + Username + "   " + Password + "   " + Level +
                    "   " + Lives + "   " + ScoreFirstLevel + "   " + ScoreSecondLevel +
                    "   " + ScoreThirdLevel + "\n";
        }
    }
    //Se cierra el archivo de usuarios
    inFile.close();
    string updatedUsers = "";
    for(int i = 0; i < int((updatedUsersTMP.length())-1); i++){
        updatedUsers += updatedUsersTMP[i];
    }

    //Se abre el archivo de usuarios temporal
    Temp.open(PATH_TO_USERS_TMP);
    Temp << updatedUsers;
    Temp.close();

    //Se remueve el archivo usuarios.txt y se renombra el archivo UsersTMP.txt por Users.txt
    remove(PATH_TO_USERS);
    rename(PATH_TO_USERS_TMP , PATH_TO_USERS);
}

void ProfileUser::startGameLevel1(){
    // Se crea y muestra la partida, el mundo, ya jugar se ha dicho
    // Variables del nivel 1
    string strPath = "../Proyecto_final/:Sprites/";

    string _nameSpBackground = ":/Sprites/carretera_nivel1.png";

    string _nameSpDecor1 = ":/Sprites/arbol1.png";
    double _wDecor1 = 50,_hDecor1 = 60;
    string _nameSpDecor2 = ":/Sprites/arbusto3.png";
    double _wDecor2 = 30,_hDecor2 = 30;
    double _velDecor = -3, _probSpawnDecor = 200;

    string _nameSpEnemy = ":/Sprites/auto4.png";
    double _wEnemy = 50, _hEnemy = 30;
    double _velEnemy = -8, _probSpawnEnemy = 300;
    double _masaEnemy = 140;

    string _nameSpObstacle = ":/Sprites/cono1.png";
    double _wObstacle = 20, _hObstacle = 20;
    double _velObstacle = -3, _probSpawnObst = 400;

    string _nameSpShot = ":/Sprites/bala1.png";
    double _wShot = 50, _hShot = 50;
    double _velshot = 12,_masaShot = 100, _millisecondsToShot = 10000;

    double _wExplosion = 80, _hExplosion = 80;

    string _nameSpBoss = "";
    double _RBoss = 30, _masaBoss = 3;
    double _LBoss = 105, _tFinalBoss = 100000; // 100 segundos, undidades -> millisegundos

    qDebug() << "Aqui no" <<__LINE__;

    Game = new GameWorld(_nameSpBackground,
    _nameSpDecor1, _wDecor1, _hDecor1,
    _nameSpDecor2, _wDecor2, _hDecor2, _velDecor, _probSpawnDecor,
    _nameSpEnemy, _wEnemy, _hEnemy,
    _velEnemy, _masaEnemy ,_probSpawnEnemy,
    _nameSpObstacle, _wObstacle, _hObstacle, _velObstacle, _probSpawnObst,
    _nameSpShot, _wShot, _hShot, _velshot, _masaShot, _millisecondsToShot,
    _wExplosion, _hExplosion, 
    _nameSpBoss, _RBoss, _masaBoss, _LBoss, _tFinalBoss,
    mUser);



    Game->show();

    connect(Game, &GameWorld::endGame, this, &ProfileUser::endGameLevel1);

    this->setVisible(false);
}

void ProfileUser::endGameLevel1(){
    // Se cierra y elimina la ventana del juego.
    Game->close();
    delete Game;
    this->setVisible(true);
    //Actualizacion de Score
    if(mUser->score() > mUser->scoreFirstLevel()){
        mUser->setScoreFirstLevel(mUser->score());
    }
    showInformation();
}

void ProfileUser::on_pB_closeProfile_clicked(){
    updateUsers();
}
