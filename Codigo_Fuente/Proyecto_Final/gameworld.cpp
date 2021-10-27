#include "gameworld.h"
#include "ui_gameworld.h"

GameWorld::GameWorld(string &_nameSpBackground,
    string &_nameSpDecor1, double _wDecor1, double _hDecor1,
    string &_nameSpDecor2, double _wDecor2, double _hDecor2,
    double _velDecor, double _probSpawnDecor,
    string &_nameSpEnemy, double _wEnemy, double _hEnemy,
    double _velEnemy, double _masaEnemy, double _probSpawnEnemy,
    string &_nameSpObstacle, double _wObstacle, double _hObstacle,
    double _velObstacle, double _probSpawnObst,
    string &_nameSpShot, double _wShot, double _hShot,
    double _velShot, double _masaShot, double _millisecondsToShot,
    double _wExplosion, double _hExplosion,
    string _nameSpBoss, double _RBoss, double _masaBoss, double _LBoss, double _tFinalBoss,
    User *&_User,
    QWidget *parent)
    : QMainWindow(parent),ui(new Ui::GameWorld)
{
ui->setupUi(this);
    // Inicializacion del constructor sobrecargado, solo un poco sobrecargado...

    // Dimesiones de la escena
    widthScene = ui->graphicsView->width() - 5;
    heightScene = ui->graphicsView->height() - 5;

    // Inicializacion de la escena
    mScene = new QGraphicsScene(this);
    mScene->setSceneRect(0, 0, widthScene, heightScene);
    ui->graphicsView->setScene(mScene);

    //Inicualizacion objeto User
    mUser = _User;

    // Atributos para las decoraciones
    nameSpDecor1 = _nameSpDecor1;
    wDecor1 = _wDecor1, hDecor1 = _hDecor1;

    nameSpDecor2 = _nameSpDecor2;
    wDecor2 = _wDecor2, hDecor2 = _hDecor2;
    velDecor = _velDecor;
    probSpawnDecor = _probSpawnDecor;
    // Espacio hábil para poner las decoraciones. Van en la parte superior.
    spaceToPutDecor = (hDecor1 > hDecor2 )? hDecor1*2 + 5 : hDecor2*2 + 5;

    // Atributos para los enemigos
    nameSpEnemy = _nameSpEnemy;
    wEnemy = _wEnemy, hEnemy = _hEnemy;
    velEnemy = _velEnemy, probSpawnEnemy = _probSpawnEnemy;
    masaEnemy = _masaEnemy;

    // Para los obstaculos
    nameSpObstacle = _nameSpObstacle;
    wObstacle = _wObstacle, hObstacle = _hObstacle;
    velObstacle = _velObstacle, probSpawnObst = _probSpawnObst;

    // Para los disparos
    nameSpShot = _nameSpShot;
    wShot = _wShot, hShot = _hShot;
    velShot = _velShot, masaShot = _masaShot, millisecondsToShot = _millisecondsToShot;

    // Para las explosiones
    wExplosion = _wExplosion, hExplosion = _hExplosion;

    // Para el boss
    nameSpBoss = _nameSpBoss;
    RBoss = _RBoss, masaBoss = _masaBoss;
    LBoss = _LBoss, tFinalBoss = _tFinalBoss;

    // Para controlar la generacion de objetos
    contTimeToSpawn = 0;
    timeToSpawn = 200; // son milisegundos
    posxSpwanAny = widthScene + 60;

    timeToGame = 0, contTimeToGame = 0;

    // Imagen de fondo
    std::string nameImgBackground = _nameSpBackground;
    QPixmap pixMapBackground(nameImgBackground.c_str());
    pixMapBackground = pixMapBackground.scaled(widthScene, heightScene);
    mScene->addPixmap(pixMapBackground);

    // Se crean rectangulos alrededor del mapa
    createRectsInvisibles();

    //Inicializacion del personaje principal
    std::string sprite = "../Proyecto_Final/Sprites/auto1.png";
    PJ = new Character ((50+20)/2,(heightScene - spaceToPutDecor)/2,50,30,60.0f,sprite);
    mScene->addItem(PJ);

    contCollisionsWithObstacle = 0;
    invisibilityTime = 0;

    // Creacion de un boss para pruebas
    // (double _R, double _masa, double _L, double _tFinal, bool _level1)
    boss = new FinalBoss(RBoss, masaBoss, LBoss, tFinalBoss, true, nameSpEnemy,
                         widthScene, heightScene - hEnemy, spaceToPutDecor + hEnemy);
    mScene->addItem(boss);

    numToTimer = 20;
    mTimer = new QTimer;
    srand(time(NULL));

    ui->LCD_LIVES->display(mUser->lives());
    ui->LCD_TIME->display(timeToGame);
    ui->LCD_SCORE->display(0);

    connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
    connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);
    connect(mTimer, &QTimer::timeout, this, &GameWorld::onUptade);
}

