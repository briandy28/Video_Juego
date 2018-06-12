/*Esta clase permite generar los escarabajos que se acercan con diferente tipo de movimiento a la momia*/

#include "obstcaculosenmov.h"
#include "controldejuego.h"
#include "nivel2.h"
#include "nivel3.h"

extern juego *Juego;
extern nivel2 *Nivel2;
extern nivel3 *Nivel3;
extern controldejuego *control;

/* Metodo constructor de la clase en el cual se asignan valores inciales necesarios en la clase
cerificando el puntaje para identificar en eque nivel se deben crear*/
obstcaculosenmov::obstcaculosenmov(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    if(control->puntaje<=10){ PX= Juego->jugador->getPX()+1300;}
    if(control->puntaje>10 && control->puntaje<=20){ PX= Nivel2->jugador->getPX()+1300;}
    PY= 480;
    setPos(PX,PY);
    setPixmap(QPixmap(":/escarabajo2.png"));
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(mover()));
    timer->start(100);
    cont=0;
    dt=0;
    timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(mover2()));
    timer3= new QTimer();
    connect(timer3, SIGNAL(timeout()), this, SLOT(mover3()));
    mover_=true;
    sonido= new QMediaPlayer();
    sonido->setMedia(QUrl("qrc:/explosion.mp3"));
    perdiste= new aviso();

}

/* Metodos GET Y SET*/
float obstcaculosenmov::getPY() const
{
    return PY;
}
void obstcaculosenmov::setPY(float value)
{
    PY = value;
}
float obstcaculosenmov::getPX() const
{
    return PX;
}
void obstcaculosenmov::setPX(float value)
{
    PX = value;
}

/* Metodo para inciar el timer 1 */
void obstcaculosenmov::iniciar1()
{
    timer->start(100);
}

/* Metodo para inciar el timer 2 */
void obstcaculosenmov::iniciar2()
{
    timer2->start(100);
}

/* Metodo para inciar el timer 3 */
void obstcaculosenmov::iniciar3()
{
    timer3->start(100);
}

