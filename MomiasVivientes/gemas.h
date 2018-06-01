#ifndef GEMAS_H
#define GEMAS_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>

//#include<QMediaPlayer>


class gemas: public QObject, public QGraphicsPixmapItem
{
public:
    explicit gemas(QGraphicsItem *parent = nullptr);
    QTimer *timer;
    float PX, PY;

public slots:
    void Mover();
};

#endif // GEMAS_H
