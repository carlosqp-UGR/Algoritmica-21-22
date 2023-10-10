#include <iostream>
#include "problema.h"
#include "solucion.h"
using namespace std;

int main(int argc, char *argv[]) {

    const string Separador = "-----------------------------------------------------";

    Problema problema("Fichero2.dat");
    cout << Separador << endl << problema;

    Solucion solucion(problema);
    cout << Separador << endl << solucion << Separador << endl;

    return 0;
}
