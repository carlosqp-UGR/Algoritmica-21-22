#include <iostream>
#include <chrono>
#include <math.h>	// funciones floor(redondeo hacia abajo) y ceil(redondeo hacia arriba)
#include <cstdlib> // Para usar srand y rand
#include <fstream> // Para usar ficheros
using namespace std;

int multiplicaBasico(int i, int j);
int multiplicaDyV(int i, int j);

int main(int argc, char **argv) {

    chrono::time_point<std::chrono::high_resolution_clock> t0_1, tf_1, t0_2, tf_2; // Para medir el tiempo de ejecución
	int i, j, m1, m2;	// Variables locales (externas al bucle)
	unsigned long t1, t2; // Tiempos de ejecución
		
	if(argc>3) {
		cerr<<argv[0]<<" Semilla NombreFicheroSalida\n\n";
		exit(-1);
	} else if(argc==1) {	// Ejecución sin argumentos
		while(true) {
			cout << "Introduzca un número natural (i):\t" ;
			cin >> i;
			cout << "Introduzca un número natural (j):\t" ;
			cin >> j;
			
			if(i<=0 || j<=0) {
				cout << endl << "Fin de la ejecución." << endl;
		 		exit(0);
	 		}
		 	
		 	// Ejecución algortimo Básico	
			t0_1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
			m1 = multiplicaBasico(i,j);
			tf_1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
	 		t1 = std::chrono::duration_cast<std::chrono::microseconds>(tf_1 - t0_1).count();
	 		
	 		// Ejecución algortimo DyV
			t0_2 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
			m2 = multiplicaDyV(i,j);
			tf_2 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
	 		t2 = std::chrono::duration_cast<std::chrono::microseconds>(tf_2 - t0_2).count();
	 		
		 	cout << "\t(i=" << i << ")*(j=" << j << ") = " << i*j << " (esperado)\n\tBasico =  " << m1 << " (" << t1 << " us)\n\tDyV =  " << m2 << " (" << t2 << " us)" << endl;
		}
	} else if(argc==3){	// Ejecución con argumentos (Semilla NombreFicheroSalida)
		
		const int num_iter = 28; // Máxima potencia de dos (2^15)
			
		// Inicializamos generador de no. aleatorios
		unsigned long int semilla= atoi(argv[1]);
		srand(semilla);
		
		// Abrimos fichero de salida
		ofstream fsalida;
		fsalida.open(argv[2]);
		if (!fsalida.is_open()) {
			cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
			return 0;
		}
		
		fsalida << "j Basico(us) DyV(us)" << endl;

		j=1;
		for(int c=0; c<num_iter; ++c) {
			// Asignación de i, j(potencia de 2)
			i=rand()%5+1;
			j*=2;
			
		 	// Ejecución algortimo Básico	
			t0_1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
			m1 = multiplicaBasico(i,j);
			tf_1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
	 		t1 = std::chrono::duration_cast<std::chrono::microseconds>(tf_1 - t0_1).count();
	 		
	 		// Ejecución algortimo DyV
			t0_2 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
			m2 = multiplicaDyV(i,j);
			tf_2 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
	 		t2 = std::chrono::duration_cast<std::chrono::microseconds>(tf_2 - t0_2).count();
	 		
	 		// Salvamos la información
	 		fsalida << j << " " << t1 << " " << t2 << endl;
		 	cout << "\t(i=" << i << ")*(j=" << j << ") = " << i*j << " (esperado)\n\tBasico =  " << m1 << " (" << t1 << " us)\n\tDyV =  " << m2 << " (" << t2 << " us)" << endl;
		}
		
		// Cerramos fichero de salida
		fsalida.close();
	}

	return 0;
}

int multiplicaBasico(int i, int j) {
	
	// Caso base
	if(j==1) return i;
	
	// Caso común
	int m=0;
	for(j; j>0; --j) m+=i;
	
	return m;
}

int multiplicaDyV(int i, int j) {
	
	// Caso base
	if(j==1) return i;
	else {	// Caso general
		int m1 = multiplicaDyV(i, floor((double) j/2));
		int m2 = multiplicaDyV(i, ceil((double) j/2));
		return m1+m2;
	}
}



// -------------------------------------------------------------------------------
/**
 * Representación alternativa
int multiplicaDyV(int i, int j) {
	
	// Caso base
	if(i==1) return j;
	if(j==1) return i;
	
	int m = 0;
	if(i<j) { 	// Caso común
		int m1 = multiplicaDyV(i, floor((double) j/2));
		int m2 = multiplicaDyV(i, ceil((double) j/2));
		m=m1+m2;
	} else { 	// Caso básico (fuerza bruta)
		for(j; j>0; --j) m+=i;
	}
	
	return m;
}
*/
