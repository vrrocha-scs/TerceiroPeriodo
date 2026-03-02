#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "logradouro.hpp" 

class MinHeap {
private:
    Logradouro** vetor;
    int tamanho;
    int capacidade;

    void Troca(int i, int j);
    void ajustar_para_baixo(int no_pai);
    void ajustar_para_cima(int no_filho);

public:
    MinHeap(int capacidadeMaxima);
    MinHeap(Logradouro** arr,int n);
    ~MinHeap();
    void inserir(Logradouro* log);
    Logradouro* extrair_minimo();

    bool esta_vazia() const{ // Verifica se o tamanho é 0
        return tamanho == 0;
    }
};

#endif