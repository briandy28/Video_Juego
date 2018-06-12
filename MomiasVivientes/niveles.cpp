#include "niveles.h"
#include "ui_niveles.h"
#include "controldejuego.h"
#include "nivel2.h"
#include "nivel3.h"
extern juego *Juego;
extern nivel2 *Nivel2;
extern nivel3 *Nivel3;
extern niveles *ventana;
extern controldejuego *control;
niveles::niveles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);
    verificar= new QTimer();
    connect(verificar,SIGNAL(timeout()),this,SLOT(verificar_nivel()));
    verificar->start();
    nivel2=0;
    nivel3=0;
}

niveles::~niveles()
{
    delete ui;
}

void niveles::on_nivel1_clicked()
{
    if(control->puntaje == 0)
    {
        Juego->iniciar_puntaje();
        Juego->nivel1();

        Juego->nivel1_=true;
        Juego->show();
        close();
    }

}

void niveles::on_nivel2_clicked()
{
    if(control->puntaje==10)
    {
       Juego->~juego();
       Juego->nivel1_=false;
       Nivel3->~nivel3();
       Nivel2->nivel2_=true;
       Nivel2->iniciar_puntaje();
       Nivel2->iniciar_timer();
       Nivel2->show();
       close();
    }
}

void niveles::on_nivel3_clicked()
{
    if(control->puntaje == 20)
    {
        Nivel3->iniciar_puntaje();
        Nivel2->nivel2_=false;
        Nivel2->~nivel2();
        Nivel3->nivel3_=true;
        Nivel3->iniciar_timer();
        Nivel3->show();
        close();
    }
}

void niveles::verificar_nivel()
{

    if(int(control->puntaje)==10)
    {
        nivel2++;
        if(nivel2==1){}
        if(nivel2==2){ Juego->avanzar(); }
    }
    else if(int(control->puntaje)==20)
    {
        nivel3++;
        if(nivel3==1){Nivel2->avanzar2(); }
    }
}
