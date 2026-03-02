#ifndef PARADA_H
#define PARADA_H

#define TIPO_EMBARQUE 0
#define TIPO_DESEMBARQUE 1

class Parada{
    public:

    Parada():coordenadaX(0.0),coordenadaY(0.0),passageiroDemanda(0.0){};
    Parada(double _coordenadaX,double _coordenadaY,int _tipo,int _passageiroDemanda):coordenadaX(_coordenadaX),coordenadaY(_coordenadaY),tipo(_tipo),passageiroDemanda(_passageiroDemanda){};

    double coordenadaX,coordenadaY;
    int tipo; 
    int passageiroDemanda;//verificar
};

#endif