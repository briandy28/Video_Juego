/* Esta clase se encarga de cargar el segundo nivel del juego.*/

#include "nivel3.h"
#include "ui_nivel3.h"
#include "controldejuego.h"
extern controldejuego *control;

/* Constructor de la clase, encargado de inicializar todas las variables, timer, agregar la escena, el suelo
y asignar los sonidos que se utilizaran en este nivel */
nivel3::nivel3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::nivel3)
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->setupUi(this);
    srand(time(NULL));
    scene = new QGraphicsScene(10,10,1000,500);
    scene->setBackgroundBrush(QBrush(QImage(":/N3.jpg")));
    ui->graphicsView->setScene(scene);
    jugador=new momia();
    scene->addItem(jugador);
    timer1=new QTimer();
    connect(timer1,SIGNAL(timeout()),this,SLOT(actualizar()));

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()),this,SLOT(generar()));

    timer3 = new QTimer();
    connect(timer3, SIGNAL(timeout()),this,SLOT(generar_obst()));

    timer_Plataforma = new QTimer();
    connect(timer_Plataforma, SIGNAL(timeout()), this, SLOT(generar_plataforma()));

    suelo = new base();
    suelo->setPx_base(-40);
    suelo->setPy_base(525);
    suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
    suelo->setPixmap(QPixmap(":/suelo.jpg"));
    scene->addItem(suelo);
    cont_obstaculos=0;
    col=true;
    mover=false;
    saltar=false;
    lanzar=false;
    saltoparabolico=false;
    opc_multijugador = false;
    nivel3_=false;

    cont=0;
    contventana=0;
    dt2=0;
    tipo_mov1 = 0; // 1 mover derecha, 0 no mover, 2 mover izq
    tipo_mov2 = 0;

    ui->punt->setText(QString("0"));
    ui->N_Bombas->setText(QString("10"));
    salto= new QMediaPlayer(this);
    salto->setVolume(100);
    salto->setMedia(QUrl("qrc:/salto.mp3"));
    lanzar2 = new QMediaPlayer();
    lanzar2->setMedia(QUrl("qrc:/lanzar.mp3"));

    QSize size(1000, 500);
    lluvia = new QMovie(":/lluvia.gif");
    lluvia->setScaledSize(size);
    ui->gotas->setMovie(lluvia);
    aviso_ = new aviso();
}

/* Desctructor de la clase */
nivel3::~nivel3()
{
    delete ui;
}

/*Metodo encargado de sumarle puntaje a la momia y agregarle una bomba a las que tenga en el momneto,
 cada vez que obtenga una gema en su recorrido, el nuevo puntaje lo muestra en el label respectivo
 al igual que el numero de bombas disponible*/
void nivel3::sumar_puntaje()
{
    control->puntaje+=1;
    control->num_Bombas+=1;
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);
    int numero_bombas =control->num_Bombas;
    QString mostrar_bombas;
    mostrar_bombas= QString::number(numero_bombas);
    ui->N_Bombas->setText(mostrar_bombas);
}

/*Metodo encargado de restarle vidas a la momia cada vez que colisiona con un escarabajo, elimina la vida
 e la interfaz correspondiente*/
void nivel3::restar_vidas()
{
    control->vidas--;
    if(control->vidas==2){ui->vida3->clear();}
    if(control->vidas==1){ui->vida1_2->clear();}
    if(control->vidas==0){ui->vida1->clear();}
}

/* Metodo encargado de verfiicar si ya se llego al puntaje necesario para  poder pasar al siguiente nivel,
de ser asi para todos los timer usados remueve los objetos de la escena y abre la nueva ventana*/
void nivel3::avanzar2()
{
    if((control->puntaje)==(10)){ contventana++;}
    timer1->stop();
    timer2->stop();
    timer3->stop();
    timer_Plataforma->stop();
    scene->removeItem(jugador);

    for(int i=0;i<int(plataformas.size());i++)
    {
       scene->removeItem(plataformas.at(i));
    }
    plataformas.clear();
    for(int i=0;i<int(plataformitas.size());i++)
    {
       scene->removeItem(plataformitas.at(i));
    }
    plataformitas.clear();
    aviso_->show();
    contventana = 4;
    close();
}

