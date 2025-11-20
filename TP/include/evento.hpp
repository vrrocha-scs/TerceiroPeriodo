#ifndef EVENTO_HPP
#define EVENTO_HPP
#include "parada.hpp"

class Evento{
    public:
    double tempo;
    int tipo;
    int idCorrida;
    int idPassageiro;

    Evento() : tempo(0) , tipo(0), idCorrida(-1), idPassageiro(-1){};

    Evento(double _tempo, int _tipo, int _idCorrida, int _idPassageiro):tempo(_tempo),tipo(_tipo),idCorrida(_idCorrida),idPassageiro(_idPassageiro){}
};

#endif