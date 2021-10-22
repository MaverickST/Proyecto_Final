#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QGraphicsPixmapItem>

class WorldObject : public QGraphicsPixmapItem
{
public:
    WorldObject();

    double getPosx() const;
    void setPosx(double value);

    double getPosy() const;
    void setPosy(double value);

    double getVel() const;
    void setVel(double value);

protected:
    double posx, posy;
    double width, height;
    double vel;
    std::string nameSpObj;

    QPixmap pixMapObj;

};

#endif // WORLDOBJECT_H
