/* Esta clase permirte darle un manejo al personaje principal que es la momia, en esta
se cambian las imagenes en abse al tipo de movimiento para asi simular movimento fluido */

#include "momia.h"
#include "juego.h"
extern juego* Juego;

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

/* Metodo constructor de la clase en el cual se asignan valores inciales*/
momia::momia(QObject *parent) : QObject(parent)
{
    PX=0;
    PY=370;
    setPos(PX,PY);
    setPixmap(QPixmap(":/Donald1.png"));
    cont=0;
    cont2=0;
}

/* Metodo encargado de realizar el movimiento lectilineo en la momia, tambien permite para la
opcion de multijugador moverse hacia la izquierda*/
void momia::mover(int tipo_mov)
{
    if(tipo_mov == 1){      //Movimiento hacia la DERECHA
        PX=PX+8;
        setPos(PX,PY);
        cont++;
        if(cont<3){this->setPixmap(QPixmap(":/Donald3.png"));}
        if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/Donald2.png"));}
        if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/Donald4.png")); cont=0;}

    }
    if(tipo_mov == 2){      //Movimiento hacia la IZQUIERDA
        PX=PX-8;
        setPos(PX,PY);
        cont++;
        if(cont<3){this->setPixmap(QPixmap(":/Donald3.png"));}
        if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/Donald2.png"));}
        if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/Donald4.png")); cont=0;}

    }
}

/* Metodo encargado de realizar el movimiento lectilineo en direccion vertical en la momia */
void momia::saltar(float dt)
{
    PY = PY -25*dt + 9.8*dt*dt ;
        this->setPos(PY,PX);
        this->setPixmap(QPixmap(":/Donald1.png"));
}

/* Metodo encargado de realizar el movimiento parabolico en la momia, cambiando asi
 su posicion en X y Y*/
void momia::saltar_parabolico(float dt)
{
    PY = PY -25*dt + 9.8*dt*dt ;
    PX=PX+8;
    this->setPos(PY,PX);
    this->setPixmap(QPixmap(":/Donald1.png"));
}

/* Metodo encargado de realizar el lanzamiento en la momia, simulando asi el cambio de
 su posicion en X y Y de la mano */
void momia::lanzar()
{
    cont2++;
//   if(cont2<1){this->setPixmap(QPixmap(":/lanzar1.png"));}
    if(cont2<1){this->setPixmap(QPixmap(":/lanzar2.png"));}
//    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar3.png"));}
    if(cont2>=1 && cont<2){this->setPixmap(QPixmap(":/lanzar4.png"));}
    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar5.png"));}
    if(cont2>=3 && cont2<4){this->setPixmap(QPixmap(":/lanzar6.png"));cont2=0;}
}


/*Metodos para Multijugador- JUGADOR 2
Estos metodos son el mismo tipo de moviento que los metodos anteriores, solo que aplican solamente
cuando se selecciona la opvion de multijugador*/

void momia::mover_multij(int tipo_mov)
{
    if(tipo_mov == 1){          //Movimiento hacia la DERECHA
        PX=PX+8;
        setPos(PX,PY);
        cont++;
        if(cont<3){this->setPixmap(QPixmap(":/Donald2_2.png"));}
        if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/Donald2_3.png"));}
        if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/Donald2_4.png")); cont=0;}

    }
    if(tipo_mov == 2){          //Movimiento hacia la IZQUIERDA
        PX=PX-8;
        setPos(PX,PY);
        cont++;
        if(cont<3){this->setPixmap(QPixmap(":/Donald2_2.png"));}
        if(cont>=3 && cont<9){this->setPixmap(QPixmap(":/Donald2_3.png"));}
        if(cont>=9 && cont<12){this->setPixmap(QPixmap(":/Donald2_4.png")); cont=0;}

    }
}

void momia::saltar_multij(float dt)
{
    PY = PY -25*dt + 9.8*dt*dt ;
    this->setPos(PY,PX);
    this->setPixmap(QPixmap(":/Donald2_1.png"));
}

void momia::saltar_parabolico_multij(float dt)
{
    PY = PY -25*dt + 9.8*dt*dt ;
    PX=PX-8;
    this->setPos(PY,PX);
    this->setPixmap(QPixmap(":/Donald2_1.png"));}

void momia::lanzar_multij()
{
    cont2++;
//   if(cont2<1){this->setPixmap(QPixmap(":/lanzar1.png"));}
    if(cont2<1){this->setPixmap(QPixmap(":/lanzar2_2.png"));}
//    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar2_3.png"));}
    if(cont2>=1 && cont<2){this->setPixmap(QPixmap(":/lanzar2_4.png"));}
    if(cont2>=2 && cont2<3){this->setPixmap(QPixmap(":/lanzar2_5.png"));}
    if(cont2>=3 && cont2<4){this->setPixmap(QPixmap(":/lanzar2_6.png"));cont2=0;}
}


