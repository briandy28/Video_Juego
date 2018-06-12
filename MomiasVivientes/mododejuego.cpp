/* Esta clase permirte selecionar por medio de la intarfaz grafica el modo de juego en
 el cual se desea jugar, ya sea un solo jugador, multijugador o si desea cargar partida*/

#include "mododejuego.h"
#include "ui_mododejuego.h"
#include "juego.h"
#include "controldejuego.h"
#include "nivel2.h"
#include "nivel3.h"

extern nivel2 *Nivel2;
extern nivel3 *Nivel3;
extern niveles *ventana;
extern juego *Juego;
extern controldejuego *control;

/* Metodo constructor de la clase */
modoDeJuego::modoDeJuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modoDeJuego)
{
    ui->setupUi(this);
}

/* Metodo destructor de la clase */
modoDeJuego::~modoDeJuego()
{
    delete ui;
}

/* Opcion para un solo jugador */
void modoDeJuego::on_pushButton_2_clicked()
{
    //un jugador
   ventana->show();
   close();
   this->~modoDeJuego();
}

/* Opcion para multijugador */
void modoDeJuego::on_pushButton_clicked()
{
    //multijugador
    Juego->multijugador();
    Juego->show();
    close();
    this->~modoDeJuego();

}
/* Opcion para cargar partida, lee el aarchivo y carga la partida en el respectivo nivel, en
 base al puntaje guardado*/
void modoDeJuego::on_pushButton_Cargar_clicked()
{
    QString info;                       //String para leer los datos del archivo
    QFile file("videojuego.txt");       //Objeto para manejar la lectura del archivo
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    info=file.readLine();
    int n;

    n = info.indexOf(" ");
    control->puntaje = info.left(n).toInt();
   control->vidas = info.right(n).toInt();
   qDebug()<<control->puntaje;
   qDebug()<<control->vidas;

    if(control->puntaje<10)
    {
        Juego->nivel1();
        Juego->nivel1_=true;
        Juego->cargar_juego();
        Juego->show();
        close();
        this->~modoDeJuego();
    }
    else
        if(control->puntaje>=10 && control->puntaje<20)
        {
            qDebug()<<control->puntaje<<control->vidas<<"entro en puntaje <20";
            Juego->nivel1_=false;
            Nivel2->nivel2_=true;
            Nivel2->iniciar_timer();
            Nivel2->cargar_juego();
            Nivel2->show();
            close();
            this->~modoDeJuego();
        }
        else
            if(control->puntaje>=20)
            {
                qDebug()<<control->puntaje<<control->vidas<<"entro en puntaje >20";
                Juego->nivel1_=false;
                Nivel2->nivel2_=false;
                Nivel3->nivel3_=true;
                Nivel3->iniciar_timer();
                Nivel3->cargar_juego();
                Nivel3->show();
                close();
                this->~modoDeJuego();
            }
}


