#ifndef IDCATC_H
#define IDCATC_H

#include <QMainWindow>
#include <time.h>
#include <fstream>
#include <iostream>
#include <QString>

#include "profileuser.h"
#include "createaccount.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class IDCATC; }
QT_END_NAMESPACE

class IDCATC : public QMainWindow{
    Q_OBJECT

public:
    IDCATC(QWidget *parent = nullptr);
    ~IDCATC();

public slots:
    void openProfileInterfaz();
    void closeProfileInterfaz();
    void openCreateAccount();
    void closeCreateAccount();
private slots:
    void on_pB_Login_clicked();
private:
    Ui::IDCATC *ui;

    ProfileUser *Profile;
    createAccount *Account;

    //Declaracion de atributos de usuarios
    string mUsername         = "";
    string mPassword         = "";
    int    mLevel            =  0;
    int    mLives            =  0;
    int    mScoreFirstLevel  =  0;
    int    mScoreSecondLevel =  0;
    int    mScoreThirdLevel  =  0;
};
#endif // IDCATC_H
