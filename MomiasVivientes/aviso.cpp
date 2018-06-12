/*Esta clase permite generar un aviso informativo de forma emergente, para bridar
al usuario informacion del proceso en el juego o si ya termino de jugar */

#include "aviso.h"
#include "ui_aviso.h"
#include "niveles.h"
#include "controldejuego.h"
extern controldejuego *control;
extern niveles *ventana;

/*Constructor para generar aviso cuando gana el nivel y puede pasar al siguiente*/
aviso::aviso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aviso)
{
    ui->setupUi(this);  
    QSize size(426, 186);
    ganaste = new QMovie(":/ganaste.gif");
    ganaste->setScaledSize(size);
    ui->gano->setMovie(ganaste);
    ganaste->start();
}

aviso::~aviso()
{
    delete ui;
}


/*Metodo que se encarga de generar aviso cuando se terminan las vidas disponibles y termmino el juego*/
void aviso::perdiste()
{
    ui->setupUi(this);
    QSize size(470, 200);
    ganaste = new QMovie(":/GameOver.gif");
    ganaste->setScaledSize(size);
    ui->gano->setMovie(ganaste);
    ganaste->start();
}

void aviso::multijugador2()
{
    ui->momia->setPixmap(QPixmap(":/jugador2_momia.png"));
}

void aviso::multijugador1()
{
    ui->momia->setPixmap(QPixmap(":/Donald_momia.png"));
}

/*Metodo que se encarga de cerrar la ventana emergente generada*/
void aviso::on_ok_clicked()
{
    close();
    this->~aviso();
}
