#include "gema.h"
extern juego *nivel1;
gema::gema(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX= nivel1->jugador->getPX()+1000;
    PY= 390;
    setPos(PX,PY);
    setPixmap(QPixmap(":/gema1.png"));
    timergema = new QTimer;
    connect(timergema, SIGNAL(timeout()), this, SLOT(mover()));
    timergema->start(40);
}

float gema::getPX() const
{
    return PX;
}

void gema::setPX(float value)
{
    PX = value;
}

float gema::getPY() const
{
    return PY;
}

void gema::setPY(float value)
{
    PY = value;
}

void gema::mover()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++ )
    {
        if (typeid(*(colliding_items[i])) == typeid(momia))
        {
            scene()->removeItem(this);
            delete this;
            nivel1->sumar_puntaje();
        }
    }
//    PX=PX-8;
//    setPos(PX,PY);

    if(PX==0)       //LLEgo al final de la pantalla
    {
        scene()->removeItem(this);
        delete this;

    }
}