/* Metodo encargado de verificar si la momia colisiona con las plataformas en el juego, si colisiona por
 con la plataforma por arriba la ubica encima de estao si colisiona por un lado la devuelve d eun golpe
 a una posicion donde pueda saltar */
void nivel3::colision()
{
    if(int(plataformas.size())!=0)
    {
        for(int i =0;i<int(plataformas.size());i++)
        {

           if(jugador->collidesWithItem(plataformas.at(i)))
            {
                jugador->setPY(plataformas.at(i)->getPy_base()-170);
                jugador->setPos(jugador->getPX(),jugador->getPY());
                col=false;
                saltar=false;
                saltoparabolico =false;
                break;
            }
            else{
                col=true;
                if(int(jugador->getPY())!=370 && saltar==false && saltoparabolico == false)
                    {
                    jugador->setPY(370);jugador->setPos(jugador->getPX(),jugador->getPY());
                    }
            }
       }
   }
    if(int(plataformitas.size())!=0)
    {
        for(int i =0;i<int(plataformitas.size());i++)
        {

           if(jugador->collidesWithItem(plataformitas.at(i)))
            {
               jugador->setPX(plataformitas.at(i)->getPx_base()-200);
               jugador->setPos(jugador->getPX(),jugador->getPY());
               break;
            }
       }
   }
}

/*Metodo que permite cargar una partida anteriormente guardada y asignar los valores correspondientes
 el la iterfaz grafica */
void nivel3::   cargar_juego()
{
    //Mostrar Puntaje en el ui
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);

    //Mostrar Cantidad de Vidasen el ui
    if(control->vidas==2){ui->vida3->clear();}
    if(control->vidas==1){ui->vida1_2->clear();ui->vida3->clear();}
    if(control->vidas==0){ui->vida1->clear();ui->vida1_2->clear();ui->vida3->clear();}
    /*Mostrar mensaje que no permita jugar*/
}

/* Metodo encargado en inicializar todos los timer del nivel respectivo*/
void nivel3::iniciar_timer()
{
    lluvia->start();
    timer1->start(40);
    timer2->start(1000);
    timer3->start(3000);
    timer_Plataforma->start(1000);
}

/* Metodo encargado en inicializar los valores de la cantidad de vidas y puntaje en la respectiva interfaz */
void nivel3::iniciar_puntaje()
{
    int numero =control->puntaje;
    QString mostrar;
    mostrar= QString::number(numero);
    ui->punt->setText(mostrar);
    int numero_bombas =control->num_Bombas;
    QString mostrar_bombas;
    mostrar_bombas= QString::number(numero_bombas);
    ui->N_Bombas->setText(mostrar_bombas);
    if(control->vidas==2){ui->vida3->clear();}
    if(control->vidas==1){ui->vida1_2->clear();}
    if(control->vidas==0){ui->vida1->clear();}
}

/* Metodo encargado de generar gemas de forma aleatoria arriba de las plataformas de este nivel */
void nivel3::generar()
{
    gema *gema1 = new gema();
    gema1->setPX(plataformas.last()->getPx_base()+80);
    gema1->setPY(plataformas.last()->getPy_base()-15);
    gema1->setPos(gema1->getPX(), gema1->getPY());
    scene->addItem(gema1);
}

/* Metodo que se encarga del movimento en general de la momia, verfica si presiono alguna tecla para realizar
el respectivo movimiento, esto lo hace para cuando esta en modo un jugador o multijugador */
void nivel3::actualizar()
{
    if (saltar)
    {
        jugador->saltar(dt);
        jugador->setPos(jugador->getPX(),jugador->getPY());
        dt+=0.1;
    }
    if(saltoparabolico)
    {
        jugador->saltar_parabolico(dt2);
        jugador->setPos(jugador->getPX(),jugador->getPY());
        dt2+=0.1;
    }
    if (jugador->getPY()>370 && col==true)
    {
        saltar = false;
        saltoparabolico=false;
        jugador->setPY(370);
        dt=0;
        dt2=0;
        jugador->setPos(jugador->getPX(),jugador->getPY());
    }

    if(mover)
        {
            jugador->mover(tipo_mov1);
        }

    if(int(plataformas.size())!=0)
    {
        if(plataformas.first()->getPx_base()==-10)
        {
            scene->removeItem(plataformas.first());
            delete plataformas.first();
        }
    }
    //opcion para el movimiento del fondo y el piso junto con la momia

        scene->setSceneRect(jugador->getPX(),10,1000,500);
        suelo->setPx_base(jugador->getPX()-40);
        suelo->setPos(suelo->getPx_base(),suelo->getPy_base());
        this->colision();

}

