#include "gameworld.h"
#include "ui_gameworld.h"

GameWorld::GameWorld(QWidget *parent) :QMainWindow(parent),ui(new Ui::GameWorld){
    ui->setupUi(this);

    // Inicializacion de la escena
    mScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mScene);

    //Inicializacion del personaje principal
    PJ = new Character(0,0,55,18,0.1,"../Proyecto_Final/Sprites/auto1.png");
    mScene->addItem(PJ);

    ui->graphicsView->setScene(mScene);
    ui->graphicsView->show();
}

GameWorld::GameWorld (string &_nameSpBackground, string &_nameSpDecor1, double _wDecor1,
double _hDecor1, string &_nameSpDecor2, double _wDecor2, double _hDecor2,
double _velDecor, int _numMaxDecor, string &_nameSpEnemy, double _wEnemy, double _hEnemy,
double _velEnemy, double _probSpawnEnemy, string &_nameSpObstacle, double _wObstacle,
double _hObstacle, double _velObstacle, double _probSpawnObst, QWidget *parent)
    : QMainWindow(parent),ui(new Ui::GameWorld)
{

    // Inicializacion del constructor sobrecargado, solo un poco sobrecargado...

    // Atributos para las decoraciones
    nameSpDecor1 = _nameSpDecor1;
    wDecor1 = _wDecor1, hDecor1 = _hDecor1;

    nameSpDecor2 = _nameSpDecor2;
    wDecor2 = _wDecor2, hDecor2 = _hDecor2;
    velDecor = _velDecor;
    numMaxDecor = _numMaxDecor;
    // Espacio hábil para poner las decoraciones. Van en la parte superior.
    spaceToPutDecor = (hDecor1 > hDecor2 )? hDecor1*2 + 5 : hDecor2*2 + 5;

    // Atributos para los enemigos
    nameSpEnemy = _nameSpEnemy;
    wEnemiy = _wEnemy, hEnemiy = _hEnemy;
    velEnemy = _velEnemy, probSpawnEnemy = _probSpawnEnemy;

    // Para los obstaculos
    nameSpObstacle = _nameSpObstacle;
    wObstacle = _wObstacle, hObstacle = _hObstacle;
    velObstacle = _velObstacle, probSpawnObst = _probSpawnObst;

    // Dimesiones de la escena
    double widthScene = ui->graphicsView->width();
    double heightScene = ui->graphicsView->height();

    // Para controlar la generacion de objetos
    contTimeToSpawn = 0;
    timeToSpawn = 500; // son milisegundos
    posxSpwanAny = widthScene/2 + 60;

    // Inicializacion de la escena
    mScene = new QGraphicsScene(-widthScene/2, -heightScene, widthScene, heightScene);
    ui->graphicsView->setScene(mScene);

    //Inicializacion del personaje principal
    PJ = new Character(0,0,55,18,0.1,"../Proyecto_Final/Sprites/auto1.png");
    mScene->addItem(PJ);

    // Imagen de fondo
    std::string nameImgBackground = _nameSpBackground;
    QPixmap pixMapBackground(nameImgBackground.c_str());
    pixMapBackground = pixMapBackground.scaled(widthScene, heightScene);
    mScene->addPixmap(pixMapBackground);

    numToTimer = 50;
    mTimer = new QTimer;

    connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
    connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);
    connect(mTimer, &QTimer::timeout, this, &GameWorld::onUptade);

}

void GameWorld::onUptade()
{

    contTimeToSpawn++;
    if (contTimeToSpawn*numToTimer >= timeToSpawn) {
        spawnSceneObject();
        contTimeToSpawn = 0;
        deleteWorldObject();
    }
}


