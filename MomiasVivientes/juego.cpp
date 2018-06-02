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
    timer3 = new QTimer();
    connect(timer3, SIGNAL(timeout()),this,SLOT(generar_obst()));
    timer3->start(50000);
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

void juego::restar_vidas()
{
 control->vidas--;
 if(control->vidas==2){ui->vida3->clear();}
 if(control->vidas==1){ui->vida2->clear();}
 if(control->vidas==0){ui->vida1->clear();}
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
    //opcion para el movimiento del fondo junto con la momia
     scene->setSceneRect(jugador->getPX(),10,1000,500);


}

void juego::generar_obst()
{
   obstcaculosenmov *matojo = new obstcaculosenmov();
   scene->addItem(matojo);
}

void juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W ){ saltar = true;}
    if( event->key() == Qt::Key_D ){ mover = true;}
}

void juego::keyReleaseEvent(QKeyEvent *event)
{
  if( event->key() == Qt::Key_D ){ mover = false; jugador->setPixmap(QPixmap(":/Donald1.png"));}
}

