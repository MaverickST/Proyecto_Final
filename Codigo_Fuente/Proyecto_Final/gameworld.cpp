#include "gameworld.h"
#include "ui_gameworld.h"

//GameWorld::GameWorld(QWidget *parent) :QMainWindow(parent),ui(new Ui::GameWorld){
//    ui->setupUi(this);

//    // Inicializacion de la escena
//    mScene = new QGraphicsScene(this);
//    ui->graphicsView->setScene(mScene);

//    //Inicializacion del personaje principal
//    //PJ = new Character(0,0,55,18,0.1,"../Proyecto_Final/Sprites/auto1.png");
//    std::string sprite = "../Proyecto_Final/Sprites/auto1.png";
//    PJ = new Character (0,0,55,18,30.0f,sprite);
//    mScene->addItem(PJ);

//    ui->graphicsView->setScene(mScene);
//    ui->graphicsView->show();

//    numToTimer = 50;
//    mTimer = new QTimer;
//    mTimer->start(50);

//    //connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
//    //connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);
//    connect(mTimer, &QTimer::timeout, this, &GameWorld::onUptade);
//}

GameWorld::GameWorld (string &_nameSpBackground, string &_nameSpDecor1, double _wDecor1,
double _hDecor1, string &_nameSpDecor2, double _wDecor2, double _hDecor2,
double _velDecor, int _numMaxDecor, string &_nameSpEnemy, double _wEnemy, double _hEnemy,
double _velEnemy, double _probSpawnEnemy, string &_nameSpObstacle, double _wObstacle,
double _hObstacle, double _velObstacle, double _probSpawnObst, QWidget *parent)
    : QMainWindow(parent),ui(new Ui::GameWorld)
{
    ui->setupUi(this);
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
    wEnemy = _wEnemy, hEnemy = _hEnemy;
    velEnemy = _velEnemy, probSpawnEnemy = _probSpawnEnemy;

    // Para los obstaculos
    nameSpObstacle = _nameSpObstacle;
    wObstacle = _wObstacle, hObstacle = _hObstacle;
    velObstacle = _velObstacle, probSpawnObst = _probSpawnObst;

    // Dimesiones de la escena
    widthScene = ui->graphicsView->width() - 10;
    heightScene = ui->graphicsView->height() - 10;

    // Para controlar la generacion de objetos
    contTimeToSpawn = 0;
    timeToSpawn = 200; // son milisegundos
    posxSpwanAny = widthScene + 60;

    // Inicializacion de la escena
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, widthScene, heightScene);
    ui->graphicsView->setScene(mScene);

//    mScene = new QGraphicsScene(this);
//    mScene->setSceneRect(0,0,anchoScene,largoScene);
//    ui->graphicsView->setScene(mScene);

    // Imagen de fondo
    std::string nameImgBackground = _nameSpBackground;
    QPixmap pixMapBackground(nameImgBackground.c_str());
    pixMapBackground = pixMapBackground.scaled(widthScene, heightScene);
//    mScene->addPixmap(pixMapBackground);

    numToTimer = 20;
    mTimer = new QTimer;
    srand(time(NULL));

    connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
    connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);
    connect(mTimer, &QTimer::timeout, this, &GameWorld::onUptade);

}

bool GameWorld::collisionWithEnemy(){
    for(auto i = mEnemiesWorld.begin(); i != mEnemiesWorld.end(); i++){
        /*if(PJ->collidesWithItem(*i)){
            cout << "Colision con " << *i << endl;
            return true;
        }*/
    }
    return false;
}

bool GameWorld::collisioWithObstacle(){
    for(auto i = mObstaclesWorld.begin(); i != mObstaclesWorld.end(); i++){
        if(PJ->collidesWithItem(*i)){
            cout << "Colision con " << *i << endl;
            return true;
        }
    }

    return false;
}

void GameWorld::onUptade(){

//    Salto con movimiento parabolico
//    if(PJ->getJump() == true){
//        PJ->parabolicMovement(0.1f);
//        beCollides = false;
//    }

//    Evaluacion de colisiones
//    bool Enemy = collisionWithEnemy();
//    bool Obstacle = collisioWithObstacle();

//    if(Enemy == true || Obstacle == true){
//        //Se detecto una colision
//        beCollides = true;
//    }else{
//        beCollides = false;
//    }

    contTimeToSpawn++;
    if (contTimeToSpawn*numToTimer >= timeToSpawn) {
        spawnSceneObject();
        contTimeToSpawn = 0;
        deleteWorldObject();
    }
    // Se mueven todos los objetos de la escena
    moveWorldObjects();
}

void GameWorld::spawnSceneObject(){

    // La ultima posicion en y de los obstaculos y autos enemigos.
    // Se usa para evitar que se generen en el mismo lugar y queden pegados
    static int lastPosy = 0;

    /// [ GENERACION ALEATORIA DE LOS OBSTACULOS/ENEMIGOS SEGUN UNA PROBABILIDAD ]
    int numRand = rand()%500 + 1; // numero aleatoria entre [1-100]
    int randPosyObjec; // Posicion en Y aleatoria de los obstaculos/enemigos

//    qDebug() << "Numero rand: " << numRand;
    if (numRand <= probSpawnEnemy) { // Se genera un enemigo

        // [spaceToPutDecor + hEnemy/2, heightScene - hEnemy] -> Numero aleatoria en este intervalo
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 3*hEnemy/2 + 1))
                + spaceToPutDecor + hEnemy/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hEnemy/2 >= lastPosy) && (randPosyObjec - hEnemy/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 3*hEnemy/2 + 1))
                    + spaceToPutDecor + hEnemy/2;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;

        // Se crea y agrega un nuevo enemigo
        Enemy *newEnemy = new Enemy(posxSpwanAny, randPosyObjec, wEnemy, hEnemy, velEnemy, nameSpEnemy);
        mEnemiesWorld.push_back(newEnemy);
        mScene->addItem(newEnemy);
