#include "hash.hpp"

TabelaHash::TabelaHash(int tam) {
    tamanho = tam;
    tabela = new NoHash*[tamanho];
    for(int i = 0; i < tamanho; i++) {
        tabela[i] = nullptr;
    }
}

TabelaHash::~TabelaHash() {
    for(int i = 0; i < tamanho; i++) {
        NoHash* atual = tabela[i];
        while(atual != nullptr) {
            NoHash* temp = atual;
            atual = atual->proximo;
            delete temp;
        }
    }
    delete[] tabela;
}


int TabelaHash::buscar(int idLog) {
    int pos = idLog % tamanho;// Função hash simples
    NoHash* atual = tabela[pos];
    
    while(atual != nullptr) {
        if(atual->idLog == idLog)
            return atual->indiceVetor;
        atual = atual->proximo;
    }
    return -1; // Não encontrado
}

void TabelaHash::inserir(int idLog, int indiceVetor) {
    int pos = idLog % tamanho;
    NoHash* novo = new NoHash(idLog, indiceVetor);
    novo->proximo = tabela[pos];
    tabela[pos] = novo;
}