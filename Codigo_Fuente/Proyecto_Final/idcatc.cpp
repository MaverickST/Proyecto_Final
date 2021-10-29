#include "idcatc.h"
#include "ui_idcatc.h"
#define PATH_TO_USERS "../Proyecto_Final/Users/Users.txt"

IDCATC::IDCATC(QWidget *parent): QMainWindow(parent), ui(new Ui::IDCATC){
    ui->setupUi(this);

    // Solo puede iniciar sesion cuando haya ingresado los datos correctamente
    ui->pB_Login->setEnabled(true); // false
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    connect(ui->pB_createAccount, &QPushButton::clicked, this, &IDCATC::openCreateAccount);
    //connect(ui->pB_Login, &QPushButton::clicked, this, &IDCATC::openProfileInterfaz);


    // Creacion de los contenedores

    // Este contenedor almacena todos los valores de todos lo objetos del juego
    // Serían: dimensiones, probabilidades, velocidades, masas,...
    mObjectsValues = QMap<string, double>{
        // Decoraciones
        {"wDecor1" , 50}, {"hDecor1", 56},
        {"wDecor2", 30}, {"hDecor2", 30},
        {"velDecor", -3}, {"probSpawnDecor", 200},
        // Enemigos
        {"wEnemy", 50}, {"hEnemy", 30},
        {"velEnemy", -8}, {"probSpawnEnemy", 200}, {"masaEnemy", 140},
        // Obstáculos
        {"wObstacle", 20}, {"hObstacle", 20},
        {"velObstacle", -3}, {"probSpawnObst", 400},
        // Disparo
        {"wShot", 20}, {"hShot", 20},
        {"velShot", 12}, {"masaShot", 90}, {"timeToShot", 2000},
        // Explosion
        {"wExplosion", 80}, {"hExplosion", 80},
        // Boss
        {"RBoss", 40}, {"masaBoss", 3}, {"LBoss", 102},
        {"tFinalBoss", 20000}, {"tToChangePosBoss", 2000}
    };

    // El contenedor almacena todos los sprites de todos los objetos del juego
    // Como el mundo va a cambiar cada cierto tiempo, los spriter de los objetos tambien.
    mSpritesWorld = QMap<string, string>{
        // Parte 1 del mundo
        {"nameSpBackground_1", ":/Sprites/carretera_nivel1.png"},
        {"nameSpDecor1_1", ":/Sprites/arbol1.png"},
        {"nameSpDecor2_1",":/Sprites/arbusto3.png"},
        {"nameSpEnemy_1",":/Sprites/auto4.png"},
        {"nameSpObstacle_1", ":/Sprites/cono1.png"},
        {"nameSpShot_1", ":/Sprites/bala1.png"},
        {"nameSpBoss_1", ":/Sprites/boss4.png"},

        // Parte 2 del mundo
        {"nameSpBackground_2", ":/Sprites/carretera_nivel2.png"},
        {"nameSpDecor1_2", ":/Sprites/camello1.png"},
        {"nameSpDecor2_2",":/Sprites/cactus1.png"},
        {"nameSpEnemy_2",":/Sprites/auto2.png"},
        {"nameSpObstacle_2", ":/Sprites/heno1.png"},
        {"nameSpShot_2", ":/Sprites/bala2.png"},
        {"nameSpBoss_2", ":/Sprites/boss11.png"},
    };

}

IDCATC::~IDCATC(){
    delete ui;
}

void IDCATC::openProfileInterfaz(){
    // Se crea y muestra ventana del perfil del usuario
    Profile = new ProfileUser(mUser);

    // Se asignan los contenedores
    Profile->setSpritesWorld(mSpritesWorld);
    Profile->setObjectsValues(mObjectsValues);

    Profile->show();

    // Conexion para el cierre de la ventana del perfil
    connect(Profile, &ProfileUser::closeWindowProfile, this, &IDCATC::closeProfileInterfaz);

    // Se oculta la ventana de inicio
    this->setVisible(false);
}

void IDCATC::openCreateAccount(){
    // Se crea y muestra ventana de creacion de usuario.
    Account = new createAccount;
    Account->show();

    // Conexion para el cierre de la ventana del perfil
    connect(Account, &createAccount::closeWindowAccount, this, &IDCATC::closeCreateAccount);

    // Se oculta la ventana de inicio
    this->setVisible(false);
}

void IDCATC::closeCreateAccount(){
    // Se cierra y elimina la ventana de creacion de cuenta
    Account->close();
    delete  Account;

    // Ahora se vuelve a la ventana de inicio
    this->setVisible(true);
}

void IDCATC::closeProfileInterfaz(){
    // Se cierra y elimina la ventana del perfil
    Profile->close();
    delete Profile;

    // Ahora se vuelve a la ventana de inicio
    this->setVisible(true);
}

void IDCATC::on_pB_Login_clicked(){
    //Se resetea la barra de progreso
    ui->Label_Status->clear();

    //Se abre el archivo de usuarios
    ifstream usersFile;
    usersFile.open(PATH_TO_USERS);
    ui->progressBar->setValue(10);

    //Variables temporales para recorrer usuarios en la base de datos de usuarios
    string Username ,Password, Lives, Time, Score;

    /*
     * Banderas booleanas:
     -> FoundUser = Almacena true si se encontro el usuario en el archivo de texto
        De lo contrario, almacena false.
     -> FoundPassword = Almacena true si las contraseñnas coinciden. De lo contrario,
        Almacena false.
    */
    static bool FoundUser = false, FoundPassword = false;

    while(!usersFile.eof()){
        usersFile >> Username >> Password >> Lives >> Time >> Score;

        ui->progressBar->setValue(15);

        if(ui->Text_Username->text().toStdString() == Username){
            //Se encontro el usuario que se ingreso el QLineEdit
            FoundUser = true;

            ui->progressBar->setValue(70);

            //Se procede a verificar que las contraseñas coincidan
            if(ui->Text_Password->text().toStdString() == Password){
                //Creacion del objeto User//
                mUser = new User(Username,Password,stoi(Lives), stoi(Time), stoi(Score));

                ui->progressBar->setValue(100);
                FoundPassword = true;
                break;
            }
        }
    }
    usersFile.close();
    ui->Text_Username->clear();
    ui->Text_Password->clear();

    if(FoundUser == true && FoundPassword == true){
        cout << "Datos correctos :)" << endl;
        FoundPassword = false;
        FoundUser = false;
        openProfileInterfaz();
    }else if(FoundUser == false){
        ui->Label_Status->setText("User not found.");
        FoundPassword = false;
        FoundUser = false;
    }else if(FoundUser == true && FoundPassword == false){
        ui->Label_Status->setText("Passwords do not match.");
        FoundPassword = false;
        FoundUser = false;
    }
}

void IDCATC::on_pB_Multi_clicked(){
    mUser = new User("1","1234",2,0,0);
    mUser2 = new User("2","6789",2,0,0);


    // Hay un cambio de mundo cada 3 minutos (180s)
    // Pero hay un aumento en la dificultad cada 10s
    int timeToChangeWorld = 60; // 60s -> tiempo para cambiar de mundo
    // Para indicar si es multijugador o no
    bool multiPlayer = true;

    Game = new GameWorld(mSpritesWorld, mObjectsValues,
    timeToChangeWorld, multiPlayer,
    mUser, mUser2);

    Game->show();

    connect(Game, &GameWorld::endGame, this, &IDCATC::endGame);

    this->setVisible(false);

}


void IDCATC::endGame()
{
    // Se cierra y elimina la ventana del juego.
    Game->close();
    delete Game;
    this->setVisible(true);
}
