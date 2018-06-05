#ifndef NIVELES_H
#define NIVELES_H

#include <QWidget>
#include<QTimer>
#include "juego.h"
#include "inicio.h"

namespace Ui {
class niveles;
}

class niveles : public QWidget
{
    Q_OBJECT

public:
    explicit niveles(QWidget *parent = 0);
    ~niveles();

private slots:
    void on_nivel1_clicked();

    void on_nivel2_clicked();

    void on_nivel3_clicked();
    void verificar_nivel();

private:
    Ui::niveles *ui;
    QTimer* verificar;
};

#endif // NIVELES_H
