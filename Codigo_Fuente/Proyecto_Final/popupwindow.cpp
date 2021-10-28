#include "popupwindow.h"
#include "ui_popupwindow.h"

PopUpWindow::PopUpWindow( QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PopUpWindow)
{
    ui->setupUi(this);

    connect(ui->pB_Continue, &QPushButton::clicked, this, &PopUpWindow::close);
    connect(ui->pB_Continue, &QPushButton::clicked, this, &PopUpWindow::pressButtosPopUpW);

}

PopUpWindow::~PopUpWindow()
{
    delete ui;
}

void PopUpWindow::showInfoUser(User *&User)
{

    ui->lb_numPJ->setText((User->username()).c_str());
    ui->lcd_scorePJ->display(User->score());
    ui->lcd_timePJ->display(User->time());
}
