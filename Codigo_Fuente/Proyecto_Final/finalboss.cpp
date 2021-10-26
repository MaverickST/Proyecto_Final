#include "finalboss.h"

FinalBoss::FinalBoss() {}

FinalBoss::FinalBoss(double _posx, double _posy, double _R, double _masa,
                     double _tFinal, double _L, std::string _nameSpBoss)
{
    posx = _posx;
    posy = _posy;
    R = _R;
    masa = _masa;
    tFinal = _tFinal;
    L = _L;
    nameSpObj = _nameSpBoss;

    // Se crea el pixmap
    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(2*R, 2*R);

    // Valores para el movimiento oscilatorio amortiguado
    double g = 9.8;
//    double Icm = (2/5)*masa*R*R; // Momento de inersia para una esfera solida
    double Wo = sqrt(g/L); // Frecuencia angular para pendulo fisico
    double Wc = Lamb/(2*masa); // Frecuencia angular critica
    W = sqrt(Wo*Wo - Wc*Wc); // Frecuencia ang. amortiguada

    Tau = masa/Lamb;
    tFinal = _tFinal;
    // Es un angulo pequeño, esto porque es un MAS amortiguado
    Phi = (11)*(M_PI_2*2)/180; // De grados a rad
    t = 0;
}

QRectF FinalBoss::boundingRect() const
{
    return QRectF (-R, -R, R*2, R*2);
}

void FinalBoss::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-R, -R, pixMapObj, 0, 0, R*2, R*2);
//    setPos(posx, posy);
}

void FinalBoss::moveBoss(int numToTimer)
{
    t += numToTimer;

    longArc = L*qPow(E, -t/(2*Tau))*qCos(W*t + Phi);

    double rads = longArc/L;

    setPos(L*qCos(rads + M_PI_2) + posx, L*qSin(rads + M_PI_2) + posy);
    setPixmap(pixMapObj);
}

double FinalBoss::getTFinal() const
{
    return tFinal;
}

void FinalBoss::setTFinal(double value)
{
    tFinal = value;
}

double FinalBoss::getL() const
{
    return L;
}

void FinalBoss::setL(double value)
{
    L = value;
}

double FinalBoss::getR() const
{
    return R;
}

void FinalBoss::setR(double value)
{
    R = value;
}

double FinalBoss::getT() const
{
    return t;
}

void FinalBoss::setT(double value)
{
    t = value;
}
