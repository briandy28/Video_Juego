#ifndef INICIO_H
#define INICIO_H
#include<QMainWindow>
#include <QWidget>
#include<QGraphicsItem>
#include <QGraphicsScene>
#include "mododejuego.h"
#include<qDebug>

namespace Ui {
class inicio;
}

class inicio : public QWidget
{
    Q_OBJECT

public:
    explicit inicio(QWidget *parent = 0);
    ~inicio();

private slots:
    void on_pushButton_clicked();

    void on_opc1_1_clicked();

    void on_opc1_2_clicked();

    void on_opc1_3_clicked();

    void on_opc2_1_clicked();

    void on_opc2_2_clicked();

    void on_opc3_1_clicked();

    void on_opc3_2_clicked();

    void on_opc3_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::inicio *ui;
    QGraphicsTextItem * mensaje;
    QGraphicsScene* scene;

    bool resp1;
    bool resp2;
    bool resp3;
};

#endif // INICIO_H
