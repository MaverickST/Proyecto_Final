#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QMainWindow>
#include <fstream>
#include <iostream>

using namespace std;

namespace Ui {
class createAccount;
}

class createAccount : public QMainWindow{
    Q_OBJECT

public:
    explicit createAccount(QWidget *parent = nullptr);
    ~createAccount();
    bool CheckingExistence();
    void signUp();
signals:
    void closeWindowAccount();

private slots:
    void on_PB_Create_clicked();

private:
    Ui::createAccount *ui;
};

#endif // CREATEACCOUNT_H
