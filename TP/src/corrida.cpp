#include <cmath>
#include <iostream>
#include "corrida.hpp"
using namespace std;

Corrida::Corrida():capacidade(0),ocupantes(0),passageiros(nullptr),trecho(nullptr),distanciaTotal(0.0){}

void Corrida::inicializar(int _capacidade){
    capacidade=_capacidade;
    ocupantes=0;
    IndiceProxParada = 0;
    passageiros = new Demanda[capacidade];
    trecho = new Trecho[2*capacidade-1];
    parada = new Parada[2*capacidade];
}



bool Corrida::AdicionaPassageiro(Demanda _passageiro){
    if(ocupantes<capacidade){
        passageiros[ocupantes]=_passageiro;
        ocupantes++;
        return true;
    }
    return false;
}

void Corrida::removePassageiro(){
    ocupantes--;
}

double Corrida::eficienciaCorrida(){
    double distanciasAvulsas=0.0;
    distanciaTotal=0.0;

    for(int i=0;i<ocupantes;i++){
    distanciasAvulsas+=distanciaEuclidiana(passageiros[i].origemX,passageiros[i].origemY,passageiros[i].destinoX,passageiros[i].destinoY);
    }

    distanciaCorrida();
    
    if(distanciaTotal == 0.0){//para evitar a divisão por 0 no final
        if(distanciasAvulsas == 0.0){
            return 1.0;
        }
        return 0.0;//prevencao para erro onde distancia total é 0.0 e a avulsa é diferente de 0.0
    }

    return distanciasAvulsas/distanciaTotal;
}

void Corrida::distanciaCorrida(){

    distanciaTotal=0.0;

    if(ocupantes==1){
        distanciaTotal=distanciaEuclidiana(passageiros[0].origemX,passageiros[0].origemY,passageiros[0].destinoX,passageiros[0].destinoY);//distancia de so um passageiro
        return;
    }

    for(int i=0;i<ocupantes-1;i++){//distancia entre origens
        distanciaTotal += distanciaEuclidiana(passageiros[i].origemX,passageiros[i].origemY,passageiros[i+1].origemX,passageiros[i+1].origemY);
    }

    distanciaTotal += distanciaEuclidiana(passageiros[ocupantes-1].origemX,passageiros[ocupantes-1].origemY,passageiros[0].destinoX,passageiros[0].destinoY);//distancia da origem do ultimo passageiro ao destino do primeiro
   
    for(int i=0;i<ocupantes-1;i++){//distancia entre os destinos
         distanciaTotal += distanciaEuclidiana(passageiros[i].destinoX,passageiros[i].destinoY,passageiros[i+1].destinoX,passageiros[i+1].destinoY);
    }
}

void Corrida::construirTrecho(){
    parada[0]=Parada(passageiros[0].origemX,passageiros[0].origemY,TIPO_EMBARQUE,passageiros[0].id);//coleta de c0
    for(int i=0;i<ocupantes-1;i++){//trechos + paradas de coleta
        trecho[i]=Trecho(passageiros[i].origemX,passageiros[i].origemY,passageiros[i+1].origemX,passageiros[i+1].origemY,TIPO_EMBARQUE);
        parada[i+1]=Parada(passageiros[i+1].origemX,passageiros[i+1].origemY,TIPO_EMBARQUE,passageiros[i+1].id);
    }

    trecho[ocupantes-1]=Trecho(passageiros[ocupantes-1].origemX,passageiros[ocupantes-1].origemY,passageiros[0].destinoX,passageiros[0].destinoY,TIPO_DESLOCAMENTO);//trecho de deslocamento
    parada[ocupantes]=Parada(passageiros[0].destinoX,passageiros[0].destinoY,TIPO_DESEMBARQUE,passageiros[0].id);//primeira parada de desembarque

    for(int i = 0;i<ocupantes-1;i++){
        trecho[i+ocupantes]=Trecho(passageiros[i].destinoX,passageiros[i].destinoY,passageiros[i+1].destinoX,passageiros[i+1].destinoY,TIPO_ENTREGA);//trecho de deslocamento
        parada[i+ocupantes+1]=Parada(passageiros[i+1].destinoX,passageiros[i+1].destinoY,TIPO_DESEMBARQUE,passageiros[i+1].id);
    }
}

void Corrida::imprimeParada(){
    for(int i=0;i<2*ocupantes;i++){
        cout<<parada[i].coordenadaX<<" "<<parada[i].coordenadaY<<" ";
    }
    cout<<endl;
}

Evento Corrida::getPrimeiroEvento(int numPrimeiroEvento){
        double tempoInicial = passageiros[0].tempo;
        int idPassageiroInicial = passageiros[0].id;
        
        return Evento(tempoInicial,TIPO_EMBARQUE,numPrimeiroEvento,idPassageiroInicial);
}

bool Corrida::processarProximoEvento(Evento eventoAtual, double velocidade, Evento& proximoEvento){
    IndiceProxParada++;//avanca o estado
    
    if(IndiceProxParada == 2*ocupantes){//verifica se é a ultima parada
        return true;//corrida terminou
    }

    //caso a corrida nao tenha terminado, agenda o proximo evento
    Trecho& trechoAtual = trecho[IndiceProxParada-1];
    Parada& paradaSeguinte = parada[IndiceProxParada];//recebe a parada seguinte

    double tempoViagem = trechoAtual.distancia / velocidade;
    double tempoProximoEvento = eventoAtual.tempo + tempoViagem;

    proximoEvento = Evento(tempoProximoEvento,paradaSeguinte.tipo,eventoAtual.idCorrida,paradaSeguinte.passageiroDemanda);
    return false;//indica que a corrida nao terminou
}
