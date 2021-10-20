#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class Character : public QGraphicsPixmapItem
{
public:
    Character();
    Character(double _posx, double _posy, double _width, double _height,
              double _dt, std::string _fileSprite);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void changePosition();

    //void moveSprite();
    //void moveCharacter(int keyEventChar);
    double getPosx() const;
    void setPosx(double value);

    double getPosy() const;
    void setPosy(double value);

protected:
    void keyPressEvent(QKeyEvent *event);
private:

    double posx, posy;
    double width, height;
    double dt;
    std::string spriteCharacter;
    int lastKey;
    QPixmap pixMapChar;


};

#endif // CHARACTER_H
