//
// Created by carlosqp on 24/5/22.
//

#include "solucion.h"
using namespace std;

Solucion::Solucion(): problema() {
    memoria.empty();
}

Solucion::Solucion(const Problema &p): problema(p) {
    memoria.empty();

    for(int i=0; i<problema.getFilas(); ++i)
        memoria.push_back(vector<int>(problema.getCols(),0));

    calculaMemoria();
}

// Rellena la memoria
void Solucion::calculaMemoria() {

    // Damos valor al caso base (recordar que inicialmente todas las casillas están inicializadas a 0), la
    // posicion inicial del jugador en el tablero -> Esquina superior izquierda.
    if(problema.isGold(0,problema.getCols()-1)) {
        ++memoria[0][problema.getCols()-1];
    }

    // Damos valor a la primera fila, desde la ultima columna hasta la primera. Cada casilla depende de su
    // inmediatamente posterior (la de su derecha, calculada previamente).
    for(int j=problema.getCols()-2; j>=0; --j) {
        if(memoria[0][j+1]<0 || problema.isWall(0, j)) {
            memoria[0][j] = -1;
        } else {
            memoria[0][j] = memoria[0][j+1];
            if(problema.isGold(0,j))
                ++memoria[0][j];
        }
    }

    // Damos valor a la última columna, desde la primera fila hasta la última. Cada casilla depende de su
    // inmediatamente superior.
    for(int i=1; i<problema.getFilas(); ++i) {
        if(memoria[i-1][problema.getCols()-1]<0 || problema.isWall(i,problema.getCols()-1)) {
            memoria[i][problema.getCols()-1] = -1;
        } else {
            memoria[i][problema.getCols()-1] = memoria[i-1][problema.getCols()-1];
            if(problema.isGold(i,problema.getCols()-1))
                ++memoria[i][problema.getCols()-1];
        }
    }

    // Calculamos la memoria de la matriz. Aprovechamos el enfoque tabular de la PD.
    for(int i=1; i<problema.getFilas(); ++i) {
        for (int j = problema.getCols() - 2; j >= 0; --j) {
            if(problema.isWall(i,j))
                memoria[i][j] = -1;
            else {
                // top = memoria[i-1][j]
                // diagonal = memoria[i-1][j+1]
                // right = memoria[i][j+1]
                memoria[i][j] = max( memoria[i-1][j], max(memoria[i-1][j+1],memoria[i][j+1]) );
                if(problema.isGold(i,j))
                    ++memoria[i][j];
            }
        }
    }
}

int Solucion::getMaxGold_Intermediate(int f, int c) const {
    if(f<0 || f>=problema.getFilas() || c<0 || c>=problema.getCols())
        return -1;
    else
        return memoria[f][c];
}

int Solucion::getMaxGold() const {
    return getMaxGold_Intermediate(problema.getFilas()-1, 0);
}

ostream &operator<<(ostream &os, const Solucion &solucion) {
    os << "Memoria de la solución: " << endl;
    for(int i=0; i<solucion.memoria.size(); ++i) {
        for (int j = 0; j < solucion.memoria[i].size(); ++j)
            os << solucion.memoria[i][j] << '\t';
        os << endl;
    }
    os << "Max bolsas de oro = " << solucion.getMaxGold() << endl;

    return os;
}
