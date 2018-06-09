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
#include "controldejuego.h"
#include "obstcaculosenmov.h"
#include "objcaida.h"
#include "base.h"

namespace Ui {
class juego;
}

class juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit juego(QWidget *parent = 0);
    ~juego();
    Ui::juego *ui;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    QTimer* timer_Plataforma;
    QTimer* nivel;
    controldejuego *control;
    void sumar_puntaje();
    void restar_vidas();
    void explosion(int x,int y);
    void nivel1();
    void nivel2();
    void multijugador();
    void avanzar();
    void colision();
    void vidas_multijugador();
    void cargar_juego();
    bool sumar,opc_multijugador;
    momia* jugador;
    momia* jugador2;
    QList<base*> plataformas;
    base* suelo;
    QFile archivo;

    //fstream archivo;

private:
    bool mover, saltar,lanzar,saltoparabolico,col, mover_j2, saltar_j2, lanzar_j2, saltoparabolico_j2;
    QGraphicsScene *scene;
    float dt,dt2;
    int cont,contventana, tipo_mov1 ,tipo_mov2;
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
    void on_actionGuardar_Juego_triggered();
    void on_actionCargar_Juego_triggered();
};

#endif // JUEGO_H
