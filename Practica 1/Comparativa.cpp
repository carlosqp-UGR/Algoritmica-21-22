#include <cstdlib> // Para usar srand y rand
#include <cstring> // memcpy
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

// Compilar: g++ -oComparativa.bin Comparativa.cpp -std=c++11

// Burbuja
void OrdenaBurbuja(int *v, int n);

// MergeSort
void fusionaMS(int *v, int posIni, int centro, int posFin, int *vaux);
void MergeSort(int *v, int posIni, int posFin, int *vaux);

// HeapSort
void insertarEnPos(double *apo, int pos);
void reestructurarRaiz(double *apo, int pos, int tamapo);
void HeapSort(int *v, int n);

int main(int argc, char *argv[]) {
	
	int *v1, *v2, *v3;
	int n, i, argumento;
	
    int *vaux; // necesario para el algoritmo MergeSort
	
    chrono::time_point<std::chrono::high_resolution_clock> t1_ini, t1_fin, t2_ini, t2_fin, t3_ini, t3_fin; // Para medir el tiempo de ejecución

	unsigned long t1_ejecucion, t2_ejecucion, t3_ejecucion; // tiempo de ejecucion del algoritmo en ns
	
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
	
	// Formato de salida
	fsalida << "n\tB\tMS\tHS\n";
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para los vectores
		v1 = new int[n];
		v2 = new int[n];
		v3 = new int[n];
		vaux= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		// Igualdad de condiciones, todos los algortimos de ordenación trabajan 
		// el mismo vector de datos.
		for (i= 0; i<n; i++) {
			int num = rand()%n;
			v1[i] = num;
			v2[i] = num;
			v3[i] = num;
		}
		
		// Ejecución de Burbuja
		t1_ini = std::chrono::high_resolution_clock::now();
		OrdenaBurbuja(v1, n);
		t1_fin = std::chrono::high_resolution_clock::now();
		t1_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(t1_fin-t1_ini).count();
		
		// Ejecución de MergeSort
		t2_ini = std::chrono::high_resolution_clock::now();
		MergeSort(v2, 0, n-1, vaux);
		t2_fin = std::chrono::high_resolution_clock::now();
		t2_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(t2_fin-t2_ini).count();
		
		// Ejecución de HeapSort
		t3_ini = std::chrono::high_resolution_clock::now();
		HeapSort(v3, n);
		t3_fin = std::chrono::high_resolution_clock::now();
		t3_ejecucion = std::chrono::duration_cast<std::chrono::nanoseconds>(t3_fin-t3_ini).count();
		
		// Vuelca los datos en el fichero
		fsalida << n << "\t" << t1_ejecucion << "\t" << t2_ejecucion << "\t" << t3_ejecucion << "\n";
		
		// Liberamos memoria del vector
		delete [] v1;
		delete [] v2;
		delete [] v3;
		delete [] vaux;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}


void OrdenaBurbuja(int *v, int n) {
	
	int i, j, aux;
	bool haycambios= true;
	
	i= 0;
	while (haycambios) {
		
	 haycambios=false; // Suponemos vector ya ordenado
	 for (j= n-1; j>i; j--) { // Recorremos vector de final a i
		 
		 if (v[j-1]>v[j]) { // Dos elementos consecutivos mal ordenados
		  aux= v[j]; // Los intercambiamos
		  v[j]= v[j-1];
		  v[j-1]= aux;
		  haycambios= true; // Al intercambiar, hay cambio
		 }
	 }
	 i++;
	}
}

void fusionaMS(int *v, int posIni, int centro, int posFin, int *vaux) {

    int i= posIni;
    int j= centro;
    int k= 0;

    while (i<centro && j<=posFin) {
        if (v[i]<=v[j]) {
            vaux[k]= v[i];
            i++;
        } else {
            vaux[k]= v[j];
            j++;
        }
        k++;
    }

    while (i<centro) {
        vaux[k]= v[i];
        i++, k++;
    }
    while (j<=posFin) {
        vaux[k]= v[j];
        j++, k++;
    }

    memcpy(v+posIni, vaux, k*sizeof(int));
}

void MergeSort(int *v, int posIni, int posFin, int *vaux) {

    if (posIni>=posFin) return;

    int centro= (posIni+posFin)/2;

    MergeSort(v, posIni, centro, vaux);
    MergeSort(v, centro+1, posFin, vaux);
    fusionaMS(v, posIni, centro+1, posFin, vaux);
}

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

void HeapSort(int *v, int n) {
	double *apo=new double[n];
	int tamapo=0;
	
	for (int i=0; i<n; i++) {
		apo[tamapo] = v[i];
		tamapo++;
		insertarEnPos(apo, tamapo);
	}
	
	for(int i=0; i<n; i++) {
		v[i] = apo[0];
		tamapo--;
		apo[0] = apo[tamapo];
		reestructurarRaiz(apo, 0, tamapo);
	}
	delete [] apo;
}
