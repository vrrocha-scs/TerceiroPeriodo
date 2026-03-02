#ifndef PALAVRA_H
#define PALAVRA_H

#include <string>
#include "logradouro.hpp" 

using namespace std;

struct NoLista{//no da lista encadeada
    Logradouro* logradouro; // Aponta para o logradouro original
    NoLista* proximo;
    
    NoLista(Logradouro* _logradouro) : logradouro(_logradouro), proximo(nullptr) {}
    NoLista(): logradouro(nullptr),proximo(nullptr){};

};

struct NoPalavra{//no da arvore AVL
    string palavra;
    NoLista* listaLogradouros; //head da lista encadeada
    int altura;//Para o balanceamento da AVL
    NoPalavra *esquerda, *direita;

    NoPalavra(string palavra) : palavra(palavra), listaLogradouros(nullptr), altura(1), esquerda(nullptr), direita(nullptr) {}
};

class IndicePalavras{//Classe da AVL
    public:
        NoPalavra* raiz;

        IndicePalavras();
        ~IndicePalavras();

        
        int getBalanceamento(NoPalavra* No);
        int maximo(int a, int b);
        int getAltura(NoPalavra* no);

        NoPalavra* rotacaoDireita(NoPalavra* No);
        NoPalavra* rotacaoEsquerda(NoPalavra* No);

        NoPalavra* inserirRecursivo(NoPalavra* no, string palavra, Logradouro* log);//é chamado pela funcao inserir
        void destruirRecursivo(NoPalavra* no);

        void inserir(string palavra, Logradouro* log);
        NoLista* buscar(string palavra); //retorna a lista de ruas daquela palavra
};

#endif