//
// Created by carlosqp on 20/5/22.
//

#include <iostream>
#include "problema.h"
#include "solucion.h"
using namespace std;

int main() {
    const string Separador = "-----------------------------------------------------";

    Problema p("Fichero1.dat");
    cout << Separador << endl << p.toString();

    Solucion s(p);
    Instancia sol0 = s.recuperaSolucion("latin", "arameo");
    cout << Separador << endl << sol0.toString() << Separador << endl;

    Instancia sol1 = s.recuperaSolucion("griego", "latin");
    cout << sol1.toString() << Separador << endl;

    return 0;
}
