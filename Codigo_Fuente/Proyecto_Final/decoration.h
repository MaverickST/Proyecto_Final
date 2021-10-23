#ifndef DECORATION_H
#define DECORATION_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "worldobject.h"

class Decoration : public WorldObject{
public:
    Decoration();

    Decoration(double _posx, double _posy, double _width, double _height,
             double _velObst, std::string &_nameSpDecor);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

};

#endif // DECORATION_H
