#include "obstacle.h"

Obstacle::Obstacle() {}

Obstacle::Obstacle(double _posx, double _posy, double _width, double
                   _height, double _velObst, std::string &_nameSpObst)
{

    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    vel = _velObst;
    nameSpObj = _nameSpObst;

    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width, height);
}

QRectF Obstacle::boundingRect() const
{
    return QRectF (-width/2, -height/2, width, height);
}

void Obstacle::advance(int)
{
    posx = posx - vel;

    setPos(posx, posy);
    setPixmap(pixMapObj);
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(posx, posy, pixMapObj);
    setPos(posx, posy);
}
