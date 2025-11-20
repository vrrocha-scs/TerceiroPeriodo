#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "evento.hpp" 

class MinHeap {
private:
    Evento vetor[1000];//verificar
    int tamanho;
public:
    MinHeap();
    MinHeap(Evento[] , int n);

    void inserir(Evento& obj);
    Evento extrair_minimo();
    void Troca(int i, int j);
    void ajustar_para_baixo(int i);
    void ajustar_para_cima(int i);
    bool esta_vazia() const { // Verifica se o tamanho é 0
        return tamanho == 0;
    }
};

#endif