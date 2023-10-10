/**
 * @file ejercicio1.cpp
 * @compile g++ ejercicio1.cpp -o ejercicio1.bin
 * @exec ./ejercicio1.exe
 * @author CarlosQP
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <set>

using namespace std;

#define SIN_CONEXION 1000000 // Valor asignado para los nodos no conectados

/**
 * @brief Estructura necesaria para plantear el problema
 **/
struct problema {
    // Matriz de adyacencia con todos los sensores (incluido el sensor objetivo: 'sink') y las velocidades de transmisión entre ellos.
    vector<vector<int>> matrizAdyacencia;
    int numeroSensores; // Número de sensores
    int sink; // Índice del sensor sink
};

/**
 * @brief Estructura para almacenar la solucion
 **/
struct solucion {
    bool valida = false;
    list<int> secuencia;
    int velocidadMinima;
};

/**
 * @brief Estructura utilizada para procesar los nodos en el algoritmo
 **/
struct nodoSensor {
    int numero;                 // Número sensor (identificador)
    int velocidadTransmision;   // Coste del camino al objetivo
    list<int> secuencia;
};

/**
 * @brief Estructura necesaria para la comparacion de velocidades
 **/
struct ComparaVelocidad {
    bool operator()(const nodoSensor &a, const nodoSensor &b) const {
		if (a.velocidadTransmision>b.velocidadTransmision)
			return true;
		else
			return false;
	}
};

/**
 * @brief Implementación del algoritmo tipo Greedy similar al de Dijsktra
 * @param p problema (mapa de sensores y velocidades)
 * @param origen sensor origen del problema
 * @return Devuelve la solucion al problema
 **/
solucion algoritmo(const problema &p, int origen) {

    set<int> Cerrados;
    priority_queue<nodoSensor,vector<nodoSensor>,ComparaVelocidad> Abiertos;

    // Nodo a procesar: inicialmente el nodo origen, posteriormente se irá extrayendo de la lista de abiertos
    nodoSensor actual;
    actual.numero = origen;
    // actual.secuencia.push_back(origen); // Inicialmente sólo se incluye a ella misma
    actual.secuencia.empty(); // Inicialmente vacía
    actual.velocidadTransmision = 0; // El coste inicial es 0
    Abiertos.push(actual); // Únicamente para la primera iteración

    // Mientras queden nodos sin explorar y no hayamos encontrado la solución
    while (!Abiertos.empty() && actual.numero!=p.sink) {

        // Saca el nodo actual de la lista de no explorados y lo inserta en la lista de visitados
        Abiertos.pop();
        Cerrados.insert(actual.numero);

        // Genera e inserta en la lista de abiertos(ordenada por el coste), a aquellos caminos conectados
        for(int i=0; i<p.numeroSensores; ++i) {
            int velocidad = p.matrizAdyacencia[actual.numero][i];
            if(velocidad!=SIN_CONEXION && i!=actual.numero) {
                nodoSensor siguiente;
                siguiente.numero = i;
                siguiente.secuencia = actual.secuencia;
                siguiente.secuencia.push_back(i);
                siguiente.velocidadTransmision = actual.velocidadTransmision + velocidad;
                Abiertos.push(siguiente);
            }
        }

        // Comprueba si el siguiente nodo a procesar ya ha sido procesado
        while((Cerrados.find(Abiertos.top().numero)!=Cerrados.end()) && !Abiertos.empty()) Abiertos.pop();

        // Selecciona el siguiente nodo
        if(!Abiertos.empty()) actual = Abiertos.top();

    }   // Fin del algoritmo: acaba si ha visitado todos los posibles nodos o si se encuentra en el nodo destino

    solucion s;

    // Si se ha encontrado la solucion
    if(actual.numero == p.sink) {
        s.valida = true;
        s.velocidadMinima = actual.velocidadTransmision;
        s.secuencia = actual.secuencia;
    }

    return s;
}


/**
 * @brief Carga y crea el problema inicializando la estructura según el fichero
 * @param nombrefich path del fichero de datos
 * @return Devuelve la estructura asociada al problema descrito en el fichero
 **/
problema cargarProblema(const char *nombrefich) {
		ifstream fich;
		char c; // Para eliminar caracteres
		int numSensores;
		int sink;

		fich.open(nombrefich);
		if (!fich) {
            cerr << "Error de apertura del fichero " << nombrefich << endl;
            exit(-1);
        }

        fich >> numSensores; // Obtiene el numero de sensores

        fich >> sink; // Obtiene el índice del sink

        // Lee la matriz de adyacencia, de conexiones entre sensores
        vector<vector<int>> matriz (numSensores);
        for(int i=0; i<numSensores; i++) {
            for(int j=0; j<numSensores; j++) {
                int n;
                fich >> n;
                if(n==-1) matriz[i].push_back(SIN_CONEXION);
                else matriz[i].push_back(n);
            }
        }

        fich.close();

        // Copia los datos en la estructura del problema
        problema p;
        p.numeroSensores = numSensores;
        p.sink = sink;
        p.matrizAdyacencia.clear();
        p.matrizAdyacencia = matriz;

        return p;
}

/**
 * @brief Imprime los detalle del problema
 **/
void imprimeProblema(const problema &p) {
    cout << "Numero de Sensores: " << p.numeroSensores << endl;
    cout << "Indice del Sensor 'SINK': " << p.sink << endl;
    cout << "Matriz de conexiones:" << endl;
    for(int i=0; i<p.numeroSensores; i++) {
        for(int j=0; j<p.numeroSensores; j++) {
            if(p.matrizAdyacencia[i][j]==SIN_CONEXION) cout << "nc\t";
            else cout << p.matrizAdyacencia[i][j] << "\t";
        }
        cout << endl;
    }
}

/**
 * @brief Imprime los detalle de la solucion del problema
 **/
void imprimeSolucion(const solucion &s) {
    if(!s.valida) cout << "Solucion No Valida" << endl;
    else {
        cout << "Velocidad de transmision (minima): " << s.velocidadMinima << endl;
        cout << "Secuencia de sensores inalámbricos ";

        for( list<int>::const_iterator it=s.secuencia.cbegin(); it!=s.secuencia.cend(); ++it )
            cout << " --> Sensor(" << *it << ")" ;
        cout << endl;
    }
}

/**
 * @brief Programa que procesa los argumentos dado un problema dado y calcula los
 * caminos de velocidad mínima en el mapa de sensores
 * @param argv[1] camino del archivo para cargar el problema
 * @param argv[2] sensor origen del problema
 **/
int main(int argc, char **argv) {
    char archivo[] = "data1.dat";

    cout << "Cargando el problema..." << endl;
    cout << "Informacion del problema: " << endl;

    problema p = cargarProblema(archivo);
    imprimeProblema(p);

    int origen = 2;
    cout << endl << "Calculando solucion para el sensor origen " << origen << "..." << endl;
    solucion s;
    s=algoritmo(p,origen);
    imprimeSolucion(s);

	return 0;
}
