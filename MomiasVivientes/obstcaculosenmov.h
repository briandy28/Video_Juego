#ifndef OBSTCACULOSENMOV_H
#define OBSTCACULOSENMOV_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QMediaPlayer>
#include "momia.h"
#include "juego.h"

class obstcaculosenmov: public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
private:
    float PX, PY,dt;
    QTimer* timer;
    QTimer* timer2;
    QTimer* timer3;
    QMediaPlayer *sonido;
    int cont;
    bool mover_;
public:
    explicit obstcaculosenmov(QGraphicsItem *parent = nullptr);

    float getPX() const;
    void setPX(float value);
    float getPY() const;
    void setPY(float value);
    void iniciar1();
    void iniciar2();
    void iniciar3();

public slots:
    void mover();
    void mover2();
    void mover3();
};


#endif // OBSTCACULOSENMOV_H
