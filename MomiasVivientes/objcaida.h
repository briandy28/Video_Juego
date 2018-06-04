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
#include "base.h"
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

private:
    float PX,PY,dt;
    QTimer *TimerLlamas;
    bool mover2;
    int cont,cont2;
    QMediaPlayer* sonido;
signals:

public slots:
    void mover();
};

#endif // OBJCAIDA_H
