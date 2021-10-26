#ifndef FINALBOSS_H
#define FINALBOSS_H

#define Lamb 0.02
#define E  2.7182818285

#include "worldobject.h"

class FinalBoss : public WorldObject
{
public:
    FinalBoss();
    FinalBoss(double _posx, double _posy, double _R, double _masa,
              double _tFinal, double _L, std::string _nameSpBoss);

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

    // Tiempo en que se detiene el pendulo
    // Se obtiene con Tau:  tFinal = 5*Tau
    // El tiempo que todo sistema oscilatorio pierde la mayor
    // parte de su energía
    double tFinal;

    double L; // Longitud del pendulo

    double Tau; // Constante Tau: tiemp de decaimiento
    double W; // Frecuencia angular amortiguada
    double Phi; // Angulo inicial en radianes
    double t; // Tiempo
    double longArc; // Longitud de arco -> x(t)

};

#endif // FINALBOSS_H
