#ifndef OBJETO_H
#define OBJETO_H

class Objeto{
    public:
        int identificador;
        double centro_x;
        double eixo_y;
        double largura; 
        double final;
        double inicio;
        Objeto(int,double,double,double);
        Objeto();
        void movimenta_objeto(int,double,double);
};
 

#endif
