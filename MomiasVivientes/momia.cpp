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
    PY=420;
    setPos(PX,PY);
    setPixmap(QPixmap(":/Donald1.png"));
    cont=0;
    cont2=0;
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

void momia::lanzar()
{
    cont2++;
//   if(cont2<1){this->setPixmap(QPixmap(":/lanzar1.png"));}
    if(cont2<1){this->setPixmap(QPixmap(":/lanzar2.png"));}
//    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar3.png"));}
    if(cont2>=1 && cont<2){this->setPixmap(QPixmap(":/lanzar4.png"));}
    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar5.png"));}
    if(cont2>=3 && cont2<4){this->setPixmap(QPixmap(":/lanzar6.png"));cont2=0;}
    qDebug()<<"contador...."<<cont2;
}
