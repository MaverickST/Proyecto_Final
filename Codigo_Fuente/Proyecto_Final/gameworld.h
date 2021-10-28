#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMainWindow>
#include <QGraphicsItem>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <time.h>
#include <fstream>
#include <qiterator.h>
//#include <QMediaPlayer>

#include "character.h"
#include "obstacle.h"
#include "enemy.h"
#include "decoration.h"
#include "enemy.h"
#include "explosion.h"
#include "gunshot.h"
#include "user.h"
#include "finalboss.h"
#include "popupwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWorld; }
QT_END_NAMESPACE

using namespace std;

class GameWorld : public QMainWindow{
    Q_OBJECT

public:

    explicit GameWorld(QMap<string, string> &_mSpritesWorld,
    QMap<string, double> &_mObjectsValues,
    int _timeToChangeWorld, bool _multiPlayer,
    User *&_User, User *&_User2,
    QWidget *parent = nullptr);


    void spawnSceneObject();
    void deleteWorldObject();
    void moveWorldObjects();

    void collisionEvaluator();
    void createRectsInvisibles();

    bool collisionWithEnemy();
    bool collisionWithObstacle();
    bool collisionWithLimits();

    void assingAttributeValues();
    void changeSprites();
    void increasedDifficulty(bool changeWorld);

    void changeInUsers();

    ~GameWorld();

signals:
    void endGame();

protected:
    void keyPressEvent(QKeyEvent *event);

public slots:
    void startQTimer();
    void onUptade();
    void pressButtonContinue();

private:
    Ui::GameWorld *ui;
    QGraphicsScene *mScene;
    QTimer *mTimer;

    FinalBoss *Boss;

    // Contenedores
    QList<Decoration *> mDecorsWorld; // Decoraciones
    QList<Enemy *> mEnemiesWorld; // Enemigos
    QList<Obstacle *> mObstaclesWorld; // Obstaculos
    QList<Explosion *> mExplosionsWorld; // Explosiones
    QList<GunShot *> mGunShotsWorld; // Disparos
    QVector<QGraphicsRectItem *> mRectsInvisibles; // Bloques delimitadores

    //Objeto user
    User *mUser;
    User *mUser2;

    // En caso de que esté en multijugador, se usa para saber si
    // está jugando el jugador 1 o el jugador 2
    bool mUserOn;

    // Para saber si está o no en multijugador
    bool multiPlayer;

    // Para saber si la ventana emergente está activa
    bool popUpWindowOn;

    // Ventana emergente
    PopUpWindow *puWindow;

    // Contenedores que almaceran todos los datos de los objetos
    // del juego
    QMap<string, string> mSpritesWorld;
    QMap<string, double> mObjectsValues;

    // Para el fondo
    QPixmap pixMapBackground;
    string nameSpBackground;

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
    double velShot, masaShot, timeToShot;
    int contTimeToShot;

    // Para las explosiones
    double wExplosion, hExplosion;

    // Para el boss;
    string nameSpBoss;
    double RBoss, masaBoss;
    double LBoss, tFinalBoss, tToChangePosBoss;

    // Para controlar la generacion de objetos
    int contTimeToSpawn;
    int timeToSpawn;
    int posxSpwanAny; // Posicion en x, no de spawnean los objetos
    int numToTimer; // Define el startTimer.

    // Atributos para el personaje principal
    Character *PJ;
    int contCollisionsWithObstacle;
    int invisibilityTime;

    // Booleanos para las colisiones
    bool beCollides = false;
    bool win        = false;
    bool EnemyCollision;
    bool ObstacleCollision;
    bool LimitsCollision;

    // Contadores del tiempo del juego
    int timeToGame, contTimeToGame;

    // Para el cambio de mundo
    bool partWorld_1;
    int timeToChangeWorld;

};

#endif // GAMEWORLD_H
