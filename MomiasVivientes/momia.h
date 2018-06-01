#ifndef MOMIA_H
#define MOMIA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>

class momia : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit momia(QObject *parent = nullptr);
    float PX,PY;
    void mover();
    void saltar(float dt);

signals:

public slots:
};

#endif // MOMIA_H
