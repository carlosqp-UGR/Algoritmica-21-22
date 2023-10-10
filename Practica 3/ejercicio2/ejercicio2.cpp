#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <fstream>


using namespace std;

struct problema{
    vector<int> v;
    int numeroGasolineras;
    int distanciaDepositoLLeno;
    int distanciaTotal;
};

struct solucion{
    vector<int> secuencia;
    int nParadas;
    bool valida;
};

struct nodoGasolinera{
    int nParadaA;
    vector<int> secuencia;
    int puntoKm;

        bool operator<(const nodoGasolinera &a) const{
            return this->nParadaA>a.nParadaA;
        }
};

solucion algoritmo(const problema &p){

    set<int> Cerrados;
    priority_queue<nodoGasolinera,vector<nodoGasolinera>> Abiertos;
    int distanciaRecorrida;
    nodoGasolinera siguiente;

    nodoGasolinera actual;
    actual.nParadaA = 0;
    actual.secuencia.empty();
    actual.puntoKm = 0;
    //distanciaRecorrida = actual.puntoKm;
    Abiertos.push(actual);

    while (!Abiertos.empty() && distanciaRecorrida!=p.distanciaTotal) {

        //Sacamos el nodo ultimo explorados, de lista de no explorados y lo metemos en lista de explorados
        Abiertos.pop();
        Cerrados.insert(actual.puntoKm);
        for(int i=0;i<p.numeroGasolineras;i++){
            if(p.v[i]-actual.puntoKm<=p.distanciaDepositoLLeno && !(p.v[i+1]-actual.puntoKm<=p.distanciaDepositoLLeno) && !(actual.puntoKm+p.distanciaDepositoLLeno>=p.distanciaTotal)){
                distanciaRecorrida += p.v[i] - actual.puntoKm;
                nodoGasolinera siguiente;
                siguiente.puntoKm = p.v[i];
                siguiente.nParadaA = actual.nParadaA + 1;
                siguiente.secuencia = actual.secuencia;
                siguiente.secuencia.push_back(i);
                Abiertos.push(siguiente);
            }
        }


        // Comprueba si el siguiente nodo a procesar ya ha sido procesado
        while((Cerrados.find(Abiertos.top().nParadaA)!=Cerrados.end()) && !Abiertos.empty()) Abiertos.pop();

        // Selecciona el siguiente nodo
        if(!Abiertos.empty()) actual = Abiertos.top();

    }

        solucion s;

        //Si la gosolinera actual
        if(p.distanciaTotal-distanciaRecorrida<=p.distanciaDepositoLLeno){
            s.nParadas = actual.nParadaA;
            s.secuencia = actual.secuencia;
            s.valida = true;
        }

        return s;
}

problema cargarProblema(const char *nombrefich) {
    ifstream fich;
    char c; // Para eliminar caracteres
    int numGasolineras;
    int distanciaTotal;
    int cantidadLLeno;
    int puntoKm;

    fich.open(nombrefich);
    if (!fich) {
        cerr << "Error de apertura del fichero " << nombrefich << endl;
        fich.close();
        exit(-1);
    }

    fich >> numGasolineras; // Obtiene el numero de gasolineras disponibles

    fich >> distanciaTotal; // Obtiene la distancia total que tiene que realizar el algoritmo

    fich >> cantidadLLeno;

    vector<int> vectorG(numGasolineras);
    for(int i=0; i<numGasolineras; i++) {
        fich >> puntoKm;
        vectorG[i]=puntoKm;
    }

    fich.close();

    // Copia los datos en la estructura del problema
    problema p;
    p.numeroGasolineras = numGasolineras;
    p.distanciaTotal = distanciaTotal;
    p.distanciaDepositoLLeno = cantidadLLeno;
    p.v=vectorG;

    return p;
}

void imprimeProblema(const problema &p) {
    cout << "Numero de Gasolineras: " << p.numeroGasolineras << endl;
    cout << "Distancia a recorrer por el autobús: " << p.distanciaTotal << endl;
    cout << "Gasolineras en las que se ha repostado:" << endl;
    for(int i=0; i<p.numeroGasolineras; i++) {
            cout<<"Gasolinera numero "<<i+1<<" en km: "<<p.v[i];
            cout << endl;
        }
}

void imprimeSolucion(const solucion &s) {
    if(!s.valida) cout << "Solucion No Valida" << endl;
    else {
        cout << "Numero de paradas minimas: " << s.nParadas << endl;
        cout << "Secuencia de gasolineras en las que se reposto ";

        for( vector<int>::const_iterator it=s.secuencia.cbegin(); it!=s.secuencia.cend(); ++it )
            cout << " --> Gasolineras en el kilometro(" << *it << ")" ;
        cout << endl;
    }
}

int main(int argc, char **argv) {
    char archivo[] = "data1.dat";

    cout<<"Solución con paradas minimas en el recorrido"<<endl;
    cout << "Cargando el problema..." << endl;
    cout << "Informacion del problema: " << endl;

    problema p = cargarProblema(archivo);
    imprimeProblema(p);

    int origen = 0;
    cout << endl << "Calculando solucion "<<endl;
    solucion s;
    s=algoritmo(p);
    imprimeSolucion(s);

    return 0;
}