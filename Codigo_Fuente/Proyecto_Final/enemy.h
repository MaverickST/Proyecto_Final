#ifndef ENEMY_H
#define ENEMY_H


#include <QPainter>
#include "worldobject.h"

class Enemy : public WorldObject
{
public:
    Enemy();

    Enemy(double _posx, double _posy, double _width, double _height,
             double _velEnemy, std::string &_nameSpEnemy);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveEnemy();


    bool getIsColliding() const;
    void setIsColliding(bool value);

    double getVelColliderObject() const;
    void setVelColliderObject(double value);

    int getContTimeToExpl() const;
    void setContTimeToExpl(int value);

private:
    bool isColliding;
    double velColliderObject;
    int contTimeToExpl;
    double velResultOfCollides;

};

#endif // ENEMY_H
