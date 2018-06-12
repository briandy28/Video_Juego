#include "gema.h"
#include "nivel2.h"
#include "nivel3.h"
#include "controldejuego.h"
extern juego *Juego;
extern nivel2 *Nivel2;
extern nivel3 *Nivel3;
extern controldejuego *control;
gema::gema(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX= 1000;
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
                if(control->puntaje<=10 && Juego->nivel1_==true)
                {
                    Juego->sumar_puntaje();
                    scene()->removeItem(this);
                    delete this;
                }
                if(control->puntaje>=10 && control->puntaje<=20 && Nivel2->nivel2_==true)
                {
                    Nivel2->sumar_puntaje();
                    scene()->removeItem(this);
                    delete this;
                }
                if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
                {
                    Nivel3->sumar_puntaje();
                    scene()->removeItem(this);
                    delete this;
                }
            }
        }
        ;

        if(PX==0)
        {
            if(control->puntaje<=10 && Juego->nivel1_==true)
            {
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>10 && control->puntaje>=20 && Nivel2->nivel2_==true)
            {
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
            {
                scene()->removeItem(this);
                delete this;
            }
        }
}
