#include "insertion.hpp"
#include "cena.hpp"
#include <iostream>

//metodo auxiliar
#define Troca(A, B) { \
  Objeto c = A; \
  A = B; \
  B = c; \
}
  
//metodo de ordenação por id
void Insertion_id(Cena v[], int n) {
    int i, j;
    Cena aux;
    for (i = 1; i < n; i++) {
        aux = v[i];
        j = i - 1;
        while (j >= 0 && (aux.id < v[j].id)) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}