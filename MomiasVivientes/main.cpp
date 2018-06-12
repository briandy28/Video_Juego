#include "mainwindow.h"
#include "juego.h"
#include "nivel2.h"
#include "niveles.h"
#include "controldejuego.h"
#include "nivel3.h"
#include <QApplication>
controldejuego *control;
MainWindow *s;
juego *Juego;
niveles *ventana;
nivel2 * Nivel2;
nivel3 * Nivel3;


/* En este emtodo se estan declaraon declarando externas las clases para poder usarlas en las otras */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s = new MainWindow;
    Juego=new juego();
    Nivel2 = new nivel2();
    Nivel3 = new nivel3();
    ventana=new niveles();
    control=new controldejuego(0,3,10);
   // s->show();
    return a.exec();
}