void GameWorld::collisionEvaluator(){
    //Se evalua colision con enemigos, limites y obstaculos

    EnemyCollision = collisionWithEnemy();
    ObstacleCollision = collisionWithObstacle();
    LimitsCollision = collisionWithLimits();

    // Colision jefe final
    // Invensibilidad
    // Adaptarlo infinito

    /**    EVALUACION DE COLISIONES     **/
    if (PJ2 != nullptr) {

    }
    if(PJ->getJump() == false && invisibilityTime == 0){//Otra consision para evaluar colisiones es el tiempo de invensibilidad

        //Solo se va a evaluar colisiones cuando el personaje no este saltando
        if(EnemyCollision || ObstacleCollision || LimitsCollision){
            cout << "Enemy: " << EnemyCollision << endl;
            cout << "Obstacle: " << ObstacleCollision << endl;
            cout << "Limits: " << LimitsCollision << endl;

            if(LimitsCollision){
                //Hubo colision con los bloques invisibles, se devuelve al PJ
                if(PJ->getLastKey() == Qt::Key_A){
                    PJ->setPosx(PJ->getPosx() + 5);
                }else if(PJ->getLastKey() == Qt::Key_D){
                    PJ->setPosx(PJ->getPosx() - 5);
                }else if(PJ->getLastKey() == Qt::Key_S){
                    PJ->setPosy(PJ->getPosy() - 5);
                }else if(PJ->getLastKey() == Qt::Key_W){
                    PJ->setPosy(PJ->getPosy() + 5);
                }
                PJ->setPosition();
                beCollides = true;
            }
            if(ObstacleCollision){
                //Hubo colision con un obstaculo
                contCollisionsWithObstacle++;
                if(contCollisionsWithObstacle == 2){
                    //Se resta vida solo cuando colisiona dos veces contra un obstaculo
                    mUser->setLives(mUser->lives() - 1);
                    ui->LCD_LIVES->display(mUser->lives());
                    Explosion *e = new Explosion((PJ)->getPosx(), (PJ)->getPosy(), wExplosion, hExplosion);
                    mScene->addItem(e);
                    mExplosionsWorld.push_back(e);
                    contCollisionsWithObstacle = 0;
                }
                PJ->setPosy((heightScene - spaceToPutDecor)/2);
                PJ->setPosx((50+20)/2);
                PJ->setPosition();
                invisibilityTime = 5;
                beCollides = false;
            }
            if(EnemyCollision){
                //Hubo colision con un enemigo
                //Se resta vida
                mUser->setLives(mUser->lives()-1);
                ui->LCD_LIVES->display(mUser->lives());
                Explosion *e = new Explosion((PJ)->getPosx(), (PJ)->getPosy(), wExplosion, hExplosion);
                mScene->addItem(e);
                mExplosionsWorld.push_back(e);
                PJ->setPosy((heightScene - spaceToPutDecor)/2);
                PJ->setPosx((50+20)/2);
                PJ->setPosition();
                invisibilityTime = 5;
                beCollides = false;
            }           
        }else{
            beCollides = false;
        }
    }
    /** FIN DE EVALUACION DE COLISIONES **/

    // Se evalua la colision de un disparo
    for (int i = 0; i < mGunShotsWorld.size(); i++) {
        // Se evalua con los autos enemigos
        for (QList<Enemy *>::iterator it2 = mEnemiesWorld.begin();
             it2 != mEnemiesWorld.end(); it2++) {

            if (mGunShotsWorld.at(i)->collidesWithItem(*it2)) {

                // Se aplica modelo fisico
                // Conservacion del momentum en una colision plástica
                double newVel;
                newVel = (masaEnemy*(*it2)->getVel() + masaShot*velShot)/(masaEnemy + masaShot);
                (*it2)->setIsColliding(true); // Hay un cambio de estado
                (*it2)->setVel(newVel); // Se le asigna una nueva velocidad

                // Se elimina la bala que colisionó con el enemigo
                mScene->removeItem(mGunShotsWorld.at(i));
                delete mGunShotsWorld.at(i);
                mGunShotsWorld.erase(mGunShotsWorld.begin() + i);
                break;
            }
        }
    }
}

bool GameWorld::collisionWithEnemy(){

    for(auto i = mEnemiesWorld.begin(); i != mEnemiesWorld.end(); i++){
        if(PJ->collidesWithItem(*i)){
            return true;
        }
    }
    return false;
}

