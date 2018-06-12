/*Esta clase permite llevar un control sobre la cantidad de vidas, la cantidad de bombas
 y el puntaje que tiene en el juego*/

#include "controldejuego.h"

/*Constructor que da valores a las vidas, puntaje y numero de bombas en base a parametros enviados */
controldejuego::controldejuego(int pnt,int vi, int bombas)
{
  vidas=vi;
  puntaje=pnt;
  num_Bombas = bombas;

}
/*Metodo que se encarga controlar y asignar valores a las vidas en el modo multijugador */
void controldejuego::control_multijugador(int vidas1,int vidas2)
{
    vidas=vidas1;
    vidasjugador2=vidas2;

}


