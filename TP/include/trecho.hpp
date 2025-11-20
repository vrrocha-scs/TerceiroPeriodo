#ifndef TRECHO_H
#define TRECHO_H
#include "utilitarios.hpp"

#define TIPO_COLETA 1
#define TIPO_ENTREGA 2
#define TIPO_DESLOCAMENTO 3       

class Trecho{
    public:
    Trecho(double _inicioX,double _inicioY,double _fimX,double _fimY,int _tipo):inicioX(_inicioX),inicioY(_inicioY),fimX(_fimX),fimY(_fimY),tipo(_tipo){
        distancia=distanciaEuclidiana(inicioX,inicioY,fimX,fimY);
    };
    Trecho():inicioX(0.0),inicioY(0.0),fimX(0.0),fimY(0.0),tipo(0),distancia(0){};
    double inicioX,inicioY,fimX,fimY;
    int tipo; 
    double distancia;
};

#endif
