#include "mainwindow.h"
#include "juego.h"
#include <QApplication>
MainWindow *s;
juego *nivel1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s = new MainWindow;
    nivel1=new juego();
   // s->show();
    return a.exec();
}
