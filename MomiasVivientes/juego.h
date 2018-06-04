#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include <QString>
#include <QMediaPlayer>
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
    controldejuego *control;
    void sumar_puntaje();
    void restar_vidas();
    void explosion(int x,int y);
    void nivel1();
    void nivel2();
    bool sumar;
    momia* jugador;
    QList<base*> plataformas;
    base* suelo;

private:
    QGraphicsScene *scene;
    bool mover, saltar,lanzar;
    float dt;
    int cont;
    QMediaPlayer* salto;
    QMediaPlayer* lanzar2;

public slots:
    void generar();
    void actualizar();
    void generar_obst();
    void generar_plataforma();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // JUEGO_H
