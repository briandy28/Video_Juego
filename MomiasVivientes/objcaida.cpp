#include "objcaida.h"
extern juego *nivel1;
objcaida::objcaida(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    PX= nivel1->jugador->getPX()+100;
    PY= 370;
    dt=0;
    setPos(PX,PY);
    setPixmap(QPixmap(":/bola.png"));
    TimerLlamas = new QTimer;
    connect(TimerLlamas, SIGNAL(timeout()), this, SLOT(mover()));
    TimerLlamas->start(40);
    mover2=true;
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
            qDebug()<<mover2;
            cont++;
            cont2++;
            if(cont2<2){this->setPixmap(QPixmap(":/explosion1.png"));sonido->play();}
            if(cont2>=2&&cont2<4){this->setPixmap(QPixmap(":/explosion2.png"));}
            if(cont2>=4&&cont2<6){this->setPixmap(QPixmap(":/explosion3.png"));}
            if(cont2>=6&&cont2<8){this->setPixmap(QPixmap(":/explosion4.png"));}
            if(cont2>=8&&cont2<=10){this->setPixmap(QPixmap(":/explosion5.png"));}

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
        scene()->removeItem(this);delete this;
    }
}
