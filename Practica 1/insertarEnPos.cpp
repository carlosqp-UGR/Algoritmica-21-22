#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void insertarEnPos(double *apo, int pos) {
	int idx = pos-1;
	int padre;
	if (idx > 0) {
		if (idx%2==0) {
			padre = (idx-2)/2;
		} else {
			padre = (idx-1)/2;
		}
		
		if (apo[padre] > apo[idx]) {
			double tmp = apo[idx];
			apo[idx] = apo[padre];
			apo[padre] = tmp;
			insertarEnPos(apo, padre+1);
		}
	}
}

/**
 * @brief Ejecuta el algoritmo segun el tamaño de caso especificado en los
 * argumentos y vuelca los datos de ejecucion en un fichero. Ejecuta siempre
 * el peor caso posible en términos de eficiencia para el algoritmo. ¿Cuál sería?
 */
int main(int argc, char *argv[]) {
	
	double *apo; // APO, su estructura interna pese a ser un árbol es la de un vector
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		apo= new double[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n-1; i++)
			apo[i]= i;
			
		apo[n]=0;
		
		cerr << "Ejecutando insertarEnPos para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		insertarEnPos(apo, 0); // Ejecutamos el algoritmo para tamaño de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (ns): " << tejecucion << " para tam. caso: "<<n<< endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		// Liberamos memoria del vector
		delete [] apo;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
