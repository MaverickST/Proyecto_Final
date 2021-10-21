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
    painter->drawPixmap(posx, posy, pixMapObj);
    setPos(posx, posy);
}

void Character::moveCharacter(int keyEventChar){
    lastKey = keyEventChar;
    if(keyEventChar != Qt::Key_Up){
        if(keyEventChar == Qt::Key_A){
            posx -= 5;
        }else if (keyEventChar == Qt::Key_D){
            posx += 5;
        }else if(keyEventChar == Qt::Key_S){
            posy += 5;
        }else if(keyEventChar == Qt::Key_W){
            posy -= 5;
        }
        setPos(posx , posy);
    }

    // Movimiento del personaje en funcion de la tecla presionada.
}

void Character::parabolicMovement(double dt){
    //Conversion de 45° a radianes
    double theta = qDegreesToRadians(45.0);

    //Se halla la velocidad en ambos ejes
    Vx = vel * cos(theta);
    Vy = vel * sin(theta);

    //Se halla la posicion en ambos ejes
    posx += Vx * dt;
    posy += Vy * dt + (G * dt * dt)/2.0f;

    Vy += G * dt;
}
