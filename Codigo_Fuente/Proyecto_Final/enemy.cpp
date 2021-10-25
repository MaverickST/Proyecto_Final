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

    // Para el momento en que colisiona con una bala
    // Y poder aplicar el modelo fisico: conservacion de momentum
    contTimeToExpl = 0;
    isColliding = false;
    timeMillisecondsToExpl = 2000;

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
        contTimeToExpl++;
    }
    posx = posx + vel;

    setPos(posx, posy);
    setPixmap(pixMapObj);
}

bool Enemy::getIsColliding() const
{
    return isColliding;
}

void Enemy::setIsColliding(bool value)
{
    isColliding = value;
}

int Enemy::getContTimeToExpl() const
{
    return contTimeToExpl;
}

void Enemy::setContTimeToExpl(int value)
{
    contTimeToExpl = value;
}

int Enemy::getTimeMillisecondsToExpl() const
{
    return timeMillisecondsToExpl;
}

void Enemy::setTimeMillisecondsToExpl(int value)
{
    timeMillisecondsToExpl = value;
}
