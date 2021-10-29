#include "gameworld.h"
#include "ui_gameworld.h"

GameWorld::GameWorld(QMap<string, string> _mSpritesWorld,
    QMap<string, double> _mObjectsValues, int _timeToChangeWorld, bool _multiPlayer,
    User *&_User, User *&_User2,
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
    mUser2 = _User2;

    // Contenedores de todos los datos
    mObjectsValues = _mObjectsValues;
    mSpritesWorld = _mSpritesWorld;

    // Inicializacion de todos los atributos
    partWorld_1 = true; // Para saber si es la parte 1 o 2 del mundo
    assingAttributeValues();
    changeSprites();

    // Otros atributos
    timeToChangeWorld = _timeToChangeWorld;
    multiPlayer = _multiPlayer;

    // Para controlar la generacion de objetos
    contTimeToSpawn = 0;
    timeToSpawn = 200; // son milisegundos
    posxSpwanAny = widthScene + 60;
    contTimeToShot = 0; // Para que dispare cada cierto tiempo

    // Para controlar el tiempo del juego
    timeToGame = 1, contTimeToGame = 0;

    // Se crean rectangulos alrededor del mapa
    createRectsInvisibles();

    //Inicializacion del personaje principal
    string sprite = "../Proyecto_Final/Sprites/auto1.png";
    PJ = new Character ((50+20)/2,(heightScene - spaceToPutDecor)/2,50,30,30.0f,sprite);
    mScene->addItem(PJ);
    PJ->setZValue(1000);
    mUserOn = true;

    // Contador para las colisiones con los obstaculos, al colisionar
    // dos veces, pierde una vida
    contCollisionsWithObstacle = 0;
    invisibilityTime = 0; // Para el tiempo que está invensible

    // Creacion del boss
    Boss = nullptr;

    // Ventana emergente
    puWindow = new PopUpWindow(this);

    // Timer, cada 20ms
    numToTimer = 20;
    mTimer = new QTimer;
    srand(time(NULL));

    // Se muestran los datos del usuario
    ui->LCD_LIVES->display(mUser->lives());
    ui->LCD_TIME->display(timeToGame);
    ui->LCD_SCORE->display(0);

    // Para saber si la ventana emergente está activa
    popUpWindowOn = false;

    connect(ui->pB_ExitGame, &QPushButton::clicked, this, &GameWorld::endGame);
    connect(ui->pB_StartGame, &QPushButton::clicked, this, &GameWorld::startQTimer);
    connect(mTimer, &QTimer::timeout, this, &GameWorld::onUptade);
    connect(puWindow, &PopUpWindow::pressButtonPopUpW, this, &GameWorld::pressButtonContinue);
}

