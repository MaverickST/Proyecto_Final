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
    connect(ui->pB_StartLevel, &QPushButton::clicked, this, &ProfileUser::startGameLevel1);
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
        //En este caso se reinicia el modo campaña y el usuario perdera todo su avance
        mUser->setLives(5);
    }

    //Envimos en numero de vidas
    ui->lcd_Lives->display(mUser->lives());

    //Enviamos el Score de cada nivel
    ui->Label_Score->setText(QString::number(mUser->score()));
}

void ProfileUser::updateUsers(){
    ifstream inFile;
    ofstream outFile, Temp;

    inFile.open(PATH_TO_USERS);

    //Atributos de usuario
    string Username ,Password, Lives, Time, Score;
    string updatedUsersTMP = "";

    while(!inFile.eof()){
        inFile >> Username >> Password >> Lives >> Time >> Score;
        //Se evalua si el usuario leido es el usuario con sesion activa
        if(Username == mUser->username()){
            //Si es el usuario activo, se actualiza el archivo .txt de usuarios
            updatedUsersTMP = updatedUsersTMP + Username + "   " + Password + "   " +
                    to_string(mUser->lives()) + "   " + to_string(mUser->time()) +
                    "   " + to_string(mUser->score()) +  "\n";
        }else{
            //Si no lo es, se respeta los datos de los demas usuarios
            updatedUsersTMP = updatedUsersTMP + Username + "   " + Password + "   " +
                    Lives + "   " + Time + "   " + Score + "\n";
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
    string strPath = "../Proyecto_final/:Sprites/";
//    User *mUser2 = nullptr;

    // Hay un cambio de mundo cada 3 minutos (180s)
    // Pero hay un aumento en la dificultad cada 20s
    int timeToChangeWorld = 180; // 180s
    // Para indicar si es multijugador o no
    bool multiPlayer = false;

    // Este contenedor almacena todos los valores de todos lo objetos del juego
    // Serían: dimensiones, probabilidades, velocidades, masas,...
    QMap<string, double> objectsValues{
        // Decoraciones
        {"wDecor1" , 50}, {"hDecor1", 50},
        {"wDecor2", 30}, {"hDecor2", 30},
        {"velDecor", -3}, {"probSpawnDecor", 200},
        // Enemigos
        {"wEnemy", 50}, {"hEnemy", 30},
        {"velEnemy", -8}, {"probSpawnEnemy", 300}, {"masaEnemy", 140},
        // Obstáculos
        {"wObstacle", 20}, {"hObstacle", 20},
        {"velObstacle", -3}, {"probSpawnObst", 400},
        // Disparo
        {"wShot", 50}, {"hShot", 50},
        {"velShot", 12}, {"masaShot", 105}, {"timeToShot", 2000},
        // Explosion
        {"wExplosion", 80}, {"hExplosion", 80},
        // Boss
        {"RBoss", 30}, {"masaBoss", 3}, {"LBoss", 102},
        {"tFinalBoss", 90000}, {"tToChangePosBoss", 2000}
    };

    // El contenedor almacena todos los sprites de todos los objetos del juego
    // Como el mundo va a cambiar cada cierto tiempo, los spriter de los objetos tambien.
    QMap<string, string> SpritesWorld{
        // Parte 1 del mundo
        {"nameSpBackground_1", ":/Sprites/carretera_nivel1.png"},
        {"nameSpDecor1_1", ":/Sprites/arbol1.png"},
        {"nameSpDecor2_1",":/Sprites/arbusto3.png"},
        {"nameSpEnemy_1",":/Sprites/auto4.png"},
        {"nameSpObstacle_1", ":/Sprites/cono1.png"},
        {"nameSpShot_1", ":/Sprites/bala1.png"},
        {"nameSpBoss_1", ""},

        // Parte 2 del mundo
        {"nameSpBackground_2", ":/Sprites/carretera_nivel2.png"},
        {"nameSpDecor1_2", ":/Sprites/camello1.png"},
        {"nameSpDecor2_2",":/Sprites/cactus1.png"},
        {"nameSpEnemy_2",":/Sprites/auto2.png"},
        {"nameSpObstacle_2", ":/Sprites/basura1.png"},
        {"nameSpShot_2", ":/Sprites/bala2.png"},
        {"nameSpBoss_2", ""},
    };


    Game = new GameWorld(SpritesWorld, objectsValues,
    timeToChangeWorld, multiPlayer,
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
    if(mUser->scoreLevel() > mUser->score()){
        mUser->setScore(mUser->scoreLevel());
    }
    showInformation();
}

void ProfileUser::on_pB_closeProfile_clicked(){
    updateUsers();
}