bool GameWorld::collisionWithObstacle(){

    for(auto it = mObstaclesWorld.begin(); it != mObstaclesWorld.end(); it++){
        if(PJ->collidesWithItem(*it)){
            return true;
        }
    }
    return false;
}

bool GameWorld::collisionWithLimits(){

    for(auto i = mRectsInvisibles.begin(); i != mRectsInvisibles.end(); i++){       
        if(PJ->collidesWithItem(*i)){
            return true;
        }
    }
    return false;
}

void GameWorld::onUptade(){

    boss->moveBoss(numToTimer);
    //Evaluacion de condicion de Game Over
    if(mUser->lives() == 0){
        //El personaje principal se ha quedado sin vidas
        //GameWorld::endGame();
    }

    collisionEvaluator();

    if(PJ->getJump() == true){
        PJ->parabolicMovement(0.1f);
    }
    contTimeToGame++;
    //MANEJO DEL TIEMPO DE INVENSIBILIDAD
    if(contTimeToGame*numToTimer >= 1000){
        invisibilityTime--;//Se resta cada 1s
    }

    //MANEJO DEL TIEMPO RECORRIDO HASTA EL MOMENTO
    // Está hecho para que cambie cada segundo
    if(contTimeToGame*numToTimer >= 1000){
        ui->LCD_TIME->display(timeToGame++);
        contTimeToGame = 0;//Se reseta la variable contTimeEndG
    }
  
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

    int numRand = rand()%1000 + 1; // numero aleatoria entre [1-1000]
    int randPosyObjec; // Posicion en Y aleatoria de los obstaculos/enemigos

//    qDebug() << "Numero rand: " << numRand;
    if (numRand <= probSpawnEnemy) { // Se genera un enemigo

        // Numero aleatoria en este intervalo
        // [spaceToPutDecor + hEnemy/2, heightScene - 3*hEnemy/2]
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 5*hEnemy/2 + 1))
                + spaceToPutDecor + hEnemy/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hEnemy/2 >= lastPosy) && (randPosyObjec - hEnemy/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 5*hEnemy/2 + 1))
                    + spaceToPutDecor + hEnemy/2;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;

        // Se crea y agrega un nuevo enemigo
        Enemy *newEnemy = new Enemy(posxSpwanAny, randPosyObjec, wEnemy, hEnemy,
                                    velEnemy, masaEnemy, nameSpEnemy);
        mEnemiesWorld.push_back(newEnemy);
        mScene->addItem(newEnemy);
//        qDebug() << "Agrega enemigo en : " << lastPosy << " "<<__LINE__;
    }
    else if (numRand <= probSpawnObst) { // Se genera un obstaculo

        // [spaceToPutDecor + hObst/2, heightScene - 3*hObst/2] -> Numero aleatoria en este intervalo
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 5*hObstacle/2 + 1))
                + spaceToPutDecor + hObstacle/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hObstacle/2 >= lastPosy) &&
               (randPosyObjec - hObstacle/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 5*hObstacle/2 + 1))
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
    // Para delimitar la posicion de spawn
    int hMaxDecor = hDecor1 > hDecor2 ? hDecor1 : hDecor2;
    int randPutDecor = rand()%1000 + 1; // [1, 1000]

    if (randPutDecor < probSpawnDecor) { // Se genera un nuevo objeto decoracion.

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

        // Se eliminan los que estan fuera de la escena
        posObject = mEnemiesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mEnemiesWorld.at(i));
            delete mEnemiesWorld.at(i);
            mEnemiesWorld.erase(mEnemiesWorld.begin() + i);
//            break; // Que solo se elimine uno en cada ejecucion.
        }
        // Se eliminan los que fueron impactados por un disparo
        // y, cumplido el tiempo para la explosion, se destruye
        // dejando en su sitio una explosion
        double timeToExplEnemy = mEnemiesWorld.at(i)->getTimeMillisecondsToExpl();
        int contTimeToExplEnemy = mEnemiesWorld.at(i)->getContTimeToExpl();

        if (contTimeToExplEnemy*numToTimer >= timeToExplEnemy) {

            // En la posicion del auto, se genera una explosion.
            double posxEnemy = mEnemiesWorld.at(i)->getPosx();
            double posyEnemy = mEnemiesWorld.at(i)->getPosy();

            Explosion *newExplosion = new Explosion(posxEnemy, posyEnemy,
                                                    wExplosion, hExplosion);
            mScene->addItem(newExplosion);
            mExplosionsWorld.push_back(newExplosion);
            cout << "Se agrega explosion en enemigo: " << __LINE__ << endl;

            // Se elimina el enemigo
            mScene->removeItem(mEnemiesWorld.at(i));
            delete mEnemiesWorld.at(i);
            mEnemiesWorld.erase(mEnemiesWorld.begin() + i);
        }
    }
    // Eliminacion de los obstaculos que ya estan fuera de la escena
    for (int i = 0; i < mObstaclesWorld.size(); i++) {

        posObject = mObstaclesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mObstaclesWorld.at(i));
            delete mObstaclesWorld.at(i);
            mObstaclesWorld.erase(mObstaclesWorld.begin() + i);
