#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class PopUpWindow;
}

class PopUpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PopUpWindow(QWidget *parent = nullptr);
    ~PopUpWindow();

    void showInfoUser(User *&User);

signals:
    void pressButtonPopUpW();

private:
    Ui::PopUpWindow *ui;
};

#endif // POPUPWINDOW_H
