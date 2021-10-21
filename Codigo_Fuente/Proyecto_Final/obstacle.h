#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QPainter>

#include "worldobject.h"

class Obstacle : public WorldObject
{
public:
    Obstacle();
    Obstacle(double _posx, double _posy, double _width, double _height,
             double _velObst, std::string &_nameSpObst);

    QRectF boundingRect() const;

    void advance(int);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:

};

#endif // OBSTACLE_H
