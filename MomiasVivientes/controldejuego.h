#ifndef CONTROLDEJUEGO_H
#define CONTROLDEJUEGO_H

class controldejuego
{
public:
    controldejuego(int pnt, int vi, int bombas);
    int puntaje, vidas, num_Bombas;
    void sumar();
};

#endif // CONTROLDEJUEGO_H
