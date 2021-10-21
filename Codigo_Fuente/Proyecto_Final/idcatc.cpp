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

}

IDCATC::~IDCATC(){
    delete ui;
}

void IDCATC::openProfileInterfaz()
{
    // Se crea y muestra ventana del perfil del usuario
    Profile = new ProfileUser(mUsername,mPassword,mLevel,mLives,mScoreFirstLevel,mScoreSecondLevel,mScoreThirdLevel);
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
    string Username ,Password, Level, Lives, ScoreFirstLevel, ScoreSecondLevel, ScoreThirdLevel;

    /*
     * Banderas booleanas:
     -> FoundUser = Almacena true si se encontro el usuario en el archivo de texto
        De lo contrario, almacena false.
     -> FoundPassword = Almacena true si las contraseñnas coinciden. De lo contrario,
        Almacena false.
    */
    static bool FoundUser = false, FoundPassword = false;

    while(!usersFile.eof()){
        usersFile >> Username >> Password >> Level >> Lives >> ScoreFirstLevel >> ScoreSecondLevel >> ScoreThirdLevel;

        /*cout << "Nombre: " << Username << endl;
        cout << "Password: " << Password << endl;
        cout << "Level: " << Level << endl;
        cout << "Lives: " << Lives << endl;
        cout << "Socre 1: " << ScoreFirstLevel << endl;
        cout << "Score 2: " << ScoreSecondLevel << endl;
        cout << "Score 3: " << ScoreThirdLevel << endl << endl;*/

        ui->progressBar->setValue(15);

        if(ui->Text_Username->text().toStdString() == Username){
            //Se encontro el usuario que se ingreso el QLineEdit
            FoundUser = true;

            ui->progressBar->setValue(70);

            //Se procede a verificar que las contraseñas coincidan
            if(ui->Text_Password->text().toStdString() == Password){
                //**Asignacion de atributos de usuarios**//
                mUsername         =              Username;
                mPassword         =              Password;
                mLevel            =           stoi(Level);
                mLives            =           stoi(Lives);
                mScoreFirstLevel  = stoi(ScoreFirstLevel);
                mScoreSecondLevel = stoi(ScoreFirstLevel);
                mScoreThirdLevel  = stoi(ScoreThirdLevel);

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
