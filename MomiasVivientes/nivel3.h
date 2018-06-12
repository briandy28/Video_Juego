#ifndef NIVEL3_H
#define NIVEL3_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include <QString>
#include <QMediaPlayer>
#include <Qmovie>
#include <Qsize>
#include <QFile>
#include <QTextStream>
#include <time.h>

#include "gema.h"
#include "momia.h"
#include "obstcaculosenmov.h"
#include "objcaida.h"
#include "base.h"
#include "aviso.h"

namespace Ui {
class nivel3;
}

class nivel3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit nivel3(QWidget *parent = 0);
    ~nivel3();
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* timer_Plataforma;
    QTimer* nivel;
    void sumar_puntaje();
    void restar_vidas();
    void avanzar2();
    void colision();
    void cargar_juego();
    void iniciar_timer();
    void iniciar_puntaje();
    bool sumar, opc_multijugador, nivel3_;
    int contventana;
    int cont, tipo_mov1 ,tipo_mov2;
    momia* jugador;
    QList<base*> plataformas;
    QList<base*> plataformitas;
    base* suelo;

private:
    Ui::nivel3 *ui;
    bool mover, saltar,lanzar,saltoparabolico,col;
    QGraphicsScene *scene;
    float dt,dt2;
    QMediaPlayer* salto;
    QMediaPlayer* lanzar2;
    QMovie* lluvia;
    aviso* aviso_;
    int cont_obstaculos ;
public slots:
    void generar();
    void actualizar();
    void generar_obst();
    void generar_plataforma();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_actionGuardar_Juego_n3_triggered();
};

#endif // NIVEL3_H
