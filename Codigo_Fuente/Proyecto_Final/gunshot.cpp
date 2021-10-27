#include "gunshot.h"

GunShot::GunShot() {}

GunShot::GunShot(double _posx, double _posy, double _width, double _height,
                 double _velGunShot, double _masaGunShot, std::string &_nameSpGunShot)
{

    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    vel = _velGunShot;
    masa = _masaGunShot;
    nameSpObj = _nameSpGunShot;

    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width, height);

}

QRectF GunShot::boundingRect() const
{
    return QRectF (-width/2, -height/2, width, height);
}

void GunShot::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-width/2, -height/2, pixMapObj, 0, 0, width, height);
    setPos(posx, posy);
}




