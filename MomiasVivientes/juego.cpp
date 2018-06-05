#include "juego.h"
#include "ui_juego.h"
#include "niveles.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

extern juego *Juego;
extern niveles *ventana;
using namespace std;
juego::juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(10,10,1000,500);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/N1")));
    timer1=new QTimer();
    connect(timer1,SIGNAL(timeout()),this,SLOT(actualizar()));
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()),this,SLOT(generar()));
    timer3 = new QTimer();
    connect(timer3, SIGNAL(timeout()),this,SLOT(generar_obst()));
    timer_Plataforma = new QTimer();
    connect(timer_Plataforma, SIGNAL(timeout()), this, SLOT(generar_plataforma()));
    suelo = new base();
    col=true;
    suelo->setPx_base(-40);
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo"));
    scene->addItem(suelo);
    mover=false;
    saltar=false;
    lanzar=false;
    saltoparabolico=false;
    ui->punt->setText(QString("0"));
    control=new controldejuego(0,3);
    cont=0;
    salto= new QMediaPlayer(this);
    salto->setVolume(100);
    salto->setMedia(QUrl("qrc:/salto.mp3"));
    lanzar2 = new QMediaPlayer();
    lanzar2->setMedia(QUrl("qrc:/lanzar.mp3"));
    QSize size(1000, 500);
    lluvia = new QMovie(":/lluvia.gif");
    lluvia->setScaledSize(size);
    ui->gotas->setMovie(lluvia);
    contventana=0;
    dt2=0;
    opc_multijugador = false;
    tipo_mov1 = 0; // 1 mover derecha, 0 no mover, 2 mover izq
    tipo_mov2 = 0;
}

juego::~juego(){delete ui;}

void juego::sumar_puntaje()
{
    control->puntaje+=1;
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);
    qDebug()<<"puntaje"<<control->puntaje;

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
    jugador=new momia();
    scene->addItem(jugador);
    timer1->start(40);
    timer2->start(2500);
    timer3->start(30000);
    timer_Plataforma->start(10000);
}

void juego::nivel2()
{
    jugador=new momia();
    scene->addItem(jugador);
    suelo = new base();
    suelo->setPx_base(-40);
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo"));
    scene->addItem(suelo);
    mover=false;
    saltar=false;
    lanzar=false;
    QSize size(1000, 500);
    lluvia = new QMovie(":/lluvia.gif");
    lluvia->setScaledSize(size);
    ui->gotas->setMovie(lluvia);
    lluvia->start();
    timer1->start(40);
    timer2->start(2500);
    timer3->start(30000);
    timer_Plataforma->start(5000);

}

void juego::multijugador()
{
    opc_multijugador = true;
    jugador =new momia();
    scene->addItem(jugador);
    jugador2 = new momia();
    jugador2->setPX(500);
    jugador2->setPY(370);
    jugador2->setPos(jugador2->getPX(),jugador2->getPY());
    scene->addItem(jugador2);
    mover_j2 = false;
    saltar_j2= false;
    lanzar_j2= false;
    saltoparabolico_j2= false;
    mover=false;
    saltar=false;
    lanzar=false;
    QSize size(1000, 500);
    lluvia = new QMovie(":/lluvia.gif");
    lluvia->setScaledSize(size);
    ui->gotas->setMovie(lluvia);
    lluvia->start();
    timer1->start(40);
}

void juego::avanzar()
{
   if((control->puntaje)==(10)){ contventana++;}
   if(contventana==1)
   {
        //Se debe parar los stop y eliminar todos los objetos
       timer1->stop();
       timer2->stop();
       timer3->stop();
       timer_Plataforma->stop();
       scene->removeItem(jugador);
       for(int i=0;i<int(plataformas.size());i++)
       {
          scene->removeItem(plataformas.at(i));
       }
       plataformas.clear();
       delete jugador;
       close();
       ventana->show();
   }
}

void juego::colision()
{
   for(int i =0;i<int(plataformas.size());i++)
   {
       if(int(plataformas.size())!=0)
       {
           if(jugador->collidesWithItem(plataformas.at(i)))
            {
                jugador->setPY(plataformas.at(i)->getPy_base()-150);
                jugador->setPos(jugador->getPX(),jugador->getPY());
                col=false;
                saltar=false;
                saltoparabolico =false;
                break;
            }
            else{
            if(int(jugador->getPY())!=370 && saltar==false && saltoparabolico == false)
                {
                jugador->setPY(370);jugador->setPos(jugador->getPX(),jugador->getPY());col=true;
                }
            }
       }
   }
}


