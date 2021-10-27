#include "finalboss.h"

FinalBoss::FinalBoss() {}

FinalBoss::FinalBoss(double _R, double _masa, double _L,
                     double _tFinal, bool _level1, std::string _nameSpBoss,
                     double _widthSpace, double _heightSpace, double _spaceOther)
{
    srand(time(NULL));

    posx = 110;
    posy = 110;
    R = _R;
    masa = _masa;
    tFinal = _tFinal;
    L = _L;
    nameSpObj = _nameSpBoss;
    level1 = _level1;

    widthSpace = _widthSpace;
    heightSpace = _heightSpace;
    spaceOther = _spaceOther;

    // Son tres fases las del boss, cada una de igual tiempo
    timeToNextPhase = tFinal/3;
    timeToChangePos = 2000;
    contTimeToChangeP = 0;
    randPosx = 0;
    randPosy = 0;

    // Se crea el pixmap
    pixMapObj.load(nameSpObj.c_str());
    pixMapObj = pixMapObj.scaled(2*R, 2*R);

    // Valores para el movimiento oscilatorio amortiguado
    double g = 9.81;
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

    contTimeToChangeP++;
    if (t <= timeToNextPhase || t == numToTimer) { // Primera fase
        if (contTimeToChangeP*numToTimer >= timeToChangePos) {
            contTimeToChangeP = 0;

            // [0.1*widthSpace , 0.4*widthSpace]
            randPosx = rand()%(int(0.4*widthSpace - 0.1*widthSpace + 1)) + 0.1*widthSpace;
            // [spaceOther, heightSpace]
            randPosy = rand()%(int(heightSpace - spaceOther + 1)) + spaceOther;
        }
    }else if (t <= timeToNextPhase*2) {
        if (contTimeToChangeP*numToTimer >= timeToChangePos) {
            contTimeToChangeP = 0;

            // [0.5*widthSpace , 0.9*widthSpace]
            randPosx = rand()%(int(0.9*widthSpace - 0.5*widthSpace + 1)) + 0.5*widthSpace;
            // [spaceOther, heightSpace]
            randPosy = rand()%(int(heightSpace - spaceOther + 1)) + spaceOther;
        }
    }else if (t <= timeToNextPhase*3) {
        if (contTimeToChangeP*numToTimer >= timeToChangePos) {
            contTimeToChangeP = 0;

            // [0.05*widthSpace , 0.95*widthSpace]
            randPosx = rand()%(int(0.95*widthSpace - 0.05*widthSpace + 1)) + 0.05*widthSpace;
            // [0.3*heightSpace + spaceOther, 0.75*heightSpace]
            randPosy = rand()%(int(0.75*heightSpace - 0.3*heightSpace - spaceOther + 1))
                    + 0.3*heightSpace + spaceOther;
        }
    }


    setPos(randPosx + L*qCos(rads + M_PI_2) - L*qSin(Phi), randPosy + L*qSin(rads + M_PI_2) - L*qCos(Phi));
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
