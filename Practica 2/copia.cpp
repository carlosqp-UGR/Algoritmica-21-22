#include <math.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


bool cuadradoPerfectoBasico(int numero) {
    bool resultado = false;

    if (numero == 1) resultado = true;
    else {
        for (int i = 0; i < numero; i++) if (i * i == numero) resultado = true;
    }

    return resultado;
}


bool cuadradoPerfecto(int numero){
    bool resultado=false;
    int aux = numero/2;

    if(numero==1) resultado = true;
    else{
        if(aux*aux>numero){
            for(int i=0;i<=numero/2;i++) if(i*i==numero) resultado = true;
        }else {
            for (int i = numero/ 2; i <= numero; i++) if (i * i == numero) resultado = true;
        }
    }
    return resultado;
}

int main(int argc, char *argv[]) {

	vector<int> vector;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0,tf, t01, tf1; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;

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
		vector.assign(n,0);

		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n-1; i++)
			vector[i]= rand()%n;

        cout<<"Introduce un  numero"<<endl;
        int m;
        cin >> m;

        t01= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
                cuadradoPerfectoBasico(m);
        tf1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo


        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf1 - t01).count();
        cerr << "\tTiempo de ejec algoritmo Basico. (ns): " << tejecucion << " para numero: "<<m<< endl;

        bool resultado = false;
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
                resultado=cuadradoPerfecto(m);
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
        if(resultado) cout<<"El número "<<m<<" es cuadrado perfecto"<<endl; //Mostramos por pantalla que es un número de cuadrado perfecto
        else cout<<"El número "<<m<<" no es cuadrado perfecto"<<endl; //Mostramos por pantalla que no es número de cuadrado perfecto

		unsigned long tejecucionDyV= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();

		cerr << "\tTiempo de ejec algoritmoDyV. (ns): " << tejecucionDyV << " para numero: "<<m<< endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<"Tamaño: "<<n<<" Basico "<<tejecucion<<"\n";
        fsalida<<"Tamaño: "<<n<<" DyV "<<tejecucionDyV<<"\n";

		// Liberamos memoria del vector
		vector.clear();
	}

	// Cerramos fichero de salida
	fsalida.close();

	return 0;
}
