#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>

class Plataforma : public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT

public:
    explicit Plataforma(QGraphicsItem *parent = nullptr);

    float getPlataf_Px() const;
    float getPlataf_Py() const;
    void setPlataf_Px(float value);
    void setPlataf_Py(float value);

private:
    float Plataf_Px;
    float Plataf_Py;
    QTimer *time_plataforma;

};

#endif // PLATAFORMA_H
