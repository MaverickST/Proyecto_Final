#include "createaccount.h"
#include "ui_createaccount.h"

#define PATH_TO_USERS "../Proyecto_Final/Users/Users.txt"

createAccount::createAccount(QWidget *parent) :QMainWindow(parent), ui(new Ui::createAccount){
    ui->setupUi(this);
    connect(ui->PB_Exit, &QPushButton::clicked, this, &createAccount::closeWindowAccount);
}

createAccount::~createAccount(){
    delete ui;
}

bool createAccount::CheckingExistence(){
    ifstream usersFile;
    usersFile.open(PATH_TO_USERS);
    string Username ,Password, Lives, Time, Score;
    while(!usersFile.eof()){
        usersFile >> Username >> Password >> Lives >> Time >> Score;
        if(ui->Username->text().toStdString() == Username){
            return true;
        }
    }
    usersFile.close();
    return false;
}

void createAccount::signUp(){
    ofstream usersFile;
    string User = "\n";
    User += ui->Username->text().toStdString();
    User += "   ";
    User += ui->Password->text().toStdString();
    User += "   5   0   0";
    usersFile.open(PATH_TO_USERS,ios::app);
    usersFile << User;
    usersFile.close();
}

void createAccount::on_PB_Create_clicked(){
    if(ui->Username->text().toStdString() == ""
            || ui->Password->text().toStdString() == ""
            || ui->ConfirmPassword->text().toStdString() == ""){
        ui->Label_Status->setText("Be sure to fill in all the fields.");

        //Se limpian los LineEdit
        ui->Username->clear();
        ui->Password->clear();
        ui->ConfirmPassword->clear();
    }else{
        bool Existance = CheckingExistence();
        if(Existance == true){
            ui->Label_Status->setText("The user entered already exists.");
            ui->Username->clear();
            ui->Password->clear();
            ui->ConfirmPassword->clear();
        }else if(Existance == false){
            if(ui->Password->text() == ui->ConfirmPassword->text()){
                signUp();
                ui->Label_Status->setText("User created successfully.");
                ui->Username->clear();
                ui->Password->clear();
                ui->ConfirmPassword->clear();
            }else{
                ui->Label_Status->setText("Passwords entered do not match.");
                ui->Password->clear();
                ui->ConfirmPassword->clear();
            }
        }
    }
}
