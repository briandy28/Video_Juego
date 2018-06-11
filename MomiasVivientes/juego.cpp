#include "juego.h"
#include "ui_juego.h"
#include "niveles.h"
#include <string>
#include <iostream>
#include <fstream>

extern juego *Juego;
extern niveles *ventana;
using namespace std;
juego::juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::juego)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(10,10,1000,500);
    scene->setBackgroundBrush(QBrush(QImage(":/N1")));
    ui->graphicsView->setScene(scene);
    jugador=new momia();

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
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo"));
    scene->addItem(suelo);

    col=true;
    mover=false;
    saltar=false;
    lanzar=false;
    saltoparabolico=false;
    opc_multijugador = false;

    cont=0;
    contventana=0;
    dt2=0;
    tipo_mov1 = 0; // 1 mover derecha, 0 no mover, 2 mover izq
    tipo_mov2 = 0;

    ui->punt->setText(QString("0"));
    ui->N_Bombas->setText(QString("10"));
    control=new controldejuego(0,3,10);
    salto= new QMediaPlayer(this);
    salto->setVolume(100);
    salto->setMedia(QUrl("qrc:/salto.mp3"));
    lanzar2 = new QMediaPlayer();
    lanzar2->setMedia(QUrl("qrc:/lanzar.mp3"));

    QSize size(1000, 500);
    lluvia = new QMovie(":/lluvia.gif");
    lluvia->setScaledSize(size);
    ui->gotas->setMovie(lluvia);
}

juego::~juego(){delete ui;}

void juego::sumar_puntaje()
{
    control->puntaje+=1;
    control->num_Bombas+=1;
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);
    int numero_bombas =control->num_Bombas;
    QString mostrar_bombas;
    mostrar_bombas= QString::number(numero_bombas);
    ui->N_Bombas->setText(mostrar_bombas);
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
    ui->vidasJ1->clear();
    ui->vidasJ2_4->clear();
    scene->addItem(jugador);
    timer1->start(40);                  //Timer de actualizar
    timer2->start(2500);                //Timer de gemas
    timer3->start(50000);                //Timer de animales
    timer_Plataforma->start(2500);      //Timer de Plataformas
}

void juego::nivel2()
{
    ui->vidasJ1->clear();
    ui->vidasJ2_4->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/N2.jpg")));
    scene->setSceneRect(jugador->getPX(),10,1000,500);
    suelo->setPx_base(-40);
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/sueloN2.jpg"));

    jugador->setPos(0,370);
    scene->addItem(jugador);

    mover=false;
    saltar=false;
    lanzar=false;

    lluvia->start();
    timer1->start(40);
    timer2->start(2500);
    timer3->start(30000);
    timer_Plataforma->start(2500);

}

void juego::nivel3()
{
    ui->vidasJ1->clear();
    ui->vidasJ2_4->clear();

    scene->setBackgroundBrush(QBrush(QImage(":/N3.jpg")));
    suelo->setPx_base(-40);
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo.jpg"));

    scene->addItem(jugador);
    jugador->setPos(0,370);

    mover=false;
    saltar=false;
    lanzar=false;

    lluvia->start();
    timer1->start(40);
    timer2->start(2500);
    timer3->start(30000);
    timer_Plataforma->start(5000) ;
}

void juego::multijugador()
{
    ui->label->clear();
    ui->punt->clear();
    ui->label_2->clear();
    ui->N_Bombas->clear();
    ui->vidasJ2->setPixmap(QPixmap(":/vidas.png"));
    ui->vidasJ2_2->setPixmap(QPixmap(":/vidas.png"));
    ui->vidasJ2_3->setPixmap(QPixmap(":/vidas.png"));
    control->control_multijugador(3,3);
    opc_multijugador = true;
    jugador =new momia();
    scene->addItem(jugador);
    jugador2 = new momia();
    jugador2->setPixmap(QPixmap(":/Donald2_1.png"));
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
       if(plataformas.size()!=0)
       {
       for(int i=0;i<int(plataformas.size());i++)
       {
          scene->removeItem(plataformas.at(i));
       }
       }
       plataformas.clear();
       if(plataformitas.size()!=0)
       {
       for(int i=0;i<int(plataformitas.size());i++)
       {
          scene->removeItem(plataformitas.at(i));
       }
       }
       plataformitas.clear();
       ventana->show();
       contventana = 4;
       close();
   }
}

void juego::avanzar2()
{
    if(int(control->puntaje)==(20)){ contventana++;qDebug()<<"cuando esta en la funcion"<<contventana;}
    if(contventana==1)
    {
         //Se debe parar los stop y eliminar todos los objetos
        timer1->stop();
        timer2->stop();
        timer3->stop();
        timer_Plataforma->stop();
        lluvia->stop();
        qDebug()<<"llego aca........"<<plataformas.size();       
        if(plataformas.size()!=0){
        for(int i=0;i<int(plataformas.size());i++)
        {
           scene->removeItem(plataformas.at(i));
        }
        }
        qDebug()<<"antes";
        plataformas.clear();
        qDebug()<<"despues";
        if(plataformitas.size()!=0)
        {
        for(int i=0;i<int(plataformitas.size());i++)
        {
           scene->removeItem(plataformitas.at(i));
        }
        }
        qDebug()<<"antes";
        plataformitas.clear();
        ventana->show();
        close();

    }
}

