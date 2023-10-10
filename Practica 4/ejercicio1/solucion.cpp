//
// Created by carlosqp on 20/5/22.
//

#include <search.h>
#include "solucion.h"
using namespace std;

#define INF 10000000
#define MIN 0

string Instancia::toString() {
    string res = "Detalles de la solución -> Traducción de '" + this->orig + "' a '" + this->dest + "':\n";

    if(numero_traducciones==0) {
        res += "Numero de MINIMO de traducciones: 0. Es el mismo idioma, ¡no necesita traducción!\n";
    } else if(this->traducciones.empty() && this->numero_traducciones>0) {
        res += "No es posible realizar la traducción. No se dispone de suficientes diccionarios.\n";
    } else {
        res += "Numero de MINIMO de traducciones: ";
        res += to_string(this->numero_traducciones);
        res += "\nSecuencia de traducciones: ";

        list<string>::const_iterator it;
        for(it=this->traducciones.cbegin(); it!=this->traducciones.cend(); ++it) {
            res += *it;
            res += "-";
        }
        res.pop_back();
        res += "\n";
    }
    return res;
}

Solucion::Solucion(const Problema &p): problema(p) {

    memoria.clear();

    string idiom_i, idiom_j;
    list<string> l;
    l.clear();

    pair<int,list<string>> def (INF,l);
    vector<pair<int,list<string>>> aux (problema.getN(), def);

    for(size_t i=0; i<problema.getN(); ++i) {
        idiom_i = problema.getIdioma(i);
        memoria.push_back(aux);
        for (size_t j = 0; j < problema.getN(); ++j) {
            idiom_j = problema.getIdioma(j);
            if(i==j) {  // Es el mismo idioma
                memoria[i][j].first = MIN;
            } else if(problema.existeDiccionario(idiom_i,idiom_j)) {
                l.push_back(idiom_i);
                l.push_back(idiom_j);
                memoria[i][j].first = 1;
                memoria[i][j].second = l;
                l.clear();
            }
        }
    }

    calculaMemoria();
}


// Algoritmo de Floyd
void Solucion::calculaMemoria() {
    for(size_t k=0; k < problema.getN(); ++k) {
        for(size_t i=0; i < problema.getN(); ++i) {
            for(size_t j=0; j < problema.getN(); ++j) {
                // if( (D[i][k]+D[k][j]) < D[i][j] )
                if ((memoria[i][k].first+memoria[k][j].first) < memoria[i][j].first) {
                    memoria[i][j].first = memoria[i][k].first+memoria[k][j].first;
                    memoria[i][j].second.clear();   // Vacía las traducciones, y las recalcula
                    list<string> l = fusiona(memoria[i][k].second, memoria[k][j].second);
                    memoria[i][j].second = l;
                }
            }
        }
    }

}

Instancia Solucion::recuperaSolucion(const string &idioma1, const string &idioma2) {
    Instancia sol;
    sol.orig = idioma1;
    sol.dest = idioma2;

    int idx1 = problema.getIndexIdioma(idioma1);
    int idx2 = problema.getIndexIdioma(idioma2);
    if (idx1>=0 && idx2>=0) {
        sol.numero_traducciones = memoria[idx1][idx2].first;
        sol.traducciones = memoria[idx1][idx2].second;
    }
    return sol;
}


list<string> fusiona(const list<string> &l1, const list<string> &l2) {
    list<string> l3;

    list<string>::const_iterator it1 = l1.cbegin() ;
    for(it1; it1!=l1.cend(); ++it1) {
        l3.push_back(*it1);
    }

    list<string>::const_iterator it2 = l2.cbegin();
    ++it2;  // El primer idioma es el idioma en común, que es el último de la cadena l1 (ya ha sido insertado)
    for(it2; it2!=l2.cend(); ++it2) {
        l3.push_back(*it2);
    }

    return l3;
}
