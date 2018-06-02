#include "momia.h"

float momia::getPX() const
{
    return PX;
}

void momia::setPX(float value)
{
    PX = value;
}

float momia::getPY() const
{
    return PY;
}

void momia::setPY(float value)
{
    PY = value;
}

momia::momia(QObject *parent) : QObject(parent)
{
    PX=0;
    PY=370;
    setPos(PX,PY);
    setPixmap(QPixmap(":/Donald1.png"));
    cont=0;
}

void momia::mover()
{
    PX=PX+8;
    setPos(PX,PY);
    cont++;
    qDebug()<<"contador"<<cont;
    if(cont<3){this->setPixmap(QPixmap(":/Donald3.png"));}
    if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/Donald2.png"));}
    if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/Donald4.png")); cont=0;}
}

void momia::saltar(float dt)
{
    PY = PY -35*dt + 20*dt*dt ;
        setPos(PY,PX);
        this->setPixmap(QPixmap(":/Donald1.png"));
}
