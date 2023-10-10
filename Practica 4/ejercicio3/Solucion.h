//
// Created by david on 24/05/22.
//

#ifndef EJERCICIO3_SOLUCION_H
#define EJERCICIO3_SOLUCION_H

#include <vector>
#include "Problema.h"

class Solucion {
private:
    std::vector<std::vector<int>> memoria;
    int bateriaGastada;
    const Problema problema;

public:
    Solucion();
    Solucion(const Problema &p);
    const int getBateriaGastada() const;
    void rellenarCosteCasilla();
    std::string toString();
    void calculaMemoria();

    friend std::ostream &operator<<(std::ostream &os, const Solucion &solucion);
};


#endif //EJERCICIO3_SOLUCION_H
