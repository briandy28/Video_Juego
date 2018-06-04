#include "obstcaculosenmov.h"
extern juego *Juego;
obstcaculosenmov::obstcaculosenmov(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX= Juego->jugador->getPX()+800;
    PY= 480;
    setPos(PX,PY);
    setPixmap(QPixmap(":/escarabajo2.png"));
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
    timer->start(100);
    cont=0;
}

float obstcaculosenmov::getPY() const
{
    return PY;
}

void obstcaculosenmov::setPY(float value)
{
    PY = value;
}

void obstcaculosenmov::mover()
{
    PX=PX-8;
    setPos(PX,PY);
    cont++;
    if(cont<3){this->setPixmap(QPixmap(":/escarabajo1.png"));}
    if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/escarabajo2.png"));}
    if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/escarabajo3.png")); cont=0;}
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++ )
    {
        if (typeid(*(colliding_items[i])) == typeid(momia))
        {
            scene()->removeItem(this);
            delete this;
           Juego->restar_vidas();
           if(Juego->control->vidas==0)
           {
               Juego->timer1->stop();
               Juego->timer2->stop();
               Juego->timer3->stop();
               Juego->timer_Plataforma->stop();
           }
        }
        if (typeid(*(colliding_items[i])) == typeid(objcaida))
        {
            scene()->removeItem(this);
            delete this;
        }
    }
    if(PX==0)       //LLEgo al final de la pantalla
    {
        scene()->removeItem(this);
        delete this;

    }

}

float obstcaculosenmov::getPX() const
{
    return PX;
}

void obstcaculosenmov::setPX(float value)
{
    PX = value;
}
