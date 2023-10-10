// Compilar: g++ -o ejercicio3.exe ejercicio3.cpp
// Ejecutar: ./ejercicio3.exe
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <fstream>

using namespace std;

struct compara {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
		if (a.second < b.second) return true;
		else return false;
	}
};

struct problema{
    priority_queue<pair<int,int>, vector<pair<int,int>>, compara> contenedores;
    unsigned int capacidadBuque;
};

struct solucion{
    bool valida = false;
    list<pair<int,int>> secuenciaContenedores;
    unsigned int cargaTotal=0;
};


solucion algoritmo(const problema &p) {

    priority_queue<pair<int,int>, vector<pair<int,int>>, compara> cont = p.contenedores;
    list<pair<int, int>> secuenciaSolucion;
    int capacidadRestante = p.capacidadBuque;
    do {
        while(cont.top().second > capacidadRestante) cont.pop();
        secuenciaSolucion.push_back(cont.top());
        capacidadRestante -= cont.top().second;
        cont.pop(); // Borro el contenedor ya cargado
    } while(!cont.empty() && capacidadRestante>0);

    solucion s;
    s.valida = true;
    s.cargaTotal = p.capacidadBuque - capacidadRestante;
    s.secuenciaContenedores = secuenciaSolucion;
    return s;
}

problema cargarProblema(const char *nombrefich) {
    ifstream fich;
    priority_queue<pair<int,int>, vector<pair<int,int>>, compara> aux;

    fich.open(nombrefich);
    if (!fich) {
        cerr << "Error de apertura del fichero " << nombrefich << endl;
        fich.close();
        exit(-1);
    }

    int cap;
    fich >> cap;

    int num_contenedores, n;
    fich >> num_contenedores;
    for(int i=1; i<= num_contenedores; i++) {
        fich >> n;
        aux.push(pair<int,int> (i,n));
    }

    fich.close();

    // Copia los datos en la estructura del problema
    problema p;
    p.capacidadBuque = cap;
    p.contenedores = aux;

    return p;
}

void imprimeProblema(const problema &p) {
    cout << "Capacidad (en toneladas) del buque: " << p.capacidadBuque << endl;
    priority_queue<pair<int,int>, vector<pair<int,int>>, compara> aux = p.contenedores;

    while(!aux.empty()) {
        cout << "Contenedor " << aux.top().first << ": " << aux.top().second << " toneladas." << endl;
        aux.pop();
    }
}

void imprimeSolucion(const solucion &s) {

    if(!s.valida) cout << "Solucion No Valida" << endl;
    else {
        cout << "Peso total de la solucion: " << s.cargaTotal << endl;
        cout << "Lista de contenedores a cargar {C(Contenedor):Peso}: " ;
        list<pair<int,int>>::const_iterator it = s.secuenciaContenedores.cbegin();
        for(it; it!=s.secuenciaContenedores.cend(); ++it)
            cout << "{C(" << (*it).first << "):" << (*it).second << "},  ";
        cout << endl;
    }
}

int main(int argc, char **argv) {
    char archivo[] = "data3.dat";

    cout<<"Ejercicio 3. Problema de carga máxima de peso en un buque."<<endl;
    cout << "Cargando el problema..." << endl;
    cout << "Informacion del problema: " << endl;

    problema p = cargarProblema(archivo);
    imprimeProblema(p);

    cout << endl << "Calculando solucion... "<<endl;
    solucion s;
    s=algoritmo(p);
    imprimeSolucion(s);

    return 0;
}
