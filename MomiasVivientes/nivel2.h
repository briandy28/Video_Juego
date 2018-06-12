#ifndef NIVEL2_H
#define NIVEL2_H

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
class nivel2;
}

class nivel2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit nivel2(QWidget *parent = 0);
    ~nivel2();
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
    QGraphicsScene *scene;
    bool sumar, opc_multijugador,nivel2_;
    int contventana;
    int cont, tipo_mov1 ,tipo_mov2;
    momia* jugador;
    QList<base*> plataformas;
    QList<base*> plataformitas;
    base* suelo;


private:
    Ui::nivel2 *ui;
    bool mover, saltar,lanzar,saltoparabolico,col;
    float dt,dt2;
    int cont_obstaculos ;
    QMediaPlayer* salto;
    QMediaPlayer* lanzar2;
    QMovie* lluvia;
    aviso* aviso_;

public slots:
    void generar();
    void actualizar();
    void generar_obst();
    void generar_plataforma();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_actionGuardar_Juego_n2_triggered();
    void on_btn_GuardarN2_clicked();
};

#endif // NIVEL2_H
