//
// Created by carlosqp on 20/5/22.
//

#ifndef PROYECTOS_PROBLEMA_H
#define PROYECTOS_PROBLEMA_H

#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Problema {
private:
    int n;  // Numero de idiomas
    int m;  // Numero de diccionarios
    vector<string> idiomas;
    vector<pair<string,string>> diccionarios;

public:

    Problema();

    Problema(const Problema &other);

    Problema(const char *nombre);

    const int getN() const;

    const int getM() const;

    string getIdioma(int index) const;

    int getIndexIdioma(const string &idioma) const;

    bool existeDiccionario(const string &idioma1, const string &idioma2) const;

    string toString() const;

};

#endif //PROYECTOS_PROBLEMA_H
