#ifndef DEMANDA_H
#define DEMANDA_H

class Demanda{
   public:
    
    Demanda(int _id,int _tempo,double _origemX,double _origemY, double _destinoX, double _destinoY):id(_id),tempo(_tempo),origemX(_origemX),origemY(_origemY),destinoX(_destinoX),destinoY(_destinoY),atendida(false){};
    Demanda():id(0),tempo(0),origemX(0.0),origemY(0.0),destinoX(0.0),destinoY(0.0),atendida(false){}

    int id;
    int tempo;
    double origemX, origemY, destinoX, destinoY;
    bool atendida;//retorna se ja foi direcionado para uma corrida
    int estadoAtual;    
};

#endif