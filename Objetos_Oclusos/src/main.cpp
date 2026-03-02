#include "cena.hpp"
#include "objeto.hpp"
#include "insertion.hpp"
#include "minheap.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

int processa_cena(Cena saida[], Objeto objeto[], int tamanho);

#define MaxTam 1000

int main(){
   
   int elementos_inoclusos=0;
   Objeto objeto[MaxTam]; // Vetor de todos os objetos
   string linha;
   int tamanho=0,aux_tempo=0;
   Cena saida[MaxTam];

   while(true){ //loop de leitura do programa
      char tipo;
      cin>>tipo;

      if(tipo!='O' && tipo!='M' && tipo!='C'){
        cerr<<"Entrada invalida, digite entradas 'O', 'M' ou 'C'"<<endl;
      }
      else{
        if(tipo=='O'){ // Cadastro de Objeto
          if(tamanho<MaxTam){
            int aux_id;
            double aux_centro_x, aux_eixo_y, aux_largura;
            cin>>aux_id>>aux_centro_x>>aux_eixo_y>>aux_largura;
            objeto[tamanho]=Objeto(aux_id,aux_centro_x,aux_eixo_y,aux_largura);
            tamanho++;
          }
          else
          cerr<<"Limite Maximo Atingido"<<endl;
        }
        else if(tipo=='M'){ // Movimentação de Objeto
          int aux_id;
          double aux_centro_x, aux_eixo_y;

          cin>>aux_tempo>>aux_id>>aux_centro_x>>aux_eixo_y;
          for(int i=0;i<tamanho;i++){
          if(aux_id==objeto[i].identificador){
              objeto[i].movimenta_objeto(aux_id,aux_centro_x,aux_eixo_y);
              break;
            }
          }
        }
        else if(tipo=='C'){ // Geração da Cena
          elementos_inoclusos = processa_cena(saida, objeto, tamanho);//processamento da cena, retorna um vetor de saida  
          cin>>aux_tempo;
          for(int i=0;i<elementos_inoclusos;i++){
            cout<<'S'<<" "<<aux_tempo<<" "<<saida[i].id<<" "<< fixed << setprecision(2)<<saida[i].comeco<<" "<<saida[i].fim<<endl;
          }
        }
      }
   }
   return 0;
}