void GameWorld::collisionEvaluator(){

    // El metodo se encarga de evaluar las colisiones entre los objetos

    //Se evalua colision con enemigos, limites y obstaculos

    EnemyCollision = collisionWithEnemy();
    ObstacleCollision = collisionWithObstacle();
    LimitsCollision = collisionWithLimits();

    /**    EVALUACION DE COLISIONES     **/

    //        cout << "MODO 1 JUGADOR :)" << endl;
    if(Boss != nullptr && PJ->collidesWithItem(Boss)){
        //Hubo colision con un enemigo
        //Se resta vida
        changeInUsers();
        Explosion *e = new Explosion((PJ)->getPosx(), (PJ)->getPosy(), wExplosion, hExplosion);
        mScene->addItem(e);
        mExplosionsWorld.push_back(e);
        PJ->setPosy((heightScene - spaceToPutDecor)/2);
        PJ->setPosx((50+20)/2);
        PJ->setPosition();
        invisibilityTime = 5;
        beCollides = false;
    }
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
        if(PJ->getJump() == true){
            PJ->setJump(false);
            PJ->setPosy(PJ->getPosy() + 20);
            PJ->setPosx(PJ->getPosx() - 20);
        }
    }else{
        beCollides = false;
    }

    if(PJ->getJump() == false && invisibilityTime == 0){//Otra consision para evaluar colisiones es el tiempo de invensibilidad
        //Solo se va a evaluar colisiones cuando el personaje no este saltando
        if(EnemyCollision || ObstacleCollision){
            if(ObstacleCollision){
                //Hubo colision con un obstaculo
                contCollisionsWithObstacle++;
                if(contCollisionsWithObstacle == 2){

                    //Se resta vida solo cuando colisiona dos veces contra un obstaculo
                    changeInUsers();
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
                changeInUsers();
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
    //Evaluacion de colisones con autos enemigos
    for(auto i = mEnemiesWorld.begin(); i != mEnemiesWorld.end(); i++){
        if(PJ->collidesWithItem(*i)){
            return true;
        }
    }
    return false;
}

bool GameWorld::collisionWithObstacle(){
    //Evaluacion de colisones con obstaculos
    for(auto it = mObstaclesWorld.begin(); it != mObstaclesWorld.end(); it++){
        if(PJ->collidesWithItem(*it)){
            return true;
        }
    }
    return false;
}

bool GameWorld::collisionWithLimits(){
    //Evaluacion de colicion con los limites de la escena
    for(auto i = mRectsInvisibles.begin(); i != mRectsInvisibles.end(); i++){       
        if(PJ->collidesWithItem(*i)){
            return true;
        }
    }
    return false;
}

void GameWorld::onUptade(){

    // El slot se ejecuta en cada timeout

    // Que solo siga el juego cuando la ventana emergente no está activa
    if (popUpWindowOn == false) {

        //Evaluacion de condicion de Game Over
        if(mUser->lives() == 0){
            //El personaje principal se ha quedado sin vidas
            //GameWorld::endGame();
        }

        // Evaluador de colisiones
        collisionEvaluator();

        // Si está realizando un salto
        if(PJ->getJump() == true){
            PJ->parabolicMovement(0.1f);
        }
        // Contadores
        contTimeToShot++; // Para controlar la cantidad de balas
        contTimeToGame++; // Para manejar el tiempo del juego

        //MANEJO DEL TIEMPO DE INVENSIBILIDAD
        if(invisibilityTime > 0 && contTimeToGame*numToTimer >= 1000){
            invisibilityTime--;//Se resta cada 1s sigueindo la misma logica que el if anterior
        }

        //MANEJO DEL TIEMPO LIMITE QUE TIENE EL USUARIO PARA GANAR EL NIVEL

        // Está hecho para que cambie cada segundo
        if(contTimeToGame*numToTimer >= 1000){
            ui->LCD_TIME->display(timeToGame++);
            contTimeToGame = 0;//Se reseta la variable contTimeEndG
        }

        // TIEMPO PARA EL CAMBIO DE MUNDO Y AUMENTO EN LA DIFICULTAD (cada 5s)
        if ((timeToGame%5 == 0) && (contTimeToGame == 0)) { // Pruebas
            if (timeToGame%timeToChangeWorld == 0) {
                // Cambio de mundo y mayor aumento de la dificultad
                increasedDifficulty(true);
            }else {
                // Solo un incremente leve de la dificultad
                increasedDifficulty(false);
            }
            // Se reasignan los valores de todos los objetos
            assingAttributeValues();
        }

        // APARICION DEL BOSS CADA CIERTO TIEMPO ( 2/3 de timeToChangeWorld)

        // El residuo nos da el tiempo que ha pasado despues de un cambio de mundo
        // Por lógica se deduce:
        //      TiempoParaCambiarElMundo - TiempoDespuesDelCambio = TiempoDeDuracionDelBoss
        // Y así sabemos cuando va a aparecer en boss
        double timeLaterOfChangeWorld = (timeToGame*1000)%(timeToChangeWorld*1000);

        if ((timeToChangeWorld*1000 - timeLaterOfChangeWorld == tFinalBoss) && (contTimeToGame == 0)) {
            // Se genera un nuevo boss
            Boss = new FinalBoss(RBoss, masaBoss, LBoss, tFinalBoss, tToChangePosBoss, nameSpBoss,
                                 widthScene, heightScene - hEnemy, spaceToPutDecor + hEnemy);
            mScene->addItem(Boss);
        }

        // Generacion y eliminacion de los objetos de la escena
        contTimeToSpawn++;
        if (contTimeToSpawn*numToTimer >= timeToSpawn) {
            spawnSceneObject();
            contTimeToSpawn = 0;
            deleteWorldObject();

        }
        // Se mueven todos los objetos de la escena
        moveWorldObjects();
    }
}

void GameWorld::spawnSceneObject(){

    // El método se encarga de la generacion aleatoria de todos los objetos
    // del mapa.


    // La ultima posicion en y de los obstaculos y autos enemigos.
    // Se usa para evitar que se generen en el mismo lugar y queden pegados
    static int lastPosy = 0;

    /// [ GENERACION ALEATORIA DE LOS OBSTACULOS/ENEMIGOS SEGUN UNA PROBABILIDAD ]

    // Con el aumento de la dificualtad, va a llegar un momento en que las probabiliadaes
    // serán mayores al 100% (1000), entonces se pone para ambos la misma prob
    if (probSpawnObst >= 1000) {
        probSpawnEnemy = 500;
        probSpawnObst = 1000;
    }

    int numRand = rand()%1000 + 1; // numero aleatoria entre [1-1000]
    int randPosyObjec; // Posicion en Y aleatoria de los obstaculos/enemigos

    if (numRand <= probSpawnEnemy) { // Se genera un enemigo

        // Numero aleatoria en este intervalo
        // [spaceToPutDecor + hEnemy/2, heightScene - hEnemy/2]
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 2*hEnemy/2 + 1))
                + spaceToPutDecor + hEnemy/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hEnemy/2 >= lastPosy) && (randPosyObjec - hEnemy/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 2*hEnemy/2 + 1))
                    + spaceToPutDecor + hEnemy/2;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;

        // Se crea y agrega un nuevo enemigo
        Enemy *newEnemy = new Enemy(posxSpwanAny, randPosyObjec, wEnemy, hEnemy,
                                    velEnemy, masaEnemy, nameSpEnemy);
        mEnemiesWorld.push_back(newEnemy);
        mScene->addItem(newEnemy);
    }
    else if (numRand <= probSpawnObst) { // Se genera un obstaculo

        // [spaceToPutDecor + hObst/2, heightScene - hObst/2] -> Numero aleatoria en este intervalo
        randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 2*hObstacle/2 + 1))
                + spaceToPutDecor + hObstacle/2;

        // Esto para el caso en que los objetos se generan casi juntos o juntos
        while ((randPosyObjec + hObstacle/2 >= lastPosy) &&
               (randPosyObjec - hObstacle/2 <= lastPosy)) {

            randPosyObjec = rand()%(int(heightScene - spaceToPutDecor - 2*hObstacle/2 + 1))
                    + spaceToPutDecor + hObstacle/2;
        }
        // Se actualiza la nueva ultima posicion aleatoria en y de los objetos
        lastPosy = randPosyObjec;

        // Se crea y agrega un nuevo obstaculo
        Obstacle *newObst = new Obstacle(posxSpwanAny, randPosyObjec, wObstacle, hObstacle,
                                         velObstacle, nameSpObstacle);
        mObstaclesWorld.push_back(newObst);
        mScene->addItem(newObst);
    }

    /// [ GENERACION ALEATORIA DEL OBJETO DECORATION PARA LA DECORACION DEL JUEGO ]

    int randPosyDecor; // Posicion en Y aleatoria
    int randDecorKind; // Como son dos tipos de decoracion, habrá un 50% de spawn para cada uno
    // Para delimitar la posicion de spawn
    int hMaxDecor = hDecor1 > hDecor2 ? hDecor1 : hDecor2;
    int randPutDecor = rand()%1000 + 1; // [1, 1000]

    if (randPutDecor < probSpawnDecor) { // Se genera un nuevo objeto decoracion.

        // [hMaxDecor/2, spaceToPutDecor - hMaxDecor/2] -> Numero aleatorio en este intervalo
        randPosyDecor = rand()%(int(spaceToPutDecor - 2*hMaxDecor/2 + 1)) + hMaxDecor/2;

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
    }
}

