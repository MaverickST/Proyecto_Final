#ifndef IDCATC_H
#define IDCATC_H

#include <QMainWindow>
#include <time.h>
#include <fstream>
#include <iostream>
#include <QString>

#include "profileuser.h"
#include "createaccount.h"
#include "user.h"

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
    void on_pB_Multi_clicked();

private:
    Ui::IDCATC *ui;

    ProfileUser *Profile;
    createAccount *Account;
    User *mUser;
};
#endif // IDCATC_H