void GameWorld::spawnSceneObject()
{

    // La ultima posicion en y de los obstaculos y autos enemigos.
    // Se usa para evitar que se generen en el mismo lugar y queden pegados
    static int lastPosy = 0;
    srand(time(NULL));

    /// [ GENERACION ALEATORIA DE LOS OBSTACULOS/ENEMIGOS SEGUN UNA PROBABILIDAD ]
    int numRand = rand()%100 + 1; // numero aleatoria entre [1-100]
    int randPosyObjec; // Posicion en y aleatoria de los obstaculos/enemigos

    if (numRand <= probSpawnEnemy) {
        // Se genera un enemigo
    }
    else if (numRand <= probSpawnObst) { // [hObst/2 + 5, heightScene - spaceToPutDecor - hObst/2 ]
        // Esto para el caso en que los objetos se generan casi juntos o juntos
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - hObstacle/2 + 1)) + hObstacle/2 + 5;
        while ((randPosyObjec + hObstacle/2 >= lastPosy) && (randPosyObjec - hObstacle/2 <= lastPosy)) {
            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - hObstacle/2 + 1)) + hObstacle/2 + 5;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;
        // Se crea y agrega un nuevo obstaculo
        mObstaclesWorld.push_back(new Obstacle(posxSpwanAny, -randPosyObjec, wObstacle, hObstacle,
                                               velObstacle, nameSpObstacle));
    }

    /// [ GENERACION ALEATORIA DEL OBJETO DECORATION PARA LA DECORACION DEL JUEGO ]
    int randPosyDecor; // Posicion en Y aleatoria
    int randDecorKind; // Como son dos tipos de decoracion, habrá un 50% de spawn para cada uno
    int hMaxDecor = hDecor1 < hDecor2 ? hDecor2 : hDecor1; // Para delimitar la posicion de spawn

    if (mDecorsWorld.size() < numMaxDecor) {
        // Se genera un nuevo objeto decoracion.
        randDecorKind = rand()%2; // [0,1]
        randPosyDecor = rand()%(int(spaceToPutDecor - hMaxDecor/2 + 1))
                        + heightScene - spaceToPutDecor + hMaxDecor/2;
        // [heightScene - spaceToPutDecor + hMaxDecor/2, heightScene]

        if (randDecorKind == 1) {
            mDecorsWorld.push_back(new Decoration(posxSpwanAny, randPosyDecor, wDecor1, hDecor1,
                                                  velDecor, nameSpDecor1));
        }else {
            mDecorsWorld.push_back(new Decoration(posxSpwanAny, randPosyDecor, wDecor2, hDecor2,
                                                  velDecor, nameSpDecor2));
        }
    }
}

void GameWorld::deleteWorldObject()
{
    int posToDelete = -posxSpwanAny;
    int posObject;

    for (int i = 0; i < mEnemiesWorld.size(); i++) {
        // Eliminacion de enemigos fuera de la escena
    }
    // Eliminacion de los obstaculos que ya estan fuera de la escena
    for (int i = 0; i < mObstaclesWorld.size(); i++) {
        posObject = mObstaclesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {
            mScene->removeItem(mObstaclesWorld.at(i));
            delete mObstaclesWorld.at(i);
            mObstaclesWorld.erase(mObstaclesWorld.begin() + i);
            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    // Eliminacion de las decoraciones que estan fuera de la escena
    for (int i = 0; i < mDecorsWorld.size(); i++) {
        posObject = mDecorsWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {
            mScene->removeItem(mDecorsWorld.at(i));
            delete mDecorsWorld.at(i);
            mDecorsWorld.erase(mDecorsWorld.begin() + i);
            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
}

GameWorld::~GameWorld(){
    delete ui;
}

void GameWorld::keyPressEvent(QKeyEvent *event){
    int posx, posy;
    switch (event->key()) {
    case Qt::Key_A:{
        //Movimiento hacia la derecha, decrece el eje X
        posx = PJ->getPosx();
        PJ->setPosx(posx - 5);
        PJ->changePosition();
        break;
    }
    case Qt::Key_D:{
        //Movimiento hacia la izquierda, crece el eje X
        posx = PJ->getPosx();
        PJ->setPosx(posx + 5);
        PJ->changePosition();
        break;
    }
    case Qt::Key_S:{
        //Movimiento hacia abajo, crece el eje Y
        posy = PJ->getPosy();
        PJ->setPosy(posy + 5);
        PJ->changePosition();
        break;
    }
    case Qt::Key_W:{
        //Movimiento hacia arriba, decrece el eje Y
        posy = PJ->getPosy();
        PJ->setPosy(posy - 5);
        PJ->changePosition();
        break;
    }
    case Qt::Key_Space:{
        //Salto (Movimiento parabolico)
        break;
    }
    }

}

void GameWorld::startQTimer(){
    mTimer->start(numToTimer);
}

