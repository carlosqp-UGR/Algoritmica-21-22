//
// Created by carlosqp on 24/5/22.
//

#include "problema.h"
#include <fstream>
#include <algorithm>
using namespace std;

Problema::Problema() {
    filas = 0;
    cols = 0;
    wall.empty();   // Evita core
    gold.empty();   // Evita core
}

Problema::Problema(const Problema &other): Problema() {
    filas = other.filas;
    cols = other.cols;
    wall = other.wall;
    gold = other.gold;
}

Problema::Problema(const char *nombre): Problema(){
    ifstream fichero;

    fichero.open(nombre);
    if (fichero) {
        fichero >> filas;
        fichero >> cols;

        int num_walls = 0;
        fichero >> num_walls;
        for(size_t i=0; i<num_walls; ++i) {
            int f, c;
            fichero >> f >> c;
            wall.push_back(pair<int,int>(f,c));
        }

        int num_gold = 0;
        fichero >> num_gold;
        for(size_t i=0; i<num_gold; ++i) {
            int f, c;
            fichero >> f >> c;
            gold.push_back(pair<int,int>(f,c));
        }

        fichero.close();
    }
}

unsigned int Problema::getFilas() const {
    return filas;
}

unsigned int Problema::getCols() const {
    return cols;
}

const list<pair<int, int>> &Problema::getWall() const {
    return wall;
}

const list<pair<int, int>> &Problema::getGold() const {
    return gold;
}

bool Problema::isWall(int f, int c) const {
    return ( find(wall.begin(),wall.end(), pair<int,int>(f,c)) != wall.end() );
}

bool Problema::isGold(int f, int c) const {
    return ( find(gold.begin(),gold.end(), pair<int,int>(f,c)) != gold.end() );
}

ostream &operator<<(ostream &os, const Problema &problema) {
    os << "Descripcion del problema: " << endl;
    for(int i=0; i<problema.getFilas(); ++i) {
        for(int j=0; j<problema.getCols(); ++j) {
            if (i==0 && j==problema.getCols()-1) {
                os << "J\t";
            } else if (i==problema.getFilas()-1 && j==0) {
                os << "S\t";
            } else if (problema.isGold(i,j)) {
                os << "O\t";
            } else if (problema.isWall(i,j)) {
                os << "M\t";
            } else {
                os << "X\t";
            }
        }
        os << endl;
    }

    return os;
}
