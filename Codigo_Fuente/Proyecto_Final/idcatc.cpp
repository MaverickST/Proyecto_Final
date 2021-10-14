#include "idcatc.h"
#include "ui_idcatc.h"

IDCATC::IDCATC(QWidget *parent): QMainWindow(parent), ui(new Ui::IDCATC){
    ui->setupUi(this);

    // Solo puede iniciar sesion cuando haya ingresado los datos correctamente
    ui->pB_Login->setEnabled(true); // false


    connect(ui->pB_Login, &QPushButton::clicked, this, &IDCATC::openProfileInterfaz);

}

IDCATC::~IDCATC()
{
    delete ui;
}

void IDCATC::openProfileInterfaz()
{
    // Se crea y muestra ventana del perfil del usuario
    Profile = new ProfileUser;
    Profile->show();

    // Conexion para el cierre de la ventana del perfil
    connect(Profile, &ProfileUser::closeWindowProfile, this, &IDCATC::closeProfileInterfaz);

    // Se oculta la ventana de inicio
    this->setVisible(false);
}

void IDCATC::closeProfileInterfaz()
{
    // Se cierra y elimina la ventana del perfil
    Profile->close();
    delete Profile;

    // Ahora se vuelve a la ventana de inicio
    this->setVisible(true);
}

