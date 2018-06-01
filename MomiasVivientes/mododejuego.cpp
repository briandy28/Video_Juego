#include "mododejuego.h"
#include "ui_mododejuego.h"
extern juego *nivel1;
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
   // juego *nivel1= new juego();
    nivel1=new juego();
    nivel1->show();
    close();
}

void modoDeJuego::on_pushButton_clicked()
{//multijugador
    close();
}
