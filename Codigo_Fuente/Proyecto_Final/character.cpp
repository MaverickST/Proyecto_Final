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

    double theta = qDegreesToRadians(30.0);

    //Se halla velocidad en ambos ejes
    Vx = vel * cos(theta);
    Vy = vel * sin(theta);
}

QRectF Character::boundingRect() const{
    return QRectF (-width/2, -height/2, width, height);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->drawPixmap(posx, posy, pixMapObj);
    setPos(posx, posy);
}

void Character::moveCharacter(int keyEventChar){
    lastKey = keyEventChar;
    if(keyEventChar == Qt::Key_A){
        posx -= 5;
        setPos(posx , posy);
    }else if (keyEventChar == Qt::Key_D){
        posx += 5;
        setPos(posx , posy);
    }else if(keyEventChar == Qt::Key_S){
        posy += 5;
        setPos(posx , posy);
    }else if(keyEventChar == Qt::Key_W){
        posy -= 5;
        setPos(posx , posy);
    }

    if(jump){
        lastPosy = posy;
    }

    // Movimiento del personaje en funcion de la tecla presionada.
}

void Character::parabolicMovement(double dt){
    Vy += G * dt;

    //Se halla la posicion en ambos ejes
    posx += Vx * dt;
    posy += Vy * dt + (G * dt * dt)/2.0f;

    setPos(posx , -posy);
    cout << "[ " << posx << " , " << posy << " ]" << endl;
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
