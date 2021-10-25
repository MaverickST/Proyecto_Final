#ifndef ENEMY_H
#define ENEMY_H

#include "worldobject.h"

class Enemy : public WorldObject
{
public:
    Enemy();

    Enemy(double _posx, double _posy, double _width, double _height,
             double _velEnemy, double _masaEnemy, std::string &_nameSpEnemy);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveEnemy();


    bool getIsColliding() const;
    void setIsColliding(bool value);

    int getContTimeToExpl() const;
    void setContTimeToExpl(int value);

    int getTimeMillisecondsToExpl() const;
    void setTimeMillisecondsToExpl(int value);

private:

    bool isColliding;
    int contTimeToExpl;
    int timeMillisecondsToExpl;

};

#endif // ENEMY_H
