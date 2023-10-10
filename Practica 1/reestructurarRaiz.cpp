#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void reestructurarRaiz(double *apo, int pos, int tamapo) {
	int minhijo;
	if ((2*pos+1) < tamapo) {
		minhijo=2*pos+1;
		
		if ((minhijo+1 < tamapo) && (apo[minhijo]>apo[minhijo+1]))
			minhijo++;
			
		if (apo[pos]>apo[minhijo]) {
			double tmp = apo[pos];
			apo[pos] = apo[minhijo];
			apo[minhijo] = tmp;
			reestructurarRaiz(apo, minhijo, tamapo);
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
	srand(semilla);
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		apo= new double[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			apo[i]= rand()%n;
		
		cerr << "Ejecutando reestructurarRaiz para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		reestructurarRaiz(apo, i, 0); // Ejecutamos el algoritmo para tamaño de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (ns): " << tejecucion << " para tam. caso " << endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		// Liberamos memoria del vector
		delete [] apo;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
