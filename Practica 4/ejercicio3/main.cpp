#include <iostream>
#include "Problema.h"
#include "Solucion.h"

using namespace std;

int main() {
    const string Separador = "-----------------------------------------------------";

    Problema problema("Fichero3.dat");
    cout << Separador << endl << problema;

    Solucion solucion(problema);
    cout<< Separador <<endl;
    cout<<solucion.toString()<<endl;
    cout<< Separador <<endl;
    solucion.calculaMemoria();
    cout << Separador << endl << solucion << Separador << endl;

    return 0;
}
