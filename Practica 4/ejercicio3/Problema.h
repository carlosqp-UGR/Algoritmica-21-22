//
// Created by david on 24/05/22.
//

#ifndef EJERCICIO3_PROBLEMA_H
#define EJERCICIO3_PROBLEMA_H

#include <vector>
#include <string>
#include <fstream>

class Problema {
    private:
        std::vector<int> ValorBateriaTerreno;
        std::vector<std::vector<int>> matrizAux;
        unsigned int columnas, filas, cantidadTerrenosDistintos, bateria;

    public:

        Problema();

        Problema(const Problema &other);

        Problema(const char *nombre);

        const int getColumnas() const;

        const int getFilas() const;

        const std::vector<int> getValorBateriaTerreno() const;

        const std::vector<std::vector<int>> getMatrizAux() const;

        const int getCosteCasilla(int posicion) const;

        const int getBateria() const;


    friend std::ostream &operator<<(std::ostream &os, const Problema &problema);
};


#endif //EJERCICIO3_PROBLEMA_H
