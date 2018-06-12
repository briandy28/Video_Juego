#include "objcaida.h"
#include "controldejuego.h"
#include "nivel2.h"
#include "nivel3.h"
extern juego *Juego;
extern nivel2 *Nivel2;
extern nivel3 *Nivel3;
extern controldejuego *control;
objcaida::objcaida(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
   if(control->puntaje<10){PX= Juego->jugador->getPX()+100;}
   if(control->puntaje>=10 && control->puntaje<=20){PX= Nivel2->jugador->getPX()+100;}
   if(control->puntaje>=20 && control->puntaje<=30){PX= Nivel3->jugador->getPX()+100;}
    PY= 370;
    dt=0;
    dt2=0;
    setPos(PX,PY);
    setPixmap(QPixmap(":/bola.png"));
    TimerLlamas = new QTimer;
    connect(TimerLlamas, SIGNAL(timeout()), this, SLOT(mover()));
    TimerLlamas2 = new QTimer;
    connect(TimerLlamas2, SIGNAL(timeout()), this, SLOT(movver2_()));
    mover2=true;
    mover3=true;
    restarvidas1=false;
    restarvidas2=false;
    cont=0;
    cont2=0;
    sonido= new QMediaPlayer();
    sonido->setMedia(QUrl("qrc:/explosion.mp3"));

}

float objcaida::getPX() const
{
    return PX;
}

void objcaida::setPX(float value)
{
    PX = value;
}

float objcaida::getPY() const
{
    return PY;
}

void objcaida::setPY(float value)
{
    PY = value;
}

void objcaida::iniciar1()
{
    TimerLlamas->start(60);
}

void objcaida::iniciar2()
{
    TimerLlamas2->start(40);
}

void objcaida::mover()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++ )
    {
        if (typeid(*(colliding_items[i])) == typeid(obstcaculosenmov))
        {
            mover2=false;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));}


        }
        if (typeid(*(colliding_items[i])) == typeid(base))
        {
            mover2=false;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));}

      }
        if(Juego->opc_multijugador==true)
        {
            if (colliding_items[i] == Juego->jugador2)
            {
                mover2=false;
               // qDebug()<<mover2;
                cont++;
                cont2++;
                if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
                if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));restarvidas2=true;}

          }
        }

    }

    if(mover2==true)
    {
    PX=PX+8;
    PY = PY -35*dt+ 20*dt*dt;
    dt+=0.1;
    setPos(PX,PY);
    }

    if(cont==10)
    {
        if(control->puntaje<=10 || Juego->opc_multijugador==true){scene()->removeItem(this);delete this;}
        if(control->puntaje>10 && control->puntaje<=20 && Juego->nivel1_==true){scene()->removeItem(this);delete this;}
        if(control->puntaje>=20 && control->puntaje<=30 && Nivel2->nivel2_==true){scene()->removeItem(this);delete this;}


        if(restarvidas2)
        {
            control->vidasjugador2--;
            Juego->vidas_multijugador();
            if(control->vidasjugador2==0)
            {
                Juego->timer1->stop();
                Juego->timer2->stop();
                Juego->timer3->stop();
                Juego->timer_Plataforma->stop();
            }
            restarvidas2=false;
        }
    }
}

void objcaida::movver2_()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++ )
    {
        if (typeid(*(colliding_items[i])) == typeid(obstcaculosenmov))
        {
            mover3=false;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));}


        }
        if (typeid(*(colliding_items[i])) == typeid(base))
        {
            mover3=false;
           // qDebug()<<mover2;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));}

        }
        if(Juego->opc_multijugador==true)
        {
        if (colliding_items[i] == Juego->jugador)
        {
            mover2=false;
           // qDebug()<<mover2;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));restarvidas1=true;}
      }
      }
    }

    if(mover3==true)
    {
    PX=PX-8;
    PY = PY -35*dt2+ 20*dt2*dt2;
    dt2+=0.1;
    setPos(PX,PY);
    }

    if(cont==10)
    {
        if(control->puntaje<=10 || Juego->opc_multijugador==true){scene()->removeItem(this);delete this;}
        if(control->puntaje>10 && control->puntaje<=20){scene()->removeItem(this);delete this;}
        if(control->puntaje>=20 && control->puntaje<=30){scene()->removeItem(this);delete this;}
        if(restarvidas1)
        {
           control->vidas--;
           Juego->vidas_multijugador();
           if(control->vidas==0)
           {
               Juego->timer1->stop();
               Juego->timer2->stop();
               Juego->timer3->stop();
               Juego->timer_Plataforma->stop();
            }
        }
        restarvidas1=false;
    }
}