void GameWorld::deleteWorldObject()
{
    // El método se encarga de la eliminacion de los objetos del mapa
    // Se eliminan bajo ciertas condiciones: que esten fuera de la escena
    // o que haya una explosion que los destruya

    // Eliminar Boss cuando haya pasado un tiempo t = tFinalBoss desde que apareció

    if (Boss != nullptr) {
        if (Boss->getTFinal() <= 0) {
            mScene->removeItem(Boss);
            delete Boss;
            Boss = nullptr;
            // Se suma score al usuario que esté en el momento
            if (mUserOn) {
                mUser->setScoreLevel(mUser->scoreLevel() + 50);
                ui->LCD_SCORE->display(mUser->scoreLevel());
            }else {
                mUser2->setScoreLevel(mUser2->scoreLevel() + 50);
                ui->LCD_SCORE->display(mUser2->scoreLevel());
            }
        }
    }


    // Posicion en X de la escena, a partir de la cual se eliminan los objetos
    int posToDelete = -posxSpwanAny;
    int posObject;

    // Eliminacion de enemigos
    for (int i = 0; i < mEnemiesWorld.size(); i++) {

        // Se eliminan los que estan fuera de la escena
        posObject = mEnemiesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mEnemiesWorld.at(i));
            delete mEnemiesWorld.at(i);
            mEnemiesWorld.erase(mEnemiesWorld.begin() + i);
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

            // Se elimina el enemigo
            mScene->removeItem(mEnemiesWorld.at(i));
            delete mEnemiesWorld.at(i);
            mEnemiesWorld.erase(mEnemiesWorld.begin() + i);

            //Se actualiza el Score
            if (mUserOn) {
                mUser->setScoreLevel(mUser->scoreLevel() + 50);
                ui->LCD_SCORE->display(mUser->scoreLevel());
            }else {
                mUser2->setScoreLevel(mUser2->scoreLevel() + 50);
                ui->LCD_SCORE->display(mUser2->scoreLevel());
            }
        }
    }
    // Eliminacion de los obstaculos que ya estan fuera de la escena
    for (int i = 0; i < mObstaclesWorld.size(); i++) {

        posObject = mObstaclesWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mObstaclesWorld.at(i));
            delete mObstaclesWorld.at(i);
            mObstaclesWorld.erase(mObstaclesWorld.begin() + i);
        }
    }
    // Eliminacion de las decoraciones que estan fuera de la escena
    for (int i = 0; i < mDecorsWorld.size(); i++) {

        posObject = mDecorsWorld.at(i)->getPosx();
        if (posObject <= posToDelete) {

            mScene->removeItem(mDecorsWorld.at(i));
            delete mDecorsWorld.at(i);
            mDecorsWorld.erase(mDecorsWorld.begin() + i);
        }
    }
    // Eliminacion de las explosiones
    for (int i = 0; i < mExplosionsWorld.size(); i++) {

        // Se verifica que la explosion terminó
        if (mExplosionsWorld.at(i)->getEndExplosion()) {

            mScene->removeItem(mExplosionsWorld.at(i));
            delete mExplosionsWorld.at(i);
            mExplosionsWorld.erase(mExplosionsWorld.begin() + i);
            break; // Que solo se elimine uno en cada ejecucion.
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
            break; // Que solo se elimine uno en cada ejecucion.
        }
    }
}

