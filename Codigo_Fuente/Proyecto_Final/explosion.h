#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "worldobject.h"

class Explosion : public WorldObject
{
public:
    Explosion();
    Explosion(double _posx, double _posy, double _width, double _height);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveExplosion();

    bool getEndExplosion() const;
    void setEndExplosion(bool value);

private:

    int colum;
    int row;
    bool endExplosion;

};

#endif // EXPLOSION_H
