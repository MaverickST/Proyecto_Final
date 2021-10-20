#include "character.h"

Character::Character() {}

Character::Character(double _posx, double _posy, double _width, double _height, double _dt, std::string _fileSprite){
    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    spriteCharacter = _fileSprite;
    dt = _dt;

    pixMapChar.load(spriteCharacter.c_str());
    pixMapChar = pixMapChar.scaled(width, height); // Esto se cambia
}

QRectF Character::boundingRect() const{
    return QRectF (-width/2, -height/2, width, height);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->drawPixmap(-width/2, -height/2, pixMapChar);
    setPos(posx, posy);
}

void Character::changePosition(){
    setPos(posx, posy);
}

/*void Character::moveCharacter(int keyEventChar){
    lastKey = keyEventChar;
    // Movimiento del personaje en funcion de la tecla presionada.
}*/

void Character::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_A:{
        //Movimiento hacia la derecha, decrece el eje X
        posx -= 5;
        setPos(posx,posy);
        break;
    }
    case Qt::Key_D:{
        //Movimiento hacia la izquierda, crece el eje X
        posx += 5;
        setPos(posx,posy);
        break;
    }
    case Qt::Key_S:{
        //Movimiento hacia abajo, crece el eje Y
        posy += 5;
        setPos(posx,posy);
        break;
    }
    case Qt::Key_W:{
        //Movimiento hacia arriba, decrece el eje Y
        posy -= 5;
        setPos(posx,posy);
        break;
    }
    case Qt::Key_Space:{
        //Salto (Movimiento parabolico)
        break;
    }
    }
}

double Character::getPosy() const
{
    return posy;
}

void Character::setPosy(double value)
{
    posy = value;
}

double Character::getPosx() const
{
    return posx;
}

void Character::setPosx(double value)
{
    posx = value;
}