void GameWorld::moveWorldObjects(){
    // La funcion se encarga de ejecutar el metodo: moveObject.
    // Tal metodo mueve al objeto en cuestion segun su propia velocidad

    if (Boss != nullptr) {
        Boss->moveBoss(numToTimer);
    }


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

        // Debe transcurrir, al menos, un tiempo t = timeToShot entre
        // disparo y disparo
        if (contTimeToShot*numToTimer >= timeToShot) {
            GunShot *bullet;

            bullet = new GunShot(PJ->getPosx()+5,PJ->getPosy(),wShot,hShot,velShot,masaShot,nameSpShot);
            mScene->addItem(bullet);
            mGunShotsWorld.push_back(bullet);
            contTimeToShot = 0;
        }

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


void GameWorld::assingAttributeValues()
{
    // El metodo se encarga de reasignar todos los valores a los datos
    // de todos los objetos
    // Como hay un constante aumento de la dificultad, constantemente se estará reasignando
    // tales valores, para que despues se vean reflejados en los propio objetos

    // Atributos para las decoraciones

    // Decoraciones tipo 1
    wDecor1 = mObjectsValues["wDecor1"];
    hDecor1 = mObjectsValues["hDecor1"];

    // Decoraciones tipo 2
    wDecor2 = mObjectsValues["wDecor2"];
    hDecor2 = mObjectsValues["hDecor2"];

    velDecor = mObjectsValues["velDecor"];
    probSpawnDecor = mObjectsValues["probSpawnDecor"];
    // Espacio hábil para poner las decoraciones. Van en la parte superior.
    spaceToPutDecor = (hDecor1 > hDecor2 )? hDecor1*2 + 5 : hDecor2*2 + 5;

    // Atributos para los enemigos
    wEnemy = mObjectsValues["wEnemy"];
    hEnemy = mObjectsValues["hEnemy"];
    velEnemy = mObjectsValues["velEnemy"];
    probSpawnEnemy = mObjectsValues["probSpawnEnemy"];
    masaEnemy = mObjectsValues["masaEnemy"];

    // Para los obstaculos
    wObstacle = mObjectsValues["wObstacle"];
    hObstacle = mObjectsValues["hObstacle"];
    velObstacle = mObjectsValues["velObstacle"];
    probSpawnObst = mObjectsValues["probSpawnObst"];

    // Para los disparos
    wShot = mObjectsValues["wShot"];
    hShot = mObjectsValues["hShot"];
    velShot = mObjectsValues["velShot"];
    masaShot = mObjectsValues["masaShot"];
    timeToShot = mObjectsValues["timeToShot"];

    // Para las explosiones
    wExplosion = mObjectsValues["wExplosion"];
    hExplosion = mObjectsValues["hExplosion"];

    // Para el boss
    RBoss = mObjectsValues["RBoss"];
    masaBoss = mObjectsValues["masaBoss"];
    LBoss = mObjectsValues["LBoss"];
    tFinalBoss = mObjectsValues["tFinalBoss"];
    tToChangePosBoss = mObjectsValues["tToChangePosBoss"];


}

void GameWorld::increasedDifficulty(bool changeWorld)
{
    // El método se encarga de aumentar los valores de los objetos,
    // que al aumentarlos y disminuirlos, implica un incremente o
    // decremento en la dificulta del juego
    // Tales valores de los objetos son: velocidades, probabilidades.


    if (changeWorld == true) {
        // El aumento es del 5% para las velocidades
        // Y del 8% para las probabilidades
        mObjectsValues["velDecor"] *= 1.05; // Velocidad de las decoraciones
        mObjectsValues["velEnemy"] *= 1.05; // Vel de los enemigos
        mObjectsValues["probSpawnEnemy"] *= 1.08; // Prob de los enemigos
        mObjectsValues["velObstacle"] *= 1.05; // Vel de los obstaculos
        mObjectsValues["probSpawnObst"] *= 1.08; // Prob de los obstaculos
        mObjectsValues["velShot"] *= 1.05; // Vel de los disparos

        // Cuando es cambio de mundo (changeWorld == true), tambien aumenta la dificultad del boss

        // Para la longitud es de 3%
        mObjectsValues["LBoss"] *= 1.03;
        // Su tiempo para cambiar de posicion se reduce un 20%
        mObjectsValues["tToChangePosBoss"] *= 0.8;

        // Para cargar los pixmap de la siguiente parte
        if (partWorld_1 == true) {
            partWorld_1 = false;
        }else {
            partWorld_1 = true;
        }
        changeSprites();

    }else {
        // El aumento es del 2% para las velocidades
        // Y del 4% para las prob
        mObjectsValues["velDecor"] *= 1.02; // Velocidad de las decoraciones
        mObjectsValues["velEnemy"] *= 1.02; // Vel de los enemigos
        mObjectsValues["probSpawnEnemy"] *= 1.04; // Prob de los enemigos
        mObjectsValues["velObstacle"] *= 1.02; // Vel de los obstaculos
        mObjectsValues["probSpawnObst"] *= 1.04; // Prob de los obstaculos
        mObjectsValues["velShot"] *= 1.02; // Vel de los disparos

    }
}

void GameWorld::changeSprites()
{
    // Cambio en los sprites de los objetos

    if (partWorld_1 == true) { // Para la parte 1 del mundo
        // Fondo
        nameSpBackground = mSpritesWorld["nameSpBackground_1"];
        // Decoraciones
        nameSpDecor1 = mSpritesWorld["nameSpDecor1_1"];
        nameSpDecor2 = mSpritesWorld["nameSpDecor2_1"];

        // Enemigos
        nameSpEnemy = mSpritesWorld["nameSpEnemy_1"];
        // Obstaculos
        nameSpObstacle = mSpritesWorld["nameSpObstacle_1"];
        // Disparo
        nameSpShot = mSpritesWorld["nameSpShot_1"];
        // Boss
        nameSpBoss = mSpritesWorld["nameSpBoss_1"];


    }else {// Para la parte 2 del mundo
        // Fondo
        nameSpBackground = mSpritesWorld["nameSpBackground_2"];
        // Decoraciones
        nameSpDecor1 = mSpritesWorld["nameSpDecor1_2"];
        nameSpDecor2 = mSpritesWorld["nameSpDecor2_2"];

        // Enemigos
        nameSpEnemy = mSpritesWorld["nameSpEnemy_2"];
        // Obstaculos
        nameSpObstacle = mSpritesWorld["nameSpObstacle_2"];
        // Disparo
        nameSpShot = mSpritesWorld["nameSpShot_2"];
        // Boss
        nameSpBoss = mSpritesWorld["nameSpBoss_2"];

    }
    // Se agrega el fondo
    pixMapBackground.load(nameSpBackground.c_str());
    pixMapBackground = pixMapBackground.scaled(widthScene + 5, heightScene + 5);
    mScene->addPixmap(pixMapBackground);
}


void GameWorld::changeInUsers()
{
    // El método se ejecuta cuando el personaje colisionó contra
    // que le hace daño
    // Se encarga de mostrar una ventana emergente cuando se pierden todas las vidas

    if (multiPlayer == true) {

        if (mUserOn == true) {
            // Se le resta una vida
            mUser->setLives(mUser->lives()-1);

            // Si perdió la vidas, se muestra la ventana emergente y
            // se cambio de jugador
            if (mUser->lives() == 0) {
                mUser->setTimeLevel(timeToGame);
                // Se muestra la ventane emergente
                popUpWindowOn = true; // Ahora está activa la ventana emergente
                puWindow->showInfoUser(mUser);
                puWindow->show();

                mUser->setLives(2); // Que vuelva a tener dos vidas
                mUserOn = false; // Ahora juega el usuario 2
                // Ahora se muestra el score del jugador 2
                ui->LCD_SCORE->display(mUser2->scoreLevel());
            }
            ui->LCD_LIVES->display(mUser->lives());

        }else {
            // Se le resta una vida
            mUser2->setLives(mUser2->lives()-1);

            // Si perdió la vidas, se muestra la ventana emergente y
            // se cambio de jugador
            if (mUser2->lives() == 0) {
                mUser2->setTimeLevel(timeToGame);
                // Se muestra la ventane emergente
                popUpWindowOn = true; // Ahora está activa la ventana emergente
                puWindow->showInfoUser(mUser2);
                puWindow->show();

                mUser2->setLives(2); // Que vuelva a tener dos vidas
                mUserOn = true; // Ahora juega el usuario 1
                // Ahora se muestra el score del jugador 1
                ui->LCD_SCORE->display(mUser->scoreLevel());
            }
            // Se muestra las vidas y el escore hasta el momento
            ui->LCD_LIVES->display(mUser2->lives());
        }
    }else {
        // Se le resta una vida
        mUser->setLives(mUser->lives()-1);
        ui->LCD_LIVES->display(mUser->lives());

        if (mUser->lives() == 0) { // Perdió todas las vidas
            mUser->setTimeLevel(timeToGame);
            // Se muestra ventana emergente
            popUpWindowOn = true;
            puWindow->showInfoUser(mUser);
            puWindow->show();
        }
    }
}

void GameWorld::pressButtonContinue()
{
    // El slot se ejecuta cuando se presiona el botón "CONTINUE"
    // de la ventana emergente

    popUpWindowOn = false; // Ya no está activa la ventana emergente

    // Consideramos el caso en que, estándo en modo un jugador, perdió todas
    // las vidas. Entonces pierde y vulve a ventana de ProfileUser
    if (multiPlayer == false) {
        if (mUser->lives() == 0) {
            // Se emite una señal, para terminar el juego, el usuario perdió
            GameWorld::endGame();
        }
    }
}

void GameWorld::startQTimer(){
    mTimer->start(numToTimer);
}

GameWorld::~GameWorld(){



    delete ui;
}

