#include "character.h"

Character::Character() {}

Character::Character(double _posx, double _posy, double _width, double _height, double _dt, std::string _fileSprite)
{
    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    spriteCharacter = _fileSprite;
    dt = _dt;

    pixMapChar.load(spriteCharacter.c_str());
    pixMapChar = pixMapChar.scaled(width, height); // Esto se cambia
}

QRectF Character::boundingRect() const
{
    return QRectF (-width/2, -height/2, width, height);
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    painter->drawPixmap(-width/2, -height/2, pixMapChar);
    painter->drawPixmap(posx, posy, pixMapChar);
    setPos(posx, posy);
}

void Character::moveCharacter(int keyEventChar)
{
    lastKey = keyEventChar;

    // Movimiento del personaje en funcion de la tecla presionada.
}
