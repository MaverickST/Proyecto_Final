#ifndef IDCATC_H
#define IDCATC_H

#include <QMainWindow>
#include <time.h>

#include "profileuser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IDCATC; }
QT_END_NAMESPACE

class IDCATC : public QMainWindow
{
    Q_OBJECT

public:
    IDCATC(QWidget *parent = nullptr);
    ~IDCATC();

public slots:
    void openProfileInterfaz();
    void closeProfileInterfaz();

private:
    Ui::IDCATC *ui;

    ProfileUser *Profile;
};
#endif // IDCATC_H
