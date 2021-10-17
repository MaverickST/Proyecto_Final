#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>

class Character : public QGraphicsPixmapItem
{
public:
    Character();
    Character(double _posx, double _posy, double _width, double _height, std::string _fileSprite);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    //void moveSprite();
    void moveCharacter(int keyEventChar);

private:

    double posx, posy;
    double width, height;
    std::string spriteCharacter;
    int lastKey;
    QPixmap pixMapChar;

};

#endif // CHARACTER_H
