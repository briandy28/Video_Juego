#include "niveles.h"
#include "ui_niveles.h"
extern juego *nivel1;
niveles::niveles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);
}

niveles::~niveles()
{
    delete ui;
}

void niveles::on_nivel1_clicked()
{
    nivel1->nivel1();
    nivel1->show();
    close();

}

void niveles::on_nivel2_clicked()
{
    if(nivel1->control->puntaje==50)
    {

    }
}

void niveles::on_nivel3_clicked()
{
    if(nivel1->control->puntaje==100)
    {

    }
}
