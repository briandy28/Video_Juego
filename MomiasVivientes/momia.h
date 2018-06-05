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

    void mover(int tipo_mov);
    void saltar(float dt);
    void saltar_parabolico(float dt);
    void lanzar();
    void mover_multij(int tipo_mov);
    void saltar_multij(float dt);
    void saltar_parabolico_multij(float dt);
    void lanzar_multij();
    void setPX(float value);
    void setPY(float value);
    float getPY() const;
    float getPX() const;
private:
    float PX;
    float PY;
    int cont, cont2;

signals:

public slots:
};

#endif // MOMIA_H
