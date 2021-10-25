#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QGraphicsPixmapItem>
#include <QPainter>

class WorldObject : public QGraphicsPixmapItem
{
public:
    WorldObject();

    void moveObject();

    double getPosx() const;
    void setPosx(double value);

    double getPosy() const;
    void setPosy(double value);

    double getVel() const;
    void setVel(double value);

    double getMasa() const;
    void setMasa(double value);

protected:
    double posx, posy;
    double width, height;
    double vel;
    double masa;
    std::string nameSpObj;

    QPixmap pixMapObj;

};

#endif // WORLDOBJECT_H
