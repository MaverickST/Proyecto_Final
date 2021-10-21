#include "decoration.h"

Decoration::Decoration() {}

Decoration::Decoration(double _posx, double _posy, double _width,
                       double _height, double _velObst, std::string &_nameSpDecor)
{

    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    vel = _velObst;
    nameSpObj = _nameSpDecor;

    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width, height);
}

QRectF Decoration::boundingRect() const
{
    return QRectF (-width/2, -height/2, width, height);
}

void Decoration::advance(int)
{
    posx = posx - vel;

    setPos(posx, posy);
    setPixmap(pixMapObj);
}

void Decoration::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(posx, posy, pixMapObj);
    setPos(posx, posy);
}
