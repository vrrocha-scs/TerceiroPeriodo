#include "objeto.hpp"

Objeto::Objeto() {}

Objeto::Objeto(int _identificador, double _centro_x, double _eixo_y, double _largura) : identificador(_identificador),centro_x(_centro_x), eixo_y(_eixo_y), largura(_largura)
{
    inicio=centro_x-(largura/2);
    final=centro_x+(largura/2); 
}

void Objeto::movimenta_objeto(int _identificador, double _centro_x, double _eixo_y)
{
    centro_x=_centro_x; 
    eixo_y=_eixo_y;
    inicio=_centro_x-(largura/2);
    final=centro_x+(largura/2);
}