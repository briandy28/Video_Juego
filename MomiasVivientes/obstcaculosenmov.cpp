#include "obstcaculosenmov.h"
extern juego *nivel1;
obstcaculosenmov::obstcaculosenmov(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX= nivel1->jugador->getPX()+800;
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
    //qDebug()<<"contador"<<cont;
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
           nivel1->restar_vidas();
           if(nivel1->control->vidas==0)
           {
               nivel1->timer1->stop();
               nivel1->timer2->stop();
               nivel1->timer3->stop();
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
