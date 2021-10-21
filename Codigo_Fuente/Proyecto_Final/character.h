#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QtMath>

#include "worldobject.h"
class Character : public WorldObject{
public:
    Character();
    Character(double _posx, double _posy, double _width, double
              _height, double _velObst, std::string &_nameSpObst);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveCharacter(int keyEventChar);

    void parabolicMovement(double dt);

    bool getJump() const;
    void setJump(bool value);

private:
    double dt;
    double Vx, Vy;
    //std::string spriteCharacter;
    int lastKey;

    bool jump = false;
    double G = -9.8;
};

#endif // CHARACTER_H
