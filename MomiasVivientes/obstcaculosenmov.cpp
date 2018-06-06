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
    dt=0;
    timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(mover2()));
    timer3= new QTimer();
    connect(timer3, SIGNAL(timeout()), this, SLOT(mover3()));
    mover_=true;
    sonido= new QMediaPlayer();
    sonido->setMedia(QUrl("qrc:/explosion.mp3"));

}

float obstcaculosenmov::getPY() const
{
    return PY;
}

void obstcaculosenmov::setPY(float value)
{
    PY = value;
}

void obstcaculosenmov::inciar1()
{
    timer->start(100);
}

void obstcaculosenmov::iniciar2()
{
    timer2->start(100);
}

void obstcaculosenmov::iniciar3()
{
    timer3->start(100);
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

void obstcaculosenmov::mover2()
{
       PX=PX-10;
        PY=(sin(PX*7)*50)+300;
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

void obstcaculosenmov::mover3()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; i++ )
        {
            if (typeid(*(colliding_items[i])) == typeid(momia))
            {
                mover_=false;
                cont++;
                if(cont<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont>=2&&cont<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont>=4&&cont<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont>=6&&cont<8){this->setPixmap(QPixmap(":/explosion4.png"));}
                if(cont>=8&&cont<=10){this->setPixmap(QPixmap(":/explosion5.png"));cont=0;}
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
            if (typeid(*(colliding_items[i])) == typeid(base))
            {
                mover_=false;
                cont++;
                if(cont<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
                if(cont>=2&&cont<4){this->setPixmap(QPixmap(":/explosion2.png"));}
                if(cont>=4&&cont<6){this->setPixmap(QPixmap(":/explosion3.png"));}
                if(cont>=6&&cont<8){this->setPixmap(QPixmap(":/explosion4.png"));}
                if(cont>=8&&cont<=10){this->setPixmap(QPixmap(":/explosion5.png"));cont=0;}
                scene()->removeItem(this);
                delete this;
            }
        }
        if(mover_==true)
        {
            PY = PY -35*dt+ 20*dt*dt;
            dt+=0.1;
            setPos(PX,PY);
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
