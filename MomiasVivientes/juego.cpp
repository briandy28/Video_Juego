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
    timer1->start(40);
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()),this,SLOT(generar()));
    timer2->start(2500);
    dt=0;
    mover=false;
    saltar=false;
    ui->punt->setText(QString("0"));
    control=new controldejuego(0,3);

}

juego::~juego()
{
    delete ui;
}

void juego::sumar_puntaje()
{
    int numero =control->puntaje+=1;
    QString mostrar;
    mostrar= QString::number(numero);
    qDebug()<<"puntaje "<<mostrar;
    ui->punt->setText(mostrar);

}

void juego::generar()
{
    gema *gema1 = new gema();
    scene->addItem(gema1);
}

void juego::actualizar()
{
    if (saltar) {
        jugador->saltar(dt);
        dt+=0.1;
        jugador->setPos( jugador->PX, jugador->PY);
    }

    if (jugador->PY>390)
    {
        saltar = false;
        jugador->PY=390;
        dt=0;
        jugador->setPos(jugador->PX,jugador->PY);
    }
    if(mover){jugador->mover();}

}

void juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W ){ saltar = true;}
    if( event->key() == Qt::Key_D ){ mover = true;}
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
  if( event->key() == Qt::Key_D ){ mover = false;}
}

