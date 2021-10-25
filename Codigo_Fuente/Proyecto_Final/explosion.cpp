#include "explosion.h"

Explosion::Explosion() {}

Explosion::Explosion(double _posx, double _posy, double _width, double _height)
{
    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    colum = 0;
    row = 0;

    nameSpObj = ":/Sprites/Explosion.png";
    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width*9, height*9);
}

QRectF Explosion::boundingRect() const
{
    return QRectF (-width/2, -height/2, width, height);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
//    QPixmap pixMapObj(nameSpObj.c_str());
//    pixMapObj = pixMapObj.scaled(width*9, height*9);
    painter->drawPixmap(-width/2, -height/2, pixMapObj, colum*width, row*height, width, height);
    setPos(posx, posy);
}

void Explosion::moveExplosion()
{
    colum++;

    if ((colum + 1)%9 == 0) {
        row++;
        colum = 0;

    }
    if (row >= 9) {
        endExplosion = true;
    }

    setPos(posx,posy);
    setPixmap(pixMapObj);
}

bool Explosion::getEndExplosion() const
{
    return endExplosion;
}

void Explosion::setEndExplosion(bool value)
{
    endExplosion = value;
}

