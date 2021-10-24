#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <time.h>

#include "character.h"
#include "obstacle.h"
#include "enemy.h"
#include "decoration.h"
#include "enemy.h"
#include "explosion.h"
#include "gunshot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWorld; }
QT_END_NAMESPACE

using namespace std;

class GameWorld : public QMainWindow
{
    Q_OBJECT

public:
//    explicit GameWorld(QWidget *parent = nullptr);

    explicit GameWorld(string &_nameSpBackground,
    string &_nameSpDecor1, double _wDecor1, double _hDecor1,
    string &_nameSpDecor2, double _wDecor2, double _hDecor2,
    double _velDecor, double _probSpawnDecor,
    string &_nameSpEnemy, double _wEnemy, double _hEnemy,
    double _velEnemy, double _masaEnemy, double _probSpawnEnemy,
    string &_nameSpObstacle, double _wObstacle, double _hObstacle,
    double _velObstacle, double _probSpawnObst,
    string &_nameSpShot, double _wShot, double _hShot,
    double _velShot, double _masaShot, double _millisecondsToShot,
    QWidget *parent = nullptr);


    void spawnSceneObject();
    void deleteWorldObject();
    void moveWorldObjects();

    bool collisionWithEnemy();
    bool collisioWithObstacle();

    ~GameWorld();

signals:
    void endGame();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void startQTimer();
    void onUptade();


private:
    Ui::GameWorld *ui;
    QGraphicsScene *mScene;
    QTimer *mTimer;

    // Contenedores
    QList<Decoration *> mDecorsWorld;
    QList<Enemy *> mEnemiesWorld;
    QList<Obstacle *> mObstaclesWorld;
    QList<Explosion *> mExplosionsWorld;
    QList<GunShot *> mGunShotsWorld;

    // Dimesiones de la escena
    double widthScene;
    double heightScene;

    // Atributos para las decoraciones
    string nameSpDecor1;
    double wDecor1, hDecor1;

    string nameSpDecor2;
    double wDecor2, hDecor2;
    double velDecor;
    int probSpawnDecor;
    double spaceToPutDecor;

    // Atributos para los enemigos
    string nameSpEnemy;
    double wEnemy, hEnemy;
    double velEnemy, probSpawnEnemy;
    double masaEnemy;

    // Para los obstaculos
    string nameSpObstacle;
    double wObstacle, hObstacle;
    double velObstacle, probSpawnObst;

    // Para los disparos
    string nameSpShot;
    double wShot, hShot;
    double velShot, masaShot, millisecondsToShot;


    // Para controlar la generacion de objetos
    int contTimeToSpawn;
    int timeToSpawn;
    int posxSpwanAny; // Posicion en x, no de spawnean los objetos
    int numToTimer; // Define el startTimer.

    //Atributos para el personaje principal
    Character *PJ;

    bool beCollides = false;
//    string &_nameSpBackground, string &_nameSpDecor1, double _wDecor1, double _hDecor1,
//    string &_nameSpDecor2, double _wDecor2, double _hDecor2, double _velDecor, int _numMaxDecor,
//    string &_nameSpEnemy, double _wEnemy, double _hEnemy, double _velEnemy, double _probSpawnEnemy,
//    string &_nameSpObstacle, double _wObstacle, double _hObstacle, double _velObstacle,
//    double _probSpawnObst



};

#endif // GAMEWORLD_H