void juego::colision()
{

    if(int(plataformas.size())!=0)
    {
        for(int i =0;i<int(plataformas.size());i++)
        {

           if(jugador->collidesWithItem(plataformas.at(i)))
            {
                jugador->setPY(plataformas.at(i)->getPy_base()-170);
                jugador->setPos(jugador->getPX(),jugador->getPY());
                col=false;
                saltar=false;
                saltoparabolico =false;
                break;
            }
            else{
                col=true;
                if(int(jugador->getPY())!=370 && saltar==false && saltoparabolico == false)
                    {
                    jugador->setPY(370);jugador->setPos(jugador->getPX(),jugador->getPY());
                    }
            }
       }       
   }
    if(int(plataformitas.size())!=0)
    {
        for(int i =0;i<int(plataformitas.size());i++)
        {

           if(jugador->collidesWithItem(plataformitas.at(i)))
            {
               jugador->setPX(plataformitas.at(i)->getPx_base()-200);
               jugador->setPos(jugador->getPX(),jugador->getPY());
               break;
            }
       }
   }

}

void juego::vidas_multijugador()
{
    if(control->vidas==2){ui->vida3->clear();}
    if(control->vidas==1){ui->vida2->clear();}
    if(control->vidas==0){ui->vida1->clear();}
    if(control->vidasjugador2==2){ui->vidasJ2_3->clear();}
    if(control->vidasjugador2==1){ui->vidasJ2_2->clear();}
    if(control->vidasjugador2==0){ui->vidasJ2->clear();}


}

void juego::cargar_juego()
{
    //Mostrar Puntaje en el ui
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);

    //Mostrar Cantidad de Vidasen el ui
    if(control->vidas==2){ui->vida3->clear();}
    if(control->vidas==1){ui->vida2->clear();ui->vida3->clear();}
    if(control->vidas==0){ui->vida1->clear();ui->vida2->clear();ui->vida3->clear();}
    /*Mostrar mensaje que no permita jugar*/
}


void juego::generar()
{
    gema *gema1 = new gema();
    gema1->setPX(plataformas.last()->getPx_base()+80);
    gema1->setPY(plataformas.last()->getPy_base()-8);
    gema1->setPos(gema1->getPX(),gema1->getPY());
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
    escarabajo->iniciar1();
    if(control->puntaje>=10)
    {
      obstcaculosenmov *escarabajo2 = new obstcaculosenmov();
      escarabajo2->setPY(400);
      escarabajo->setPX(1300);
      escarabajo2->setPos(escarabajo2->getPX(),escarabajo->getPY());
      scene->addItem(escarabajo2);
      escarabajo2->iniciar2();
    }
    if(control->puntaje>=20)
    {
      obstcaculosenmov *bola = new obstcaculosenmov();
      bola->setPixmap(QPixmap(":/bolaenelaire.png"));
      bola->setPY(10);
      bola->setPX(500);
      bola->setPos(bola->getPX(),bola->getPY());
      scene->addItem(bola);
      bola->iniciar3();
    }

}

void juego::generar_plataforma()
{
    base * plataforma = new base();
    if(int(plataformas.size())==0){plataforma->setPx_base(1200);}
    else{plataforma->setPx_base(plataformas.last()->getPx_base() + 1100);}
    plataformas.append(plataforma);
    plataforma->setPos(plataformas.last()->getPx_base(), plataformas.last()->getPy_base());
    scene->addItem(plataformas.last());
    base * plataforma2 = new base();
    plataforma2->setPixmap(QPixmap(":/barraPequeñita.png"));
    plataforma2->setPx_base(plataforma->getPx_base()-2);
    plataforma2->setPy_base(plataforma->getPy_base());
    plataformitas.append(plataforma2);
    plataforma2->setPos(plataformitas.last()->getPx_base(), plataformitas.last()->getPy_base());
    scene->addItem(plataformitas.last());
}

//1 mover derecha, 0 no mover, 2 mover izq
void juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_W ){saltar = true;salto->play();}
    if( event->key() == Qt::Key_Q ){saltoparabolico = true;salto->play();}
    if( event->key() == Qt::Key_D ){ mover = true, tipo_mov1=1;}
    if( event->key() == Qt::Key_A ){ mover = true, tipo_mov1=2;}
    if(event->key()==Qt::Key_E){
        if(control->num_Bombas>0)
        {
            lanzar2->play();
            objcaida* bola = new objcaida();
            bola->setPY(jugador->getPY());
            bola->setPos(bola->getPX(),bola->getPY());
            scene->addItem(bola);
            bola->iniciar1();
            jugador->lanzar();
            control->num_Bombas--;
            //ui->N_Bombas;
            int numero_bombas =control->num_Bombas;
            QString mostrar_bombas;
            mostrar_bombas= QString::number(numero_bombas);
            ui->N_Bombas->setText(mostrar_bombas);
        }
    }

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
        bola->iniciar2();
        jugador2->lanzar_multij();
        scene->addItem(bola);}

}

void juego::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_D ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_A ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_E ){ jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_J ){ mover_j2 = false; jugador2->setPixmap(QPixmap(":/Donald2_1.png"));}
    if( event->key() == Qt::Key_L ){ mover_j2 = false; jugador2->setPixmap(QPixmap(":/Donald2_1.png"));}
    if( event->key() == Qt::Key_U ){ jugador2->setPixmap(QPixmap(":/Donald2_1.png"));}
}

void juego::on_actionGuardar_Juego_triggered()
{
    QFile file("videojuego.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream texto(&file);
    texto<<control->puntaje<<QString(" ");
    texto<<control->vidas;
    file.close();
}
