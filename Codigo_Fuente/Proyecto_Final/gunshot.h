#ifndef GUNSHOT_H
#define GUNSHOT_H

#include "worldobject.h"

class GunShot : public WorldObject
{
public:
    GunShot();

    GunShot(double _posx, double _posy, double _width, double _height,
            double _velGunShot, double _masaGunShot, std::string &_nameSpGunShot);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};

#endif // GUNSHOT_H
