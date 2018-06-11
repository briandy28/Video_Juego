#ifndef AVISO_H
#define AVISO_H

#include <QWidget>

namespace Ui {
class aviso;
}

class aviso : public QWidget
{
    Q_OBJECT

public:
    explicit aviso(QWidget *parent = 0);
    ~aviso();

private:
    Ui::aviso *ui;
};

#endif // AVISO_H
