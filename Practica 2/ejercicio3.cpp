#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <cstring> // Para usar memcpy
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

using namespace std;


int CalculoParcial(int min,int max,int busca){
	
	int n;
	bool encontrado = false;
	int centro = (min+max)/2;
	if(min<max-1){
		n=centro*(centro+1)*(centro+2);
		if(n<busca){
			min = centro;
			return CalculoParcial(min,max,busca);
		}else{
			max = centro;
			return CalculoParcial(min,max,busca);
		}
	}else{
		if(min == max) return min;
		n=min*(min+1)*(min+2);
		if(n == busca) return min;
		n= max*(max+1)*(max+2);
		if(n == busca) return max;
	}
	return -1;
	
}

int CalculoN(int N){

	return CalculoParcial(0,N,N);
	
}
int main(int argc, char *argv[]) {
	
	int N, y;
	cin >> N;
	
	y = CalculoN(N);
	
	if(y>=0) cout << "N: " << N << " y: " << y;
	
	
	return 0;
}
