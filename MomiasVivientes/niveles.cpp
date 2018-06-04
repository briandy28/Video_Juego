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

}

niveles::~niveles()
{
    delete ui;
}

void niveles::on_nivel1_clicked()
{
    Juego->nivel1();
    Juego->show();
    close();

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
    if(Juego->control->puntaje==100)
    {

    }
}

void niveles::verificar_nivel()
{

    if(int(Juego->control->puntaje)==10)
    {
        Juego->avanzar();
    }
    if(int(Juego->control->puntaje)==60)
    {
         Juego->avanzar();
    }
}
