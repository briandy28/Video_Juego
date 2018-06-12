/*Esta clase por medio de la interfaz grafica permite realizar las preguntas de validacion
para el acceso al juego luego de responderlas correctamente */

#include "inicio.h"
#include "ui_inicio.h"

inicio::inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
    this->showMaximized();

}

inicio::~inicio()
{
    delete ui;
}

/* Metodos encargados de asignar la respuesta correcta a las preguntas */
void inicio::on_opc1_1_clicked(){resp1=false;}
void inicio::on_opc1_2_clicked(){resp1=true;}
void inicio::on_opc1_3_clicked(){resp1=false;}
void inicio::on_opc2_1_clicked(){resp2=true;}
void inicio::on_opc2_2_clicked(){resp2=false;}
void inicio::on_opc3_1_clicked(){resp3=false;}
void inicio::on_opc3_2_clicked(){resp3=true;}
void inicio::on_opc3_3_clicked(){resp3=false;}

/* Metodo encargado de verificar si las respuestas estan correctas, de ser asi permite jugar sino avisa
que se fallo en las respustas*/
void inicio::on_pushButton_clicked()
{

    if(resp1==true && resp2==true && resp3==true)

    {
      modoDeJuego *modo= new modoDeJuego();
      modo->show();
      close();
      this->~inicio();
    }
    else

    {
      ui->error->setText(QString(" has fallado "));
    }
}

/* Metodo que permite intentar nuevamente responder las pregunras luego de haber fallado */
void inicio::on_pushButton_2_clicked()
{   //reiniciar
    ui->error->clear();
}
