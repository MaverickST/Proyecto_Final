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
    string Username ,Password, Level, Lives, ScoreFirstLevel, ScoreSecondLevel, ScoreThirdLevel;
    while(!usersFile.eof()){
        usersFile >> Username >> Password >> Level >> Lives >> ScoreFirstLevel >> ScoreSecondLevel >> ScoreThirdLevel;
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
    User += "   1   5   0   0   0";
    usersFile.open(PATH_TO_USERS,ios::app);
    usersFile << User;
    usersFile.close();
}

void createAccount::on_PB_Create_clicked(){
    if(ui->Username->text().toStdString() == "" && ui->Password->text().toStdString() == ""){
        ui->Label_Status->setText("You must enter a username and password.");
    }else if(ui->Username->text().toStdString() == ""){
         ui->Label_Status->setText("You must enter a username.");
         ui->Password->clear();
    }else if(ui->Password->text().toStdString() == ""){
        ui->Label_Status->setText("You must enter a password.");
        ui->Username->clear();
    }else{
        bool Existance = CheckingExistence();
        if(Existance == true){
            ui->Label_Status->setText("The user entered already exists.");
        }else if(Existance == false){
            signUp();
            ui->Label_Status->setText("User created successfully.");
        }
        ui->Username->clear();
        ui->Password->clear();
    }
}
