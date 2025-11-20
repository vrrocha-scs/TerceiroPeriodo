#include <iostream>
#include <cmath>
#include <iomanip>
#include "demanda.hpp"
#include "minheap.hpp"
#include "corrida.hpp"
#include "utilitarios.hpp"
using namespace std;


int main(){
    int capacidade=0,numDemandas=0,numCorridasCriadas=0;
    double velocidade=0.0,intervMax=0.0,distMaxO=0.0,distMaxD=0,eficienciaMin=0.0;   

    cin>>capacidade>>velocidade>>intervMax>>distMaxO>>distMaxD>>eficienciaMin>>numDemandas;

    Demanda* todasDemandas = new Demanda[numDemandas];
    Corrida* corridas = new Corrida[numDemandas];
    bool* demandaAtendida = new bool[numDemandas];

    for(int i=0;i<numDemandas;i++){//le as demandas
        int idAux=0,tempo_aux=0;
        double origemXAux=0,origemYAux=0,destinoXAux=0,destinoYAux=0;
        cin>>idAux>>tempo_aux>>origemXAux>>origemYAux>>destinoXAux>>destinoYAux;
        todasDemandas[i]=Demanda(idAux,tempo_aux,origemXAux,origemYAux,destinoXAux,destinoYAux);
        demandaAtendida[i]=false;
    } 

    MinHeap escalador;

    for(int i=0;i<numDemandas;i++){//montar corridas
        if(demandaAtendida[i]) continue;
        Corrida& auxCorrida = corridas[numCorridasCriadas];//cria corrida com construtor default
        auxCorrida.inicializar(capacidade);
        
        Demanda c0=todasDemandas[i];
        auxCorrida.AdicionaPassageiro(c0);
        demandaAtendida[i]=true;

        for(int j=i+1;j<numDemandas && auxCorrida.ocupantes<capacidade;j++){//encontrar os proximos passageiros de uma corrida
            if(demandaAtendida[j]) continue;
            Demanda candidato = todasDemandas[j];

            if(candidato.tempo-c0.tempo>=intervMax){//verifica restrição de tempo
                break;  
            }
            
            bool distanciaExcedida = false;
            for(int k=0;k<auxCorrida.ocupantes;k++){//verifica restricao de distancia com os passageiros que ja estao na corrida 
                Demanda passageiro = auxCorrida.passageiros[k];
                if(distanciaEuclidiana(passageiro.origemX,passageiro.origemY,candidato.origemX,candidato.origemY)>distMaxO || distanciaEuclidiana(passageiro.destinoX,passageiro.destinoY,candidato.destinoX,candidato.destinoY)>distMaxD){
                    distanciaExcedida=true;
                    break;
                }
            }
            if(!distanciaExcedida){
                auxCorrida.AdicionaPassageiro(candidato);

                if(auxCorrida.eficienciaCorrida()<eficienciaMin){
                    auxCorrida.removePassageiro();
                    break;
                }else{
                    demandaAtendida[j]=true;
                }
            }
        }

        Evento primeiroEvento = auxCorrida.getPrimeiroEvento(numCorridasCriadas);
        escalador.inserir(primeiroEvento);

        numCorridasCriadas++;

        auxCorrida.construirTrecho();
    }

    cout << fixed << setprecision(2);

    while(!escalador.esta_vazia()){
        Evento eventoAtual= escalador.extrair_minimo();
        Corrida& corridaAtual = corridas[eventoAtual.idCorrida];

        Evento proximoEvento;//proxima parada
        bool corridaTerminou = corridaAtual.processarProximoEvento(eventoAtual, velocidade, proximoEvento);

        if(corridaTerminou){//gera as estatisticas da corrida
            corridaAtual.eficienciaCorrida();
            double distanciaFinal = corridaAtual.distanciaTotal;
            double tempoConclusao = eventoAtual.tempo;
            int numParadas = corridaAtual.ocupantes * 2;
            cout << tempoConclusao << " " << distanciaFinal << " " << numParadas << " "; //imprime as estatisticas da corrida
            corridaAtual.imprimeParada(); //imprime as informações de parada
        }else{
            escalador.inserir(proximoEvento);
        }
    }
}