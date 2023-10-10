//
// Created by carlosqp on 20/5/22.
//

#include "problema.h"
using namespace std;

Problema::Problema() {
    n = 0;
    m = 0;
    idiomas.clear();        // Evita 'core'
    diccionarios.clear();   // Evita 'core
}

Problema::Problema(const Problema &other): Problema() {
    n = other.n;
    m = other.m;
    idiomas = other.idiomas;
    diccionarios = other.diccionarios;
}

// Implementar
Problema::Problema(const char *nombre): Problema() {
    ifstream fichero;

    fichero.open(nombre);
    if (fichero) {

        // Lee los idiomas
        fichero >> n;
        string aux;
        for (int i = 0; i < n; ++i) {
            fichero >> aux;
            idiomas.push_back(aux);
            aux.clear();
        }

        // Lee los diccionarios
        fichero >> m;
        string aux1, aux2;
        for (int i = 0; i < m; ++i) {
            fichero >> aux1;
            fichero >> aux2;
            diccionarios.push_back(pair<string, string>(aux1, aux2));
        }

        fichero.close();
    }

    idiomas.shrink_to_fit();
    diccionarios.shrink_to_fit();
}

const int Problema::getN() const {
    return n;
}

const int Problema::getM() const {
    return m;
}

bool Problema::existeDiccionario(const string &idioma1, const string &idioma2) const {
    bool existe = false;
    for(size_t i=0; i<diccionarios.size() && !existe; ++i) {
        if( (diccionarios[i].first==idioma1 && diccionarios[i].second==idioma2) ||
            (diccionarios[i].first==idioma2 && diccionarios[i].second==idioma1) )
            existe = true;
    }
    return existe;
}

string Problema::getIdioma(int index) const {
    return idiomas[index];
}

int Problema::getIndexIdioma(const string &idioma) const {
    for(int i=0; i<idiomas.size(); ++i) {
        if(idioma==idiomas[i])
            return i;
    }
    return -1;
}


string Problema::toString() const {
    string res = "Detalles del problema:\nIdiomas disponibles (" + to_string(n) + "):\n";
    for(size_t i=0; i<n; ++i) {
        res += idiomas[i];
        res += "\n";
    }

    res += "Diccionarios disponibles (";
    res += to_string(m);
    res += "):\n";
    for(size_t i=0; i<m; ++i) {
        res += diccionarios[i].first;
        res += "-";
        res += diccionarios[i].second;
        res += "\n";
    }

    return res;
}
