#ifndef CORRIDA_H
#define CORRIDA_H
#include "demanda.hpp" 
#include "trecho.hpp"
#include "parada.hpp"
#include "utilitarios.hpp"
#include "evento.hpp"

class Corrida{
public:
    Corrida();
    void inicializar(int);
    ~Corrida(){
        delete[] passageiros;
        delete[] trecho;
        delete[] parada;
    }        
    bool AdicionaPassageiro(Demanda);
    void removePassageiro();
    double eficienciaCorrida();
    void distanciaCorrida();
    void construirTrecho();
    void imprimeParada();
    Evento getPrimeiroEvento(int);
    bool processarProximoEvento(Evento,double,Evento&);

    int IndiceProxParada;
    int capacidade;
    int ocupantes;
    Demanda* passageiros;
    Trecho* trecho; 
    Parada* parada;
    double distanciaTotal;
};



#endif