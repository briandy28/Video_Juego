#include "gemas.h"

gemas::gemas(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX=600;
    PY=390;
    setPos(PX,PY);
    setPixmap(QPixmap(":/gema1.png"));
    timer = new QTimer();
    //connect(timer, SIGNAL(timeout()),this,SLOT(Mover()));
    connect(timer,SIGNAL(timeout()),this,SLOT(mover()));
    timer->start(40);

}

//void gemas::mover()
//{
//    PX=PX-8;
//    setPos(PX,PY);
//    if (PX == 0)
//    {
//        scene()->removeItem(this);
//        delete this;
//    }
//}
