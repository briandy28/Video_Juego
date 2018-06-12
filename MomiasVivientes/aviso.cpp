#include "aviso.h"
#include "ui_aviso.h"
#include "niveles.h"
#include "controldejuego.h"
extern controldejuego *control;

extern niveles *ventana;
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

void aviso::perdiste()
{
    ui->setupUi(this);
    QSize size(550, 200);
    ganaste = new QMovie(":/GameOver.gif");
    ganaste->setScaledSize(size);
    ui->gano->setMovie(ganaste);
    ganaste->start();
}

void aviso::on_ok_clicked()
{
    close();

}
