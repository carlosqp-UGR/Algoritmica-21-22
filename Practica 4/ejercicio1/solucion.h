//
// Created by carlosqp on 20/5/22.
//

#ifndef PROYECTOS_SOLUCION_H
#define PROYECTOS_SOLUCION_H

#include "list"
#include "problema.h"
using namespace std;

struct Instancia {
    string orig = "sin idioma";
    string dest = "sin idioma";
    int numero_traducciones = -1;
    list<string> traducciones;

    string toString();
};

class Solucion {
private:
    vector<vector<pair<int,list<string>>>> memoria;
    const Problema problema;

public:

    // Carga el problema e inicializa las estructuras debidamente
    Solucion(const Problema &p);

    // Calcula la memoria con el algoritmo de Floyd
    void calculaMemoria();

    Instancia recuperaSolucion(const string &idioma1, const string &idioma2);

};

    list<string> fusiona(const list<string> &l1, const list<string> &l2);
    // string imprime(list<string> &l);

#endif //PROYECTOS_SOLUCION_H
