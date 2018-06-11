#ifndef CONTROLDEJUEGO_H
#define CONTROLDEJUEGO_H

class controldejuego
{
public:
    controldejuego(int pnt, int vi, int bombas);
    int puntaje, vidas,vidasjugador2,num_Bombas;
    void control_multijugador(int vidas1,int vidas2);
};

#endif // CONTROLDEJUEGO_H
