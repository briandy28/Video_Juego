#include "base.h"
#include "juego.h"
extern juego *Juego;
base::base(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    Px_base = 800;
    Py_base = 330+rand()%71;
    setPixmap(QPixmap(":/barraPequeña.png"));
    setPos(Px_base,Py_base);
    eliminar=new QTimer();
    //connect(eliminar, SIGNAL(timeout()), this, SLOT(remover_base()));
    //eliminar->start(40);
}

base::~base()
{
    delete this;
}

void base::remover_base()
{
    if(Juego->control->puntaje == 10)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"eliminado";
    }
}


float base::getPx_base() const
{
    return Px_base;
}
float base::getPy_base() const
{
    return Py_base;
}
void base::setPx_base(float value)
{
    Px_base = value;
}
void base::setPy_base(float value)
{
    Py_base = value;
}

//void base::remover_plataforma()
//{
//    if(Juego->plataformas.size()!=0)
//    {
//        if(Juego->plataformas.first()->getPx_base()==-10)
//    {
//        scene()->removeItem(Juego->plataformas.first());
//        delete Juego->plataformas.first();
//        qDebug()<<"eliminado";
//    }
//    }
//}
