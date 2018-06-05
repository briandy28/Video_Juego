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
