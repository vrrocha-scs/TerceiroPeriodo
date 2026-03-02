#ifndef LOGRADOURO_H
#define LOGRADOURO_H
#include <string>
using namespace std;

class Logradouro{
    public:
    int idLog;
    string nome,tipoLog;

    double somaLat,somaLong;
    int quantidadeEnderecos;

    double latMedia,longMedia;

    int contadorIntersecao;
    double distanciaCache;

    Logradouro() : idLog(0), somaLat(0), somaLong(0), quantidadeEnderecos(0), latMedia(0), longMedia(0), contadorIntersecao(0), distanciaCache(0.0) {}
    Logradouro(int _id, string _nome, string _tipoLog) : idLog(_id), nome(_nome), tipoLog(_tipoLog),  somaLat(0), somaLong(0), quantidadeEnderecos(0), latMedia(0), longMedia(0), contadorIntersecao(0),distanciaCache(0.0){}

    void AdicionaEndereco(double lat, double lon){
        somaLat+=lat;
        somaLong+=lon;
        quantidadeEnderecos++;
        latMedia = somaLat/quantidadeEnderecos;
        longMedia = somaLong/quantidadeEnderecos;
    }
};
#endif