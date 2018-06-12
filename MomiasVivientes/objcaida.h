#ifndef OBJCAIDA_H
#define OBJCAIDA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>
#include <QMediaPlayer>
#include "juego.h"

class objcaida : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit objcaida(QGraphicsItem *parent = nullptr);
    float getPX() const;
    void setPX(float value);
    float getPY() const;
    void setPY(float value);
    void iniciar1();
    void iniciar2();

private:
    float PX,PY,dt,dt2;
    QTimer *TimerLlamas,*TimerLlamas2;
    bool mover2,mover3,restarvidas1,restarvidas2;
    int cont,cont2;
    QMediaPlayer* sonido;
signals:

public slots:
    void mover();
    void movver2_();
};

#endif // OBJCAIDA_H
