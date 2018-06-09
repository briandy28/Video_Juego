#include "mododejuego.h"
#include "ui_mododejuego.h"
#include "juego.h"
extern niveles *ventana;
extern juego *Juego;
modoDeJuego::modoDeJuego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modoDeJuego)
{
    ui->setupUi(this);
}

modoDeJuego::~modoDeJuego()
{
    delete ui;
}

void modoDeJuego::on_pushButton_2_clicked()
{
    //un jugador
   ventana->show();
   close();
}

void modoDeJuego::on_pushButton_clicked()
{//multijugador
    Juego->multijugador();
    Juego->show();
    close();
}

void modoDeJuego::on_pushButton_Cargar_clicked()
{
    QString info;                       //String para leer los datos del archivo
    QFile file("videojuego.txt");       //Objeto para manejar la lectura del archivo
    file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
    info=file.readLine();
    int n;
    //while(n>=0){      //Ciclo para guardar cada dato de la linea de texto en su posicion correspondiente en el arreglo vec

    n = info.indexOf(" ");
    Juego->control->puntaje = info.left(n).toInt();
    Juego->control->vidas = info.right(n).toInt();

    if(Juego->control->puntaje<10)
    {
        Juego->nivel1();
        Juego->cargar_juego();
        Juego->show();
        close();
    }
    else
        if(Juego->control->puntaje>=10 || Juego->control->puntaje<20)
        {
            Juego->nivel2();
            Juego->cargar_juego();
            Juego->show();
            close();
        }
        else
            if(Juego->control->puntaje>=20)
            {
                //Juego->nivel3();
                Juego->cargar_juego();
                Juego->show();
                close();
            }





//}
//    info>>Juego->control->puntaje;

//    info=file.readLine();
//    info>>Juego->control->vidas;

    //qDebug<<Juego->control->puntaje<<","<<Juego->control->vidas;

//    QFile filea("videojuego.txt");
//    filea.open(QIODevice::ReadOnly);
//    QTextStream texto(&filea);
////    filea >> control->puntaje;
//    while (!texto.atEnd()) {
//        QString line = texto.readLine();
////        control->puntaje(line);
//        texto>>control->puntaje;
//    }
}
