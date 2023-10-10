#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <algorithm> // Para usar std::max() y std::min()
using namespace std;

/**
 * @brief estructura asociada a vector que almacena una pareja de su maximo y su minimo
 */
template <typename T>
struct componentes {
	T max, min;
};

/**
 * @brief Funcion que implementa un algortimo recursivo que devuelve el mínimo y máximo valor asociado a una estructura lineal (vector)
 * @param a vector de componentes
 * @param Cini posicion inicial
 * @param Cfin posicion final
 * @ret Devuelve una estructura con el maximo y el minimo conponente entre a[Cini] y a[Cfin]
 * @pre Cini>=0 
 * @pre Cini<Cfin<N
 */
template <typename T>
componentes<T> MaximoMinimoDyV(T *a, int Cini, int Cfin) {
	// assert(Cfin<N);
	componentes<T> salida;
	
	if(Cini<(Cfin-1)) {
		int mitad = (Cini+Cfin)/2;
		componentes<T> salida1 = MaximoMinimoDyV(a, Cini, mitad);
		componentes<T> salida2 = MaximoMinimoDyV(a, mitad+1, Cfin);
		salida.max = max(salida1.max, salida2.max);
		salida.min = min(salida1.min, salida2.min);
	} else if (Cini==Cfin) { // n=1
		salida.max = a[Cini];
		salida.min = a[Cini];
	} else { // Cini == (Cfin-1), n=2
		salida.max = max(a[Cini], a[Cfin]);	// O(1)
		salida.min = min(a[Cini], a[Cfin]); // O(1)
	}

	return salida;
}

/**
 * @brief Ejecuta el algoritmo segun el tamaño de caso especificado en los argumentos y vuelca los datos de ejecucion en un fichero.
 */
int main(int argc, char *argv[]) {
	
	int *v;
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
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		// Creamos la estructura que almacenará el maximo y el mínimo de la función
		componentes<int> salida;
		
		cerr << "Ejecutando MaximoMinimoDyV para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		salida = MaximoMinimoDyV(v, 0, (n-1)); // Ejecutamos el algoritmo para tamaño de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (ns): " << tejecucion << " para tam. caso "<< n<< "\t[min(" << salida.min << "), max(" << salida.max << ")]" << endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
