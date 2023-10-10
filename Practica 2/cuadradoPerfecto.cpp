#include <math.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
void cuadradoPerfectoBasico(int numero){
    int raiz = numero/2; //Dividimos entre dos, como ya que no existe ningún numero que su raiz sea mayor que su mitad, de esta forma nos quitamos la mitad de los números
    int anterior = 0; //Valor temporal que almacenara un posible resultado

    while(raiz!=anterior){ //Si raiz es igual, a temporal que era un posible resultada, raiz será la raiz del número dado
        anterior = raiz; //Posible resultado
        raiz=(numero/anterior + anterior)/2; //Calculamos nueva raíz
    }
    if(raiz*raiz==numero) cout<<"El número "<<numero<<" es cuadrado perfecto"<<endl; //Mostramos por pantalla que es un número de cuadrado perfecto
    else cout<<"El número "<<numero<<" no es cuadrado perfecto"<<endl; //Mostramos por pantalla que no es número de cuadrado perfecto
}
 */



void cuadradoPerfectoBasico(int numero){
    int raiz = 0;
    bool encontrado = false;

    if(numero==1){
        raiz=1;
    }else {
        while (raiz != 0 && !encontrado) { /*Si raiz es igual, a temporal que era un posible resultada, raiz será la raiz del número dado*/
            if (raiz * raiz == numero) encontrado = true;
            else raiz--;
        }
    }
    if(raiz*raiz==numero) cout<<"El número "<<numero<<" es cuadrado perfecto"<<endl; //Mostramos por pantalla que es un número de cuadrado perfecto
    else cout<<"El número "<<numero<<" no es cuadrado perfecto"<<endl; //Mostramos por pantalla que no es número de cuadrado perfecto
}

int calculo(int numero, int posIni,int posFin){
    int resultado = 0;
    for(int i=0;i<posFin;i++) if(i*i==numero) resultado = i;

    return resultado;
}

void cuadradoPerfecto(int numero){
    bool s1=false,s2=false,base = false;
    bool encontrado = false;

    if(numero==1){
        base= true;
    }else{
        bool s1=calculo(numero,0,numero/2);
        bool s2=calculo(numero,numero/2,numero);
    }

    if(s1 || s2 || base) cout<<"El número "<<numero<<" es cuadrado perfecto"<<endl; //Mostramos por pantalla que es un número de cuadrado perfecto
    else cout<<"El número "<<numero<<" no es cuadrado perfecto"<<endl; //Mostramos por pantalla que no es número de cuadrado perfecto
}

int main(int argc, char *argv[]) {

	vector<int> vector;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0,tf, t01, tf1; // Para medir el tiempo de ejecución
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
		vector.assign(n,0);

		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n-1; i++)
			vector[i]= rand()%n;

        t01= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
        cuadradoPerfectoBasico(4);
        tf1= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

        unsigned long tejecucion= std::chrono::duration_cast<std::chrono::nanoseconds>(tf1 - t01).count();
        cerr << "\tTiempo de ejec algoritmo Basico. (ns): " << tejecucion << " para tam. caso: "<<n<< endl;

		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		    cuadradoPerfecto(4);
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo

		unsigned long tejecucionDyV= std::chrono::duration_cast<std::chrono::nanoseconds>(tf - t0).count();

		cerr << "\tTiempo de ejec algoritmoDyV. (ns): " << tejecucionDyV << " para tam. caso: "<<n<< endl;

		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";

		// Liberamos memoria del vector
		vector.clear();
	}

	// Cerramos fichero de salida
	fsalida.close();

	return 0;
}

