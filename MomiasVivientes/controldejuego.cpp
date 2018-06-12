#include "controldejuego.h"
controldejuego::controldejuego(int pnt,int vi, int bombas)
{
  vidas=vi;
  puntaje=pnt;
  num_Bombas = bombas;

}

void controldejuego::control_multijugador(int vidas1,int vidas2)
{
    vidas=vidas1;
    vidasjugador2=vidas2;

}


