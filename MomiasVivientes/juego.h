#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include "gema.h"
#include "momia.h"
#include "controldejuego.h"
#include "obstcaculosenmov.h"
#include <QString>

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
    controldejuego *control;
    void sumar_puntaje();
    void restar_vidas();
    bool sumar;
    momia* jugador;

private:

    QGraphicsScene *scene;
    bool mover, saltar;
    float dt;
    int cont;
public slots:
    void generar();
    void actualizar();
    void generar_obst();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // JUEGO_H
