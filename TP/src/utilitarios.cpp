#include "utilitarios.hpp"
#include <cmath> 

double distanciaEuclidiana(double origemX, double origemY, double destinoX, double destinoY) {
    return sqrt(pow(destinoX - origemX, 2.0) + pow(destinoY - origemY, 2.0));
}