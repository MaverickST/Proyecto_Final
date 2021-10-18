#include "gameworld.h"
#include "ui_gameworld.h"

GameWorld::GameWorld(QWidget *parent) :QMainWindow(parent),ui(new Ui::GameWorld){
    ui->setupUi(this);
}

GameWorld::GameWorld (string &_nameSpBackground, string &_nameSpDecor1, double _wDecor1,
double _hDecor1, string &_nameSpDecor2, double _wDecor2, double _hDecor2,
double _velDecor, int _numMaxDecor, string &_nameSpEnemy, double _wEnemy, double _hEnemy,
double _velEnemy, double _probSpawnEnemy, string &_nameSpObstacle, double _wObstacle,
double _hObstacle, double _velObstacle, double _probSpawnObst, QWidget *parent)
    :QMainWindow(parent),ui(new Ui::GameWorld)
{

    // Inicializacion del constructor sobrecargado, solo un poco sobrecargado...

    // Atributos para las decoraciones
    nameSpDecor1 = _nameSpDecor1;
    wDecor1 = _wDecor1, hDecor1 = _hDecor1;

    nameSpDecor2 = _nameSpDecor2;
    wDecor2 = _wDecor2, hDecor2 = _hDecor2;
    velDecor = _velDecor;
    numMaxDecor = _numMaxDecor;

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

    // Inicializacion de la escena
    mScene = new QGraphicsScene(-widthScene/2, -heightScene/2, widthScene, heightScene);
    ui->graphicsView->setScene(mScene);

    // Imagen de fondo
    std::string nameImgBackground = _nameSpBackground;
    QPixmap pixMapBackground(nameImgBackground.c_str());
    pixMapBackground = pixMapBackground.scaled(widthScene, heightScene);
    mScene->addPixmap(pixMapBackground);

    numToTimer = 50;
    mTimer = new QTimer;

    connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
    connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);


}

GameWorld::~GameWorld()
{
    delete ui;
}

void GameWorld::startQTimer()
{
    mTimer->start(numToTimer);
}
