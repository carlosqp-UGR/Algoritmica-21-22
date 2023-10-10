//
// Created by carlosqp on 24/5/22.
//

#ifndef EJERCICIO2_PROBLEMA_H
#define EJERCICIO2_PROBLEMA_H

#include <list>
#include <ostream>

class Problema {
private:
    unsigned int filas, cols;
    std::list<std::pair<int,int>> wall;
    std::list<std::pair<int,int>> gold;

public:
    Problema();

    Problema(const Problema &other);

    Problema(const char *nombre);

    unsigned int getFilas() const;

    unsigned int getCols() const;

    const std::list<std::pair<int, int>> &getWall() const;

    const std::list<std::pair<int, int>> &getGold() const;

    bool isWall(int f, int c) const;

    bool isGold(int f, int c) const;

    friend std::ostream &operator<<(std::ostream &os, const Problema &problema);
};

#endif //EJERCICIO2_PROBLEMA_H
