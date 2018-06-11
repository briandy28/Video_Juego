#include "niveles.h"
#include "ui_niveles.h"
extern juego *Juego;
extern niveles *ventana;
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
    if(Juego->control->puntaje == 0)
    {
        Juego->nivel1();
        Juego->show();
        close();
    }

}

void niveles::on_nivel2_clicked()
{
    if(Juego->control->puntaje==10)
    {
       Juego->nivel2();
       Juego->show();
       close();
    }
}

void niveles::on_nivel3_clicked()
{
    if(Juego->control->puntaje == 20)
    {
        Juego->nivel3();
        Juego->show();
        close();
    }
}

void niveles::verificar_nivel()
{

    if(int(Juego->control->puntaje)==10)
    {
        nivel2++;
        if(nivel2==1){ Juego->avanzar(); }
    }
    else if(int(Juego->control->puntaje)==20)
    {
        nivel3++;
        if(nivel3==1){ Juego->contventana=0; Juego->avanzar2(); }
    }
}
