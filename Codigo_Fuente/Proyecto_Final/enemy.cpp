#include "enemy.h"

Enemy::Enemy() {}

Enemy::Enemy(double _posx, double _posy, double _width, double _height,
             double _velEnemy, double _masaEnemy, std::string &_nameSpEnemy)
{
    posx = _posx;
    posy = _posy;
    width = _width;
    height = _height;
    vel = _velEnemy;
    masa = _masaEnemy;
    contTimeToExpl = 0;
    isColliding = false;

    nameSpObj = _nameSpEnemy;
    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(width, height);
}

QRectF Enemy::boundingRect() const
{
    return QRectF (-width/2, height/2, width, height);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-width/2, height/2, pixMapObj, 0, 0, width, height);
    setPos(posx, posy);

    // Dibuja la fuente de la porción rectangular
    // del mapa  de píxeles dado en el objetivo
    // dado en el dispositivo de pintura
}

void Enemy::moveEnemy()
{
    if (isColliding) {
        // Para cuando impacte una bala, despues de un tiempo hay una explosion.
        if (contTimeToExpl == 0) {
            //velResultOfCollides
        }
    }else {
        posx = posx - vel;

        setPos(posx, posy);
        setPixmap(pixMapObj);
    }
}

bool Enemy::getIsColliding() const
{
    return isColliding;
}

void Enemy::setIsColliding(bool value)
{
    isColliding = value;
}

double Enemy::getVelColliderObject() const
{
    return velColliderObject;
}

void Enemy::setVelColliderObject(double value)
{
    velColliderObject = value;
}

int Enemy::getContTimeToExpl() const
{
    return contTimeToExpl;
}

void Enemy::setContTimeToExpl(int value)
{
    contTimeToExpl = value;
}
