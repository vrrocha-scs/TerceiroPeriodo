#include "palavra.hpp"
#include <iostream> 

IndicePalavras::IndicePalavras() {
    raiz = nullptr;
}

IndicePalavras::~IndicePalavras() {
    destruirRecursivo(raiz);
}

void IndicePalavras::destruirRecursivo(NoPalavra* no) {
    if (no != nullptr) {
        destruirRecursivo(no->esquerda);
        destruirRecursivo(no->direita);
        
        // Limpar a lista encadeada deste nó
        NoLista* atual = no->listaLogradouros;
        while (atual != nullptr) {
            NoLista* aux = atual;
            atual = atual->proximo;
            delete aux;
        }
        delete no;
    }
}

// Funções Auxiliares de AVL
int IndicePalavras::getAltura(NoPalavra* N) {
    if (N == nullptr) return 0;
    return N->altura;
}

int IndicePalavras::maximo(int A, int B) {
    if(A>B) 
        return A;
    else 
        return B;
}

// Rotação Direita
NoPalavra* IndicePalavras::rotacaoDireita(NoPalavra* avo){
    NoPalavra* pai = avo->esquerda;
    NoPalavra* filho = pai->direita;

    // Rotação
    pai->direita = avo;
    avo->esquerda = filho;

    // Atualiza alturas
    avo->altura = maximo(getAltura(avo->esquerda), getAltura(avo->direita)) + 1;
    pai->altura = maximo(getAltura(pai->esquerda), getAltura(pai->direita)) + 1;

    return pai; // Nova raiz (avo esta a direita, o pai esta na raiz e o filho a esquerda do avo)
}

// Rotação Esquerda
NoPalavra* IndicePalavras::rotacaoEsquerda(NoPalavra* avo) {
    NoPalavra* pai = avo->direita;
    NoPalavra* filho = pai->esquerda;

    // Rotação
    pai->esquerda = avo;
    avo->direita = filho;

    // Atualiza alturas
    avo->altura = maximo(getAltura(avo->esquerda), getAltura(avo->direita)) + 1;
    pai->altura = maximo(getAltura(pai->esquerda), getAltura(pai->direita)) + 1;

    return pai; // Nova raiz (avo esta na esquerda, o pai esta na raiz e o filho a direita do avo)
}

int IndicePalavras::getBalanceamento(NoPalavra* N) {
    if (N == nullptr) return 0;
    return getAltura(N->esquerda) - getAltura(N->direita);
}


void IndicePalavras::inserir(string palavra, Logradouro* log) {
    raiz = inserirRecursivo(raiz, palavra, log);
}

NoPalavra* IndicePalavras::inserirRecursivo(NoPalavra* no, string palavra, Logradouro* log) {
    if (no == nullptr) {
        NoPalavra* novo = new NoPalavra(palavra);
        novo->listaLogradouros = new NoLista(log);// Cria o primeiro nó da lista encadeada 
        return novo;
    }

    if (palavra < no->palavra)
        no->esquerda = inserirRecursivo(no->esquerda, palavra, log);
    else if (palavra > no->palavra)
        no->direita = inserirRecursivo(no->direita, palavra, log);
    else {//palavra ja existe (insere na lista)
        if (no->listaLogradouros != nullptr && no->listaLogradouros->logradouro->idLog == log->idLog){//evitar duplicatas ao ler um logradouro
            return no; 
        }
        NoLista* novoItem = new NoLista(log);
        novoItem->proximo = no->listaLogradouros;//insere no inicio da lista
        no->listaLogradouros = novoItem;
        return no; // Retorna o mesmo nó
    }

    no->altura = 1 + maximo(getAltura(no->esquerda), getAltura(no->direita));//atualiza altura do pai

    int balance = getBalanceamento(no);//verifica balanceamento

    //a definição dos casos segue o padrão dado nos slides da aula 19 - Árvores Balanceadas e estarão na documentação do trabalho
    if (balance > 1 && palavra < no->esquerda->palavra)//caso 1 
        return rotacaoDireita(no);

    if (balance < -1 && palavra > no->direita->palavra)//caso 2
        return rotacaoEsquerda(no);

    if (balance > 1 && palavra > no->esquerda->palavra){//caso 3
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balance < -1 && palavra < no->direita->palavra){//caso 4
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no;
}


NoLista* IndicePalavras::buscar(string palavra){
    NoPalavra* atual = raiz;
    while (atual != nullptr){
        if (palavra == atual->palavra) {
            return atual->listaLogradouros; //Retorna a cabeça da lista
        }
        if (palavra < atual->palavra)
            atual = atual->esquerda;
        else
            atual = atual->direita;
    }
    return nullptr; // Não achou
}