#include "mainwindow.h"
#include "juego.h"
#include "niveles.h"
#include <QApplication>
MainWindow *s;
juego *Juego;
niveles *ventana;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s = new MainWindow;
    Juego=new juego();
    ventana=new niveles();
   // s->show();
    return a.exec();
}
