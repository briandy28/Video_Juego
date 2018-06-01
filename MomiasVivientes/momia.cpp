#include "momia.h"

momia::momia(QObject *parent) : QObject(parent)
{
   PX=0;
   PY=390;
   setPos(PX,PY);
   setPixmap(QPixmap(":/momia.png"));
}

void momia::mover()
{
    PX=PX+8;
    setPos(PX,PY);
    if (PX == 0)
    {
        scene()->removeItem(this);
        delete this;
    }
}

void momia::saltar(float dt)
{
    PY = PY -35*dt + 20*dt*dt ;
        setPos(PY,PX);
}