/* Metodo encargado del movimiento del movimiento de los escarabajos que van por el suelo */
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
            if(control->puntaje<=10 && Juego->nivel1_==true)
            {

                Juego->restar_vidas();
                if(control->vidas==0)
                {
                   Juego->timer1->stop();
                   Juego->timer2->stop();
                   Juego->timer3->stop();
                   Juego->timer_Plataforma->stop();
                   perdiste->perdiste();
                   perdiste->show();
                   Juego->close();
                }
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
            {
                Nivel2->restar_vidas();
                if(control->vidas==0)
                {
                   Nivel2->timer1->stop();
                   Nivel2->timer2->stop();
                   Nivel2->timer3->stop();
                   Nivel2->timer_Plataforma->stop();
                   perdiste->perdiste();
                   perdiste->show();
                   Nivel2->close();
                }
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
            {
                Nivel3->restar_vidas();
                if(control->vidas==0)
                {
                   Nivel3->timer1->stop();
                   Nivel3->timer2->stop();
                   Nivel3->timer3->stop();
                   Nivel3->timer_Plataforma->stop();
                   perdiste->perdiste();
                   perdiste->show();
                   Nivel3->close();
                }
                scene()->removeItem(this);
                delete this;
            }

        }
        if (typeid(*(colliding_items[i])) == typeid(objcaida))
        {
            if(control->puntaje<=10 && Juego->nivel1_==true)
            {
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
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
    if(PX==0)       //LLEgo al final de la pantalla
    {
        if(control->puntaje<=10 && Juego->nivel1_==true)
        {
            scene()->removeItem(this);
            delete this;
        }
        if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
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

/* Metodo encargado del movimiento del movimiento de los escarabajos que se van acercando
 * con el movimiento oscilatorio*/
void obstcaculosenmov::mover2()
{

       PX=PX-10;
       amplitud = 20+rand()%81;
       PY=(sin(PX*7)*amplitud)+300;
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
               if(control->puntaje<=10 && Juego->nivel1_==true)
               {

                   Juego->restar_vidas();
                   if(control->vidas==0)
                   {
                      Juego->timer1->stop();
                      Juego->timer2->stop();
                      Juego->timer3->stop();
                      Juego->timer_Plataforma->stop();
                      perdiste->perdiste();
                      perdiste->show();
                      Juego->close();
                   }
                   scene()->removeItem(this);
                   delete this;
               }
               if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
               {
                   Nivel2->restar_vidas();
                   if(control->vidas==0)
                   {
                      Nivel2->timer1->stop();
                      Nivel2->timer2->stop();
                      Nivel2->timer3->stop();
                      Nivel2->timer_Plataforma->stop();
                      perdiste->perdiste();
                      perdiste->show();
                      Nivel2->close();
                   }
                   scene()->removeItem(this);
                   delete this;
               }
               if(control->puntaje>20 && control->puntaje<=30 && Nivel3->nivel3_==true)
               {
                   Nivel3->restar_vidas();
                   if(control->vidas==0)
                   {
                      Nivel3->timer1->stop();
                      Nivel3->timer2->stop();
                      Nivel3->timer3->stop();
                      Nivel3->timer_Plataforma->stop();
                      perdiste->perdiste();
                      perdiste->show();
                      Nivel3->close();
                   }
                   scene()->removeItem(this);
                   delete this;
               }

           }
           if (typeid(*(colliding_items[i])) == typeid(objcaida))
           {
               if(control->puntaje<=10 && Juego->nivel1_==true)
               {
                   cont++;
                   if(cont==10)
                   {
                   scene()->removeItem(this);
                   delete this;
                   cont=0;
                   }
               }
               if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
               {
                   cont++;
                   if(cont==10)
                   {
                   scene()->removeItem(this);
                   delete this;
                   cont=0;
                   }
               }
               if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
               {
                   cont++;
                   if(cont==10)
                   {
                   scene()->removeItem(this);
                   delete this;
                   cont=0;
                   }
               }
           }
       }
       if(PX==0)       //LLEgo al final de la pantalla
       {
           if(control->puntaje<=10 && Juego->nivel1_==true)
           {
               scene()->removeItem(this);
               delete this;
           }
           if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
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

/* Metodo encargado del movimiento del movimiento de los escarabajos que se van acercando
 * con movimiento en caida libre*/
void obstcaculosenmov::mover3()
{

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++ )
    {
        if (typeid(*(colliding_items[i])) == typeid(momia))
        {
            if(control->puntaje<=10 && Juego->nivel1_==true)
            {

                mover_=false;
                cont++;
                if(cont<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont>=2&&cont<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont>=4&&cont<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont>=6&&cont<8){this->setPixmap(QPixmap(":/explosion4.png"));scene()->removeItem(this);delete this;}
                Juego->restar_vidas();
                if(control->vidas==0)
                {
                   Juego->timer1->stop();
                   Juego->timer2->stop();
                   Juego->timer3->stop();
                   Juego->timer_Plataforma->stop();
                   perdiste->perdiste();
                   perdiste->show();
                   Juego->close();
                }

            }
            if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
            {
                mover_=false;
                cont++;
                if(cont<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont>=2&&cont<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont>=4&&cont<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont>=6&&cont<8){this->setPixmap(QPixmap(":/explosion4.png"));scene()->removeItem(this);delete this;}
                Juego->restar_vidas();
                Nivel2->restar_vidas();
                if(control->vidas==0)
                {
                   Nivel2->timer1->stop();
                   Nivel2->timer2->stop();
                   Nivel2->timer3->stop();
                   Nivel2->timer_Plataforma->stop();
                   perdiste->perdiste();
                   perdiste->show();
                   Nivel2->close();
                }

            }
            if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
            {
                mover_=false;
                cont++;
                if(cont<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont>=2&&cont<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont>=4&&cont<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont>=6&&cont<8){this->setPixmap(QPixmap(":/explosion4.png"));scene()->removeItem(this);delete this;}
                Juego->restar_vidas();
                Nivel3->restar_vidas();
                if(control->vidas==0)
                {
                   Nivel3->timer1->stop();
                   Nivel3->timer2->stop();
                   Nivel3->timer3->stop();
                   Nivel3->timer_Plataforma->stop();
                   Nivel3->close();
                   perdiste->perdiste();
                   perdiste->show();
                   Nivel3->close();
                }
            }

        }
            if (typeid(*(colliding_items[i])) == typeid(base))
            {
                if(control->puntaje<=10 && Juego->nivel1_==true)
                {

                    mover_=false;
                    scene()->removeItem(this);
                    delete this;


                }
                if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
                {
                    mover_=false;
                    scene()->removeItem(this);
                    delete this;


                }
                if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
                {
                    mover_=false;
                    scene()->removeItem(this);
                    delete this;
                }

            }
        if (typeid(*(colliding_items[i])) == typeid(objcaida))
        {
            if(control->puntaje<=10 && Juego->nivel1_==true)
            {
                mover_=false;
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
            {
                mover_=false;
                scene()->removeItem(this);
                delete this;
            }
            if(control->puntaje>=20 && control->puntaje<=30 && Nivel3->nivel3_==true)
            {
                mover_=false;
                scene()->removeItem(this);
                delete this;
            }
        }

    }
    if(mover_==true)
    {
        this->setPixmap(QPixmap(":/bolaenelaire.png"));
        PY = PY +35*dt+ 20*dt*dt;
        dt+=0.1;
        setPos(PX,PY);
    }
    if(PX==0)       //LLEgo al final de la pantalla
    {
        if(control->puntaje<=10 && Juego->nivel1_==true)
        {
            scene()->removeItem(this);
            delete this;
        }
        if(control->puntaje>10 && control->puntaje<=20 && Nivel2->nivel2_==true)
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

