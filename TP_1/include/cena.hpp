#ifndef CENA_H
#define CENA_H
#include "objeto.hpp"
#include "insertion.hpp"

class Cena{
    public:
    int id;
    double comeco, fim;
    Cena();  
};
    int gera_cena(Cena[],Objeto[],int,int);
#endif