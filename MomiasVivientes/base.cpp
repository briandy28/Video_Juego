/*Esta clase permite generar plataformas en los diferentes niveles del juego
 en las cuales el jugador se puede ubicar para porder obtener gemas y ganar puntos,
ademaspermite generar el suelo sobre el cual camina la momia en todos los niveles*/

#include "base.h"

/*Constructor para generar las plataformas y el suelo, los valores se modifican en algunas clases
dependiendo de las necesidades*/
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
//Metodos GET y SET
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
