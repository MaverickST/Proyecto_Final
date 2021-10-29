#include "profileuser.h"
#include "ui_profileuser.h"

#define PATH_TO_USERS     "../Proyecto_Final/Users/Users.txt"
#define PATH_TO_USERS_TMP "../Proyecto_Final/Users/UsersTMP.txt"

ProfileUser::ProfileUser(QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);
}

ProfileUser::ProfileUser(User *&_User,QWidget *parent): QMainWindow(parent),ui(new Ui::ProfileUser){
    ui->setupUi(this);

    //Inicializacion del objeto mUser
    mUser = _User;
    showInformation();
    connect(ui->pB_StartLevel, &QPushButton::clicked, this, &ProfileUser::startGame);
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

    //Enviamos el mejor Score y el mejor tiempo hecho
    ui->Label_Score->setText(QString::number(mUser->score()));
    ui->LABEL_TIME->setText(QString::number(mUser->time()));
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

void ProfileUser::startGame(){

    // Se crea y muestra la partida, el mundo, y a jugar se ha dicho

    // Hay un cambio de mundo cada 3 minutos (180s)
    // Pero hay un aumento en la dificultad cada 5s
    int timeToChangeWorld = 60; // 60s -> tiempo para cambiar de mundo
    // Para indicar si es multijugador o no
    bool multiPlayer = false;
    User *mUser2 = nullptr;

    Game = new GameWorld(mSpritesWorld, mObjectsValues,
    timeToChangeWorld, multiPlayer,
    mUser, mUser2);

    Game->show();

    connect(Game, &GameWorld::endGame, this, &ProfileUser::endGame);

    this->setVisible(false);

}

void ProfileUser::endGame(){
    // Se cierra y elimina la ventana del juego.
    Game->close();
    delete Game;
    this->setVisible(true);
    //Actualizacion de Score
    if(mUser->scoreLevel() > mUser->score()){
        mUser->setScore(mUser->scoreLevel());
    }
    
    // Se actualiza el mejor tiempo
    if (mUser->time() < mUser->timeLevel()) {
        mUser->setTime(mUser->timeLevel());
    }
    
    //Si la vida del usuario es igual a 0:
    //Se resetea atributo que se encarga de guardar info del nivel jugado
    //Se resetea atributo que almacena variable del tiempo de juego
    mUser->setScoreLevel(0);
    showInformation();
}

void ProfileUser::on_pB_closeProfile_clicked(){
    updateUsers();
}

void ProfileUser::setSpritesWorld(const QMap<string, string> &spritesWorld)
{
    mSpritesWorld = spritesWorld;
}

void ProfileUser::setObjectsValues(const QMap<string, double> &objectsValues)
{
    mObjectsValues = objectsValues;
}
