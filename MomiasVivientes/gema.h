#ifndef GEMA_H
#define GEMA_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>
#include "momia.h"
#include "juego.h"

class gema : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit gema(QGraphicsItem *parent = nullptr);


private:
    QTimer *timergema;
    float PX,PY;

public slots:
    void mover();
};

#endif // GEMA_H
