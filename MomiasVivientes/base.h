#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsScene>
#include <typeinfo>
#include <QDebug>
#include<QGraphicsTextItem>

class base : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit base(QGraphicsItem *parent = nullptr);
    float getPx_base() const;
    float getPy_base() const;
    void setPx_base(float value);
    void setPy_base(float value);

private:
    float Px_base;
    float Py_base;
    QTimer *eliminar;
public slots:
//    void remover_plataforma();

};

#endif // BASE_H
