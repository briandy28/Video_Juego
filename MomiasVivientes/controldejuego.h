#ifndef CONTROLDEJUEGO_H
#define CONTROLDEJUEGO_H

class controldejuego
{
public:
    controldejuego(int pnt,int vi);
    int puntaje, vidas,vidasjugador2;
    void control_multijugador(int vidas1,int vidas2);
};

#endif // CONTROLDEJUEGO_H
