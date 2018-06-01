#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include "gema.h"
#include "momia.h"
#include "controldejuego.h"
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
    QTimer* timer1;
    QTimer* timer2;
    void sumar_puntaje();
    bool sumar;

private:
    Ui::juego *ui;
    QGraphicsScene *scene;
    momia* jugador;
    bool mover, saltar;
    float dt;
    int vidas;
    controldejuego *control;


public slots:
    void generar();
    void actualizar();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // JUEGO_H