//            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    // Eliminacion de las decoraciones que estan fuera de la escena
    for (int i = 0; i < mDecorsWorld.size(); i++) {

        posObject = mDecorsWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mDecorsWorld.at(i));
            delete mDecorsWorld.at(i);
            mDecorsWorld.erase(mDecorsWorld.begin() + i);
//            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    // Eliminacion de las explosiones
    for (int i = 0; i < mExplosionsWorld.size(); i++) {

        // Se verifica que la explosion terminó
        if (mExplosionsWorld.at(i)->getEndExplosion()) {

            mScene->removeItem(mExplosionsWorld.at(i));
            delete mExplosionsWorld.at(i);
            mExplosionsWorld.erase(mExplosionsWorld.begin() + i);
//            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
    // Eliminacion de las balas
    for (int i = 0; i < mGunShotsWorld.size(); i++) {

        posObject = mGunShotsWorld.at(i)->getPosx();
        // Que haya salido de la escena
        if ((posObject <= posToDelete) || (posObject >= posxSpwanAny)) {

            mScene->removeItem(mGunShotsWorld.at(i));
            delete mGunShotsWorld.at(i);
            mGunShotsWorld.erase(mGunShotsWorld.begin() + i);
//            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
}

void GameWorld::moveWorldObjects(){
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
    // Animacion de la explosion
    for (int i = 0; i < mExplosionsWorld.size(); i++) {
        mExplosionsWorld.at(i)->moveExplosion();
    }
    // Las balas
    for (int i = 0; i < mGunShotsWorld.size(); i++) {
        mGunShotsWorld.at(i)->moveObject();
    }
}

void GameWorld::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_B){
        ///**************EL PERSONAJE PRINCIPAL DISPARA***************///
        GunShot *bullet;

        bullet = new GunShot(PJ->getPosx()+5,PJ->getPosy(),wShot,hShot,velShot,masaShot,nameSpShot);
        mScene->addItem(bullet);
        mGunShotsWorld.push_back(bullet);

    }else if(event->key() == Qt::Key_J && (PJ->getJump() == false)){
        ///**********************SALTO DEL PERSONAJE**********************///
        ///Tecla que realiza el salto (Movimiento Parabolico) del personaje
        ///Mientras el persoanje se encuentre en dicho movimiento, no se
        ///podra Mover hacia otras direcciones ni tampoco realizar otro salto

        //Se envia true al atributo privado del objeto Character
        //Para indicar que hay un salto en ejecucion
        PJ->setJump(true);

        //Se resetea la velocidad inicial
        PJ->calculateInitialVelocity();
    }else if(!beCollides && (PJ->getJump() == false)){
        PJ->moveCharacter(event->key());
    }
}

void GameWorld::startQTimer(){
    mTimer->start(numToTimer);
}


GameWorld::~GameWorld(){
    delete ui;
}

void GameWorld::createRectsInvisibles(){

    // La funcion se encarga de crear un rectangulos pequeños invisibles
    // que limitarán el desplazamiento del usuario
    // Esto para que no salga de la escena

    // [spaceToPutDecor + hObst/2, heightScene - 3*hObst/2]
    QGraphicsRectItem *rec;
    QPen penRect(Qt::transparent, 3, Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
    QColor colorRect(Qt::transparent);

    // Que sean pequeños para que no reduzcan mucho el espacio
    int wRects = 5;
    int hRects = 5;

    // Se obtiene la cantidad de rects a poner en base al tamaño de la escena
    int numRectsW = widthScene/wRects + 1;
    int numRectsH = (heightScene - spaceToPutDecor - 5)/hRects ;

    for (int i = 0; i < numRectsH; i++) {
        for (int j = 0; j < numRectsW; j++) {

            // Solo se ponen en los bordes.
            if ((i == 0) || (j == 0) || (j == numRectsW - 1) || (i == numRectsH - 1)) {

                rec = new QGraphicsRectItem(j*wRects, i*hRects + spaceToPutDecor,
                                            wRects, hRects);
                // Se pone transparente
                rec->setBrush(colorRect);
                rec->setPen(penRect);

                // Se agrega a la escena y a un contenedor de todos estos
                mScene->addItem(rec);
                mRectsInvisibles.push_back(rec);
            }
        }
    }

}
