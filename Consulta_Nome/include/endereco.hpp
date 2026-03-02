#ifndef ENDERECO_H
#define ENDERECO_H
#include <string>
using namespace std;

class Endereco{
    public:
    long long idEnd;
    int idLog, num, cep;
    double latitude, longitude;
    string tipoLog, bairro, regiao, nome;

    Endereco():idEnd(0), idLog(0), num(0), cep(0), latitude(0), longitude(0){};
    Endereco(long long _idEnd, int _idLog, int _Num, int _cep, double _latitude, double _longitude,string _tipoLog,string _nome, string _bairro, string _regiao):idEnd(_idEnd), idLog(_idLog), num(_Num), cep(_cep), latitude(_latitude), longitude(_longitude),tipoLog(_tipoLog),bairro(_bairro),regiao(_regiao),nome(_nome){}
       
};
    
#endif