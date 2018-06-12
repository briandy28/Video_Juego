#ifndef AVISO_H
#define AVISO_H

#include <QWidget>
#include <QMovie>
#include <QSize>

namespace Ui {
class aviso;
}

class aviso : public QWidget
{
    Q_OBJECT

public:
    explicit aviso(QWidget *parent = 0);
    ~aviso();
    void perdiste();
    QMovie *ganaste;

private slots:
    void on_ok_clicked();

private:
    Ui::aviso *ui;
};

#endif // AVISO_H
