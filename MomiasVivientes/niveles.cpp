/*Esta clase por medio de la interfaz grafica permite realizar la seleccion del nivel en el cual
 se va a jugar*/

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

/* Metodo constructor de la clase en el cual se asignan valores inciales*/
niveles::niveles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);
    verificar= new QTimer();
    connect(verificar,SIGNAL(timeout()),this,SLOT(verificar_nivel()));
    verificar->start();
    nivel2=0;
    nivel3_=0;
    final= new aviso();
}

/* Metodo destructor de la clase*/
niveles::~niveles()
{
    delete ui;
}
/* Seleccion del nivel 1*/
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

/* Seleccion del nivel 2*/
void niveles::on_nivel2_clicked()
{
    if(control->puntaje==10)
    {
       Juego->~juego();
       Juego->nivel1_=false;
       Nivel2->nivel2_=true;
       Nivel2->iniciar_puntaje();
       Nivel2->iniciar_timer();
       Nivel2->show();
       close();
    }
}

/* Seleccion del nivel 3*/
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

/* Metodo encargado de verificar si ya se llego al puntaje requerido para poder pasar al siguiente nivel
en caso de ser cumplido vuelve a abrir la interfaz para seleccionar otro nivel*/
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
        nivel3_++;
        if(nivel3_==1){Nivel2->avanzar2(); }
    }
    else if(int(control->puntaje)==30)
    {

        final->show();
        Nivel3->close();

    }
}
