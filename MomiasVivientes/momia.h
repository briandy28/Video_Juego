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

    void mover();
    void saltar(float dt);
    void setPX(float value);
    void setPY(float value);
    float getPY() const;
    float getPX() const;
private:
    float PX;
    float PY;
    int cont;

signals:

public slots:
};

#endif // MOMIA_H