//        qDebug() << "Agrega enemigo en : " << lastPosy << " "<<__LINE__;
    }
    else if (numRand <= probSpawnObst) { // Se genera un obstaculo

        // [spaceToPutDecor + hObst/2, heightScene - hObst] -> Numero aleatoria en este intervalo
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 3*hObstacle/2 + 1))
                + spaceToPutDecor + hObstacle/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hObstacle/2 >= lastPosy) && (randPosyObjec - hObstacle/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 3*hObstacle/2 + 1))
                    + spaceToPutDecor + hObstacle/2;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;

        // Se crea y agrega un nuevo obstaculo
        Obstacle *newObst = new Obstacle(posxSpwanAny, randPosyObjec, wObstacle, hObstacle,
                                         velObstacle, nameSpObstacle);
        mObstaclesWorld.push_back(newObst);
        mScene->addItem(newObst);
//        qDebug() << "Agrega obstaculo en : "<< lastPosy << " "<<__LINE__;
    }

    /// [ GENERACION ALEATORIA DEL OBJETO DECORATION PARA LA DECORACION DEL JUEGO ]
    int randPosyDecor; // Posicion en Y aleatoria
    int randDecorKind; // Como son dos tipos de decoracion, habrá un 50% de spawn para cada uno
    int hMaxDecor = hDecor1 > hDecor2 ? hDecor1 : hDecor2; // Para delimitar la posicion de spawn

    if (mDecorsWorld.size() < numMaxDecor) { // Se genera un nuevo objeto decoracion.

        // [0, spaceToPutDecor - hMaxDecor/2] -> Numero aleatorio en este intervalo
        randPosyDecor = rand()%(int(spaceToPutDecor - hMaxDecor/2 + 1));

        randDecorKind = rand()%2; // [0,1]
        Decoration *newDecor;
        if (randDecorKind == 1) { // Decoracion tipo uno
            newDecor = new Decoration(posxSpwanAny, randPosyDecor, wDecor1, hDecor1,
                                      velDecor, nameSpDecor1);
            mDecorsWorld.push_back(newDecor);
        }else { // Decoracion tipo 2
            newDecor = new Decoration(posxSpwanAny, randPosyDecor, wDecor2, hDecor2,
                                      velDecor, nameSpDecor2);
            mDecorsWorld.push_back(newDecor);
        }
        mScene->addItem(newDecor);
//        qDebug() << "Agrega decoracion en : "<< randPosyDecor << " " <<__LINE__;
    }
}

void GameWorld::deleteWorldObject()
{
    // Posicion en X de la escena, a partir de la cual se eliminan los objetos
    int posToDelete = -posxSpwanAny;
    int posObject;

    // Eliminacion de enemigos fuera de la escena
    for (int i = 0; i < mEnemiesWorld.size(); i++) {

        posObject = mEnemiesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mEnemiesWorld.at(i));
            delete mEnemiesWorld.at(i);
            mEnemiesWorld.erase(mEnemiesWorld.begin() + i);
//            qDebug() << "Elimina Enemigo" <<__LINE__;
            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    // Eliminacion de los obstaculos que ya estan fuera de la escena
    for (int i = 0; i < mObstaclesWorld.size(); i++) {

        posObject = mObstaclesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mObstaclesWorld.at(i));
            delete mObstaclesWorld.at(i);
            mObstaclesWorld.erase(mObstaclesWorld.begin() + i);
            qDebug() << "Elimina obstacles" <<__LINE__;
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
            qDebug() << "Elimina decors" <<__LINE__;
            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    qDebug() << "Aqui no" <<__LINE__;
}

void GameWorld::moveWorldObjects()
{
    // La funcion se encarga de ejecutar el metodo: moveObject.
    // Tal metodo mueve al objeto en cuestion segun su propia velocidad

    // Se mueven las decoraciones
    for (int i = 0; i < mDecorsWorld.size(); i++) {
        mDecorsWorld.at(i)->moveObject();
    }
    // Se mueven los enemigos
    for (int i = 0; i < mEnemiesWorld.size(); i++) {
        mEnemiesWorld.at(i)->moveEnemy();
    }
    // Se mueven los obstaculos
    for (int i = 0; i < mObstaclesWorld.size(); i++) {
        mObstaclesWorld.at(i)->moveObject();
    }
}

GameWorld::~GameWorld(){
    delete ui;
}

void GameWorld::keyPressEvent(QKeyEvent *event){
//    if(event->key() == Qt::Key_Space){
//        PJ->setJump(true);
//    }else if(!beCollides && (PJ->getJump() == false)){
//        PJ->moveCharacter(event->key());
//    }
}

void GameWorld::startQTimer(){
    mTimer->start(numToTimer);
}

