#ifndef JUEGO_H
#define JUEGO_H

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

#include "gema.h"
#include "momia.h"
#include <time.h>
#include "obstcaculosenmov.h"
#include "objcaida.h"
#include "base.h"
#include "aviso.h"

namespace Ui {
class juego;
}

class juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego(QWidget *parent = 0);
    ~juego();
    QMediaPlayer *sonido;
    Ui::juego *ui;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* timer_Plataforma;
    QTimer* nivel;
    void sumar_puntaje();
    void restar_vidas();
    void explosion(int x,int y);
    void nivel1();
    void nivel2();
    void nivel3();
    void multijugador();
    void avanzar();
    void avanzar2();
    void colision();
    void vidas_multijugador();
    void cargar_juego();
    void iniciar_puntaje();
    bool sumar, opc_multijugador, nivel1_;
    int contventana;
    momia* jugador;
    momia* jugador2;
    QList<base*> plataformas;
    QList<base*> plataformitas;
    base* suelo;
    aviso* aviso_;

private:
    bool mover, saltar,lanzar,saltoparabolico,col, mover_j2, saltar_j2, lanzar_j2, saltoparabolico_j2;
    QGraphicsScene *scene;
    float dt,dt2;
    int cont, tipo_mov1 ,tipo_mov2;
    QMediaPlayer* salto;
    QMediaPlayer* lanzar2;
    QMovie* lluvia;

public slots:
    void generar();
    void actualizar();
    void generar_obst();
    void generar_plataforma();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_actionGuardar_juego_Nivel1_triggered();
};

#endif // JUEGO_H
