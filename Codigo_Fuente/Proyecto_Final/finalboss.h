#ifndef FINALBOSS_H
#define FINALBOSS_H

#define Lamb 0.000018


#include <time.h>
#include "worldobject.h"

class FinalBoss : public WorldObject
{
public:
    FinalBoss();
    FinalBoss(double _R, double _masa,
              double _L, double _tFinal, bool _level1 , std::string _nameSpBoss,
              double _widthSpace, double _heightSpace, double _spaceOther);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void moveBoss(int numToTimer);

    double getTFinal() const;
    void setTFinal(double value);

    double getL() const;
    void setL(double value);

    double getR() const;
    void setR(double value);

    double getT() const;
    void setT(double value);

private:

    double R; // Radio de la esfera que pende del pendulo

    double L; // Longitud del pendulo

    double tFinal; // El tiemp que dura el boss

    // Hay boss en el primer y tercer nivel.
    // Como son distintos los movimientos que hará en cada nivel, debe
    // haber una forma de saber si es el nivel 1 o el nivel 3
    bool level1;

    // Para delimitar el movimiento del boss
    double widthSpace;
    double heightSpace;
    double spaceOther;

    double timeToNextPhase;
    double timeToChangePos;
    int contTimeToChangeP;
    double randPosx;
    double randPosy;

    double Tau; // Constante Tau: tiemp de decaimiento
    double W; // Frecuencia angular amortiguada
    double Phi; // Angulo inicial en radianes
    double t; // Tiempo
    double longArc; // Longitud de arco -> x(t)
    double E = 2.7182818285;
};

#endif // FINALBOSS_H