void juego::generar()
{
    gema *gema1 = new gema();
    scene->addItem(gema1);
}

void juego::actualizar()
{
    //Un Jugador
    if (saltar)
    {
        jugador->saltar(dt);
        jugador->setPos(jugador->getPX(),jugador->getPY());
        dt+=0.1;
    }
    if(saltoparabolico)
    {
        jugador->saltar_parabolico(dt2);
        jugador->setPos(jugador->getPX(),jugador->getPY());
        dt2+=0.1;
    }
    if (jugador->getPY()>370 && col==true)
    {
        saltar = false;
        saltoparabolico=false;
        jugador->setPY(370);
        dt=0;
        dt2=0;
        jugador->setPos(jugador->getPX(),jugador->getPY());
    }
    if(opc_multijugador){
        if(mover)
        {
            jugador->mover(tipo_mov1);
        }
    }
    else if(mover)
        {
            if(tipo_mov1 == 1){
                jugador->mover(tipo_mov1);
            }
        }


    if(int(plataformas.size())!=0)
    {
        if(plataformas.first()->getPx_base()==-10)
        {
            scene->removeItem(plataformas.first());
            delete plataformas.first();
            qDebug()<<"si entro.................";
        }
    }
    //opcion para el movimiento del fondo y el piso junto con la momia
    if(!opc_multijugador){
        scene->setSceneRect(jugador->getPX(),10,1000,500);
        suelo->setPx_base(jugador->getPX()-40);
        suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
        this->colision();
    }

    //Multijugador
    if(opc_multijugador){
        if (saltar_j2)
        {
            jugador2->saltar_multij(dt);
            jugador2->setPos(jugador2->getPX(),jugador2->getPY());
            dt+=0.1;
        }
        if(saltoparabolico_j2)
        {
            jugador2->saltar_parabolico_multij(dt2);
            jugador2->setPos(jugador2->getPX(),jugador2->getPY());
            dt2+=0.1;
        }
        if (jugador2->getPY()>370 && col==true)
        {
            saltar_j2 = false;
            saltoparabolico_j2=false;
            jugador2->setPY(370);
            dt=0;
            dt2=0;
            jugador2->setPos(jugador2->getPX(),jugador2->getPY());
        }
        if(mover_j2)
        {
            jugador2->mover_multij(tipo_mov2);
        }
    }
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

//1 mover derecha, 0 no mover, 2 mover izq
void juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W ){saltar = true;salto->play();}
    if( event->key() == Qt::Key_Q ){saltoparabolico = true;salto->play();}
    if( event->key() == Qt::Key_D ){ mover = true, tipo_mov1=1;}
    if( event->key() == Qt::Key_A ){ mover = true, tipo_mov1=2;}
    if(event->key()==Qt::Key_E){
        lanzar2->play();
        objcaida* bola = new objcaida();
        jugador->lanzar();
        scene->addItem(bola);}

    //Jugardor 2

    if( event->key() == Qt::Key_I ){saltar_j2 = true;salto->play();}
    if( event->key() == Qt::Key_O ){saltoparabolico_j2 = true;salto->play();}
    if( event->key() == Qt::Key_J ){ mover_j2 = true; tipo_mov2=2;}
    if( event->key() == Qt::Key_L ){ mover_j2 = true; tipo_mov2=1;}
    if(event->key()==Qt::Key_U){
        lanzar2->play();
        objcaida* bola = new objcaida();
        bola->setPX(jugador2->getPX()+100);
        bola->setPos(bola->getPX(),bola->getPY());
        jugador2->lanzar();
        scene->addItem(bola);}

}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_D ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_A ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_E ){ jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_J ){ mover_j2 = false; jugador2->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_L ){ mover_j2 = false; jugador2->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_U ){ jugador2->setPixmap(QPixmap(":/Donald1.png"));}
}

void juego::on_actionGuardar_Juego_triggered()
{
    QFile file("videojuego.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream texto(&file);
    texto<<control->puntaje<<QString("\t puntaje \n");
    texto<<control->vidas<<QString("\t numero de vidas");
    file.close();
}

void juego::on_actionCargar_Juego_triggered()
{
    QFile filea("videojuego.txt");
    filea.open(QIODevice::ReadOnly);
    QTextStream texto(&filea);
//    filea >> control->puntaje;
    while (!texto.atEnd()) {
        QString line = texto.readLine();
//        control->puntaje(line);
        texto>>control->puntaje;
    }

}
