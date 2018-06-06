#include "inicio.h"
#include "ui_inicio.h"

inicio::inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
    this->showMaximized();
    sonido=new QMediaPlayer();
    sonido->setMedia(QUrl("qrc:/Egyptian music.mp3"));
    sonido->setVolume(100);
    sonido->play();

}

inicio::~inicio()
{
    delete ui;
}

void inicio::on_opc1_1_clicked(){resp1=false;}
void inicio::on_opc1_2_clicked(){resp1=true;}
void inicio::on_opc1_3_clicked(){resp1=false;}
void inicio::on_opc2_1_clicked(){resp2=true;}
void inicio::on_opc2_2_clicked(){resp2=false;}
void inicio::on_opc3_1_clicked(){resp3=false;}
void inicio::on_opc3_2_clicked(){resp3=true;}
void inicio::on_opc3_3_clicked(){resp3=false;}
void inicio::on_pushButton_clicked()
{
    qDebug()<< "resp 1 "<<resp1;
    qDebug()<< "resp 2 "<<resp2;
    qDebug()<< "resp 3 "<<resp3;
    if(resp1==true && resp2==true && resp3==true)

    {
      modoDeJuego *modo= new modoDeJuego();
      modo->show();
      close();
    }
    else

    {
      ui->error->setText(QString(" has fallado "));
    }
}


void inicio::on_pushButton_2_clicked()
{   //reiniciar
    ui->error->clear();
}
