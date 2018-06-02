#ifndef OBSTCACULOSENMOV_H
#define OBSTCACULOSENMOV_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>
#include "momia.h"
#include "juego.h"

class obstcaculosenmov: public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
private:
    float PX, PY;
    QTimer* timer;
    int cont;
public:
    explicit obstcaculosenmov(QGraphicsItem *parent = nullptr);

    float getPX() const;
    void setPX(float value);
    float getPY() const;
    void setPY(float value);
public slots:
    void mover();
};


#endif // OBSTCACULOSENMOV_H
