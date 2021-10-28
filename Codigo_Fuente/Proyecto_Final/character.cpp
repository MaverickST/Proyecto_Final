#include "character.h"

Character::Character() {}

Character::Character(double _posx, double _posy, double _width, double
                   _height, double _velObst, std::string &_nameSpObst){

    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    vel = _velObst;
    nameSpObj = _nameSpObst;

    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width, height);
}

QRectF Character::boundingRect() const{
    return QRectF (-width/2, -height/2, width, height);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->drawPixmap(-width/2, -height/2, pixMapObj, 0, 0, width, height);
    setPosition();
}

void Character::moveCharacter(int keyEventChar){
    // Movimiento del personaje en funcion de la tecla presionada.
    if(keyEventChar == Qt::Key_A){
        posx -= 5;
        setPosition();
        lastKey = Qt::Key_A;
    }else if (keyEventChar == Qt::Key_D){
        posx += 5;
        setPosition();
        lastKey = Qt::Key_D;
    }else if(keyEventChar == Qt::Key_S){
        posy += 5;
        setPosition();
        lastKey = Qt::Key_S;
    }else if(keyEventChar == Qt::Key_W){
        posy -= 5;
        setPosition();
        lastKey = Qt::Key_W;
    }

    /*if(jump){
        lastPosy = posy;
        calculateSpeed();
    }*/
}

void Character::setPosition(){
    setPos(posx , posy);
    setPixmap(pixMapObj);
}

void Character::calculateInitialVelocity(){
    //Posicion que indicara la parada del movimiento parabolico
    lastPosy = posy;

    //Se pasa de grados a radianes
    double theta = qDegreesToRadians(75.0);//Posiblemente se solucione poniendo el angulo negativo

    //Se halla velocidad en ambos ejes
    Vx = vel * cos(theta);
    Vy = vel * sin(theta);
}

void Character::parabolicMovement(double dt){
    if(posy <= lastPosy){
        Vy += G * dt;

        //Se halla la posicion en ambos ejes
        posx += Vx * dt;

        posy -= Vy * dt + (G * dt * dt)/2.0f;

        setPos(posx , posy);
        setPixmap(pixMapObj);
//        cout << "[ " << posx << " , " << posy << " ]" << endl;
    }else{
//        cout << "Maximo alcance" << endl;
        jump = false;
    }
}

bool Character::getJump() const{
    return jump;
}

void Character::setJump(bool value){
    jump = value;
}

double Character::getLastPosy() const{
    return lastPosy;
}

void Character::setLastPosy(double value){
    lastPosy = value;
}

int Character::getLastKey() const{
    return lastKey;
}

void Character::setLastKey(int value){
    lastKey = value;
}

int Character::getScore() const{
    return Score;
}

void Character::setScore(int value){
    Score = value;
}
