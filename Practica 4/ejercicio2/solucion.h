//
// Created by carlosqp on 24/5/22.
//

#ifndef EJERCICIO2_SOLUCION_H
#define EJERCICIO2_SOLUCION_H

#include <vector>
#include <ostream>
#include "problema.h"

class Solucion {
private:
    std::vector<std::vector<int>> memoria;
    const Problema problema;

public:
    Solucion();
    Solucion(const Problema &p);
    void calculaMemoria();
    int getMaxGold_Intermediate(int f, int c) const;
    int getMaxGold() const;

    friend std::ostream &operator<<(std::ostream &os, const Solucion &solucion);
};

#endif //EJERCICIO2_SOLUCION_H
