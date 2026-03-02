#ifndef TABELAHASH_HPP
#define TABELAHASH_HPP

struct NoHash {
    int idLog;//ID do logradouro(chave)
    int indiceVetor;//Posição no vetor principal(Valor)
    NoHash* proximo;//Ponteiro para o próximo (em caso de colisão)

    NoHash(int id, int idx) : idLog(id), indiceVetor(idx), proximo(nullptr) {}
};

class TabelaHash {
private:
    int tamanho;
    NoHash** tabela;

public:
    TabelaHash(int tam = 20011);
    ~TabelaHash();

    int buscar(int idLog);//retorna o indice do vetor

    void inserir(int idLog, int indiceVetor);
};

#endif