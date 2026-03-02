#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "objeto.hpp" 

class MinHeap {
private:
    Objeto vetor[1000];
    int tamanho;

    void Troca(int i, int j);
    void ajustar_para_baixo(int i);
    void ajustar_para_cima(int i);

public:
    MinHeap();
    MinHeap(Objeto arr[], int n);
    void inserir(Objeto& obj);
    Objeto extrair_minimo();

    bool esta_vazia() const { // Verifica se o tamanho é 0
        return tamanho == 0;
    }
};

#endif