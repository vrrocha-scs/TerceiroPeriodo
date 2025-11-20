#include "minheap.hpp" 
#include <iostream> 
#define MaxTam 1000

MinHeap::MinHeap(Evento arr[], int n) { // construtor da Heap (usando Evento)
    tamanho = n;
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = arr[i];
    }
    for (int i = tamanho / 2 - 1; i >= 0; --i) {
        ajustar_para_baixo(i);
    }
}

MinHeap::MinHeap() : tamanho(0) {}

void MinHeap::Troca(int i, int j) {//função de troca
    Evento temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

void MinHeap::ajustar_para_baixo(int no_pai) {
    int indice_esquerda = 2 * no_pai + 1;
    int indice_direita = 2 * no_pai + 2;
    int menor_indice = no_pai;

    //verifica se o menor valor de y é do indice pai
    if (indice_esquerda < tamanho && vetor[indice_esquerda].tempo < vetor[no_pai].tempo)
        menor_indice = indice_esquerda;
    if (indice_direita < tamanho && vetor[indice_direita].tempo < vetor[menor_indice].tempo)
        menor_indice = indice_direita;

    //realiza a troca de valores caso contrario(abaixando o maior valor no heap)  
    if (menor_indice != no_pai) {
        Troca(no_pai, menor_indice); 
        ajustar_para_baixo(menor_indice);
    }
}

void MinHeap::ajustar_para_cima(int no_filho) {
    int no_pai = (no_filho - 1) / 2;
    while (no_filho > 0 && vetor[no_filho].tempo < vetor[no_pai].tempo) {//verifica se o filho é menor que o pai
        Troca(no_filho, no_pai);//sobe o no filho no heap
        no_filho = no_pai;
        no_pai = (no_filho - 1) / 2;
    }
}

void MinHeap::inserir(Evento& obj) {//insere no final da heap o novo elemento
    if (tamanho < MaxTam) { 
        vetor[tamanho] = obj;
        tamanho++;
        ajustar_para_cima(tamanho - 1);//ordena o elemento na heap
    }
    else 
        std::cerr<<"Limite Maximo Atingido"<<std::endl;

}

Evento MinHeap::extrair_minimo(){
    if (tamanho == 1) {
        tamanho--;
        return vetor[0];
    }
    Evento raiz = vetor[0];
    vetor[0] = vetor[tamanho - 1];//v[0]=ultimo elemento do heap
    tamanho--;//remove o ultimo elemento
    ajustar_para_baixo(0);//ajusta o elemento que esta na primeira posicao(deveria estar na ultima)

    return raiz;//retorna efetivamente o valor da posicao 0 (raiz) do heap
}