/* Genera escarabajos que se acercan a la momia para atacarla */
void nivel3::generar_obst()
{

    obstcaculosenmov *escarabaj2 = new obstcaculosenmov();
    escarabaj2->setPY(400);
    escarabaj2->setPX(jugador->getPX()+1300);
    escarabaj2->setPos(escarabaj2->getPX(),escarabaj2->getPY());
    scene->addItem(escarabaj2);
    escarabaj2->iniciar2();
    cont_obstaculos++;
}

/* Metodo encargado de generar las plataformas de forma aleatoria de este nivel */
void nivel3::generar_plataforma()
{
    base * plataforma = new base();
    if(int(plataformas.size())==0){plataforma->setPx_base(1200);}
    else{plataforma->setPx_base(plataformas.last()->getPx_base() + 1100);}
    plataformas.append(plataforma);
    plataforma->setPos(plataformas.last()->getPx_base(), plataformas.last()->getPy_base());
    scene->addItem(plataformas.last());
    base * plataforma2 = new base();
    plataforma2->setPixmap(QPixmap(":/barraPequeñita.png"));
    plataforma2->setPx_base(plataforma->getPx_base()-3);
    plataforma2->setPy_base(plataforma->getPy_base());
    plataformitas.append(plataforma2);
    plataforma2->setPos(plataformitas.last()->getPx_base(), plataformitas.last()->getPy_base());
    scene->addItem(plataformitas.last());
}

/* Metodo encargados de verificar si se presiona tecla y asi cambiar  los estados de las banderas
 *  de movimiento*/
void nivel3::keyPressEvent(QKeyEvent *event)
{
    if(control->puntaje>=20 && control->puntaje<30)
    {
     if( event->key() == Qt::Key_W ){saltar = true;salto->play();}
     if( event->key() == Qt::Key_Q ){saltoparabolico = true;salto->play();}
     if( event->key() == Qt::Key_D ){ mover = true, tipo_mov1=1;}
     if(event->key()==Qt::Key_E)
     {
         if(control->num_Bombas>0)
         {
             lanzar2->play();
             objcaida* bola = new objcaida();
             bola->setPY(jugador->getPY());
             bola->setPos(bola->getPX(),bola->getPY());
             scene->addItem(bola);
             bola->iniciar1();
             jugador->lanzar();
             control->num_Bombas--;
             //ui->N_Bombas;
             int numero_bombas =control->num_Bombas;
             QString mostrar_bombas;
             mostrar_bombas= QString::number(numero_bombas);
             ui->N_Bombas->setText(mostrar_bombas);
         }
    }
    }
}

/* Metodo encargados de verificar si se deja de presionar alguna tecla y asi cambiar
 los estados de las banderas de movimiento*/
void nivel3::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_D ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_A ){ mover = false,tipo_mov1 =0; jugador->setPixmap(QPixmap(":/Donald1.png"));}
    if( event->key() == Qt::Key_E ){ jugador->setPixmap(QPixmap(":/Donald1.png"));}
}

/* Metodo encargado de verificar si se presiona la opcion de guardar partida*/
void nivel3::on_actionGuardar_Juego_n3_triggered()
{
    qDebug()<<"entro a funcion guardar de nivel 3 ";
    QFile file("videojuego.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream texto(&file);
    texto<<control->puntaje<<QString(" ");
    texto<<control->vidas;
    texto<<"/n"<<"Puntaje "<<"Vidas";
    file.close();
}
