#include "worldobject.h"

WorldObject::WorldObject() {}

void WorldObject::moveObject()
{
    posx = posx - vel;

    setPos(posx,posy);
    setPixmap(pixMapObj);
}

double WorldObject::getPosx() const
{
    return posx;
}

void WorldObject::setPosx(double value)
{
    posx = value;
}

double WorldObject::getPosy() const
{
    return posy;
}

void WorldObject::setPosy(double value)
{
    posy = value;
}

double WorldObject::getVel() const
{
    return vel;
}

void WorldObject::setVel(double value)
{
    vel = value;
}
