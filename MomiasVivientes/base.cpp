#include "base.h"

base::base(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    Px_base = 800;
    Py_base = 370+rand()%30;        // entre 290 y 400
    setPixmap(QPixmap(":/barraPequeña.png"));
    setPos(Px_base,Py_base);
}

base::~base()
{
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
