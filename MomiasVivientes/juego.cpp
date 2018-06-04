#include "juego.h"
#include "ui_juego.h"
#include <string>
extern juego *nivel1;
using namespace std;
juego::juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(10,10,1000,500);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/N1")));
    jugador=new momia();
    scene->addItem(jugador);
    timer1=new QTimer();
    connect(timer1,SIGNAL(timeout()),this,SLOT(actualizar()));
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()),this,SLOT(generar()));
    timer3 = new QTimer();
    connect(timer3, SIGNAL(timeout()),this,SLOT(generar_obst()));
    timer_Plataforma = new QTimer();
    connect(timer_Plataforma, SIGNAL(timeout()), this, SLOT(generar_plataforma()));
    suelo = new base();
    suelo->setPx_base(-40);
    suelo->setPy_base(500);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo"));
    scene->addItem(suelo);
    mover=false;
    saltar=false;
    lanzar=false;
    ui->punt->setText(QString("0"));
    control=new controldejuego(0,3);
    cont=0;
    salto= new QMediaPlayer(this);
    salto->setVolume(100);
    salto->setMedia(QUrl("qrc:/salto.mp3"));
    lanzar2 = new QMediaPlayer();
    lanzar2->setMedia(QUrl("qrc:/lanzar.mp3"));
}

juego::~juego(){delete ui;}

void juego::sumar_puntaje()
{
    int numero =control->puntaje+=1;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);
}

void juego::restar_vidas()
{
 control->vidas--;
 if(control->vidas==2){ui->vida3->clear();}
 if(control->vidas==1){ui->vida2->clear();}
 if(control->vidas==0){ui->vida1->clear();}
}

void juego::nivel1()
{
    timer1->start(40);
    timer2->start(2500);
    timer3->start(30000);
    timer_Plataforma->start(5000);
}

void juego::nivel2()
{
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer_Plataforma->stop();
    scene->removeItem(jugador);
    scene->removeItem(suelo);
    for(int i=0;i<int(plataformas.size());i++)
    {
        scene->removeItem(plataformas.at(i));
    }
    scene->clear();

}


void juego::generar()
{
    gema *gema1 = new gema();
    scene->addItem(gema1);
}

void juego::actualizar()
{
    if (saltar)
    {
        jugador->saltar(dt);
        dt+=0.1;
        jugador->setPos( jugador->getPX(), jugador->getPY());
    }
    if (jugador->getPY()>390)
    {
        saltar = false;
        jugador->setPY(370);
        dt=0;
        jugador->setPos(jugador->getPX(),jugador->getPY());
    }
    if(mover){jugador->mover();}
    //opcion para el movimiento del fondo y el piso junto con la momia
     scene->setSceneRect(jugador->getPX(),10,1000,500);
     suelo->setPx_base(jugador->getPX()-40);
     suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
}

void juego::generar_obst()
{
   obstcaculosenmov *escarabajo = new obstcaculosenmov();
   scene->addItem(escarabajo);
}

void juego::generar_plataforma()
{
    base * plataforma = new base();
    if(int(plataformas.size())==0){plataforma->setPx_base(jugador->getPX() + 1100);}
    else{plataforma->setPx_base(plataformas.last()->getPx_base() + 1100);}
    plataformas.append(plataforma);
    plataforma->setPos(plataformas.last()->getPx_base(), plataformas.last()->getPy_base());
    scene->addItem(plataformas.last());
}

void juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W ){saltar = true;salto->play();}
    if( event->key() == Qt::Key_D ){ mover = true;}
    if(event->key()==Qt::Key_E){
        lanzar2->play();
        objcaida* bola = new objcaida();
        jugador->lanzar();
        scene->addItem(bola);}
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_D ){ mover = false; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_E ){ jugador->setPixmap(QPixmap(":/Donald1.png"));}
}
