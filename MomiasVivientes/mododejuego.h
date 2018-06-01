#ifndef MODODEJUEGO_H
#define MODODEJUEGO_H

#include <QWidget>
#include "juego.h"

namespace Ui {
class modoDeJuego;
}

class modoDeJuego : public QWidget
{
    Q_OBJECT

public:
    explicit modoDeJuego(QWidget *parent = 0);
    ~modoDeJuego();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::modoDeJuego *ui;
};

#endif // MODODEJUEGO_H
