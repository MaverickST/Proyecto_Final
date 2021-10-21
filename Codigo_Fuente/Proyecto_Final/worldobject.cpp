#include "worldobject.h"

WorldObject::WorldObject()
{}

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
