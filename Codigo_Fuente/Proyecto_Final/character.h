#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
#include <QtMath>
#include <iostream>
#include "worldobject.h"

using namespace std;
class Character : public WorldObject{
public:
    Character();
    Character(double _posx, double _posy, double _width, double
              _height, double _velObst, std::string &_nameSpObst);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveCharacter(int keyEventChar);
    void setPosition();

    void calculateInitialVelocity();
    void parabolicMovement(double dt);

    bool getJump() const;
    void setJump(bool value);

    double getLastPosy() const;
    void setLastPosy(double value);

    int getLastKey() const;
    void setLastKey(int value);

    int getScore() const;
    void setScore(int value);

private:
    double dt;
    double Vx, Vy;
    double lastPosy;

    int lastKey;
    int Score;

    bool jump = false;
    double G = -9.8;
};

#endif // CHARACTER_H
