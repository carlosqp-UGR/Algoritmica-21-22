//
// Created by david on 24/05/22.
//

#include "Solucion.h"
#include <iostream>
using namespace std;
Solucion::Solucion(): problema() {
    memoria.empty();
    this->bateriaGastada = 0;
}

Solucion::Solucion(const Problema &p): problema(p) {
    memoria.empty();
    this->bateriaGastada = 0;
    this->memoria=p.getMatrizAux();
    rellenarCosteCasilla();
}

const int Solucion::getBateriaGastada() const {
    return this->bateriaGastada;
}

void Solucion::rellenarCosteCasilla() {
    //Aquí rellenamos el coste de cada casilla en función de su tipo
    for(int i=problema.getFilas()-1;i>=0;--i){
        for(int j=0;j<problema.getColumnas();++j) {
            if (this->memoria[i][j] == 0) {
                this->memoria[i][j] = problema.getCosteCasilla(0);
            } else if (this->memoria[i][j] == 1) {
                this->memoria[i][j] = problema.getCosteCasilla(1);
            } else if(this->memoria[i][j] == 2){
                this->memoria[i][j] = problema.getCosteCasilla(2);
            }else if(this->memoria[i][j] == -1){
                this->memoria[i][j] = 0;
            }else{
                this->memoria[i][j] = 0;
            }
        }
    }
}

//Calcula la memoría de manera que guarda en cada posición de esta el coste del camino mas barata para llegar a dicha casilla
void Solucion::calculaMemoria() {
    bool iguales = false;

    for(int i=0;i<problema.getValorBateriaTerreno().size();++i){
        if(problema.getValorBateriaTerreno()[i]==problema.getValorBateriaTerreno()[i+1]){
            iguales = true;
        }
    }
    //Caso Base
    if(iguales){
        this->bateriaGastada=problema.getValorBateriaTerreno()[0]*(problema.getFilas()-2);//Guardamos el de el caso base
    }else{//Caso General

        //Rellenamos la primera fila
        for(int i=problema.getFilas()-2;i>=0;--i) {
            this->memoria[i][0] += this->bateriaGastada;
            this->bateriaGastada = this->memoria[i][0];
        }

        //Rellenamos la primera columna
        this->bateriaGastada=0;
        for(int j=1;j<problema.getColumnas();++j) {
            this->memoria[problema.getFilas()-1][j] += this->bateriaGastada;
            this->bateriaGastada = this->memoria[problema.getFilas()-1][j];
        }

        //Calculamos el coste mínimo para llegar a cada casilla, consiguiendo así que se cumple POB ya que si cada casilla tiene
        //su coste minimo para llegar lograremos que la casilla destino tenga el coste minimo para llegar a esta
        for(int i=problema.getFilas()-2;i>=0;--i){
            for(int j=1;j<problema.getColumnas();++j){
                memoria[i][j] += min(memoria[i][j-1], min(memoria[i+1][j-1], memoria[i+1][j]));
            }
        }
        //Almacenamos el final el coste necesario para llegar a la casilla objetivo
        bateriaGastada = memoria[0][this->problema.getColumnas()-1];
    }
}

std::string Solucion::toString(){
    string coste = "Coste de Cada Casilla en función del tipo\n";
    for(int i=0; i<problema.getFilas();++i) {
        for(int j=0;j<problema.getColumnas();++j){
            coste += to_string(memoria[i][j]);
            coste += " ";
        }
        coste+="\n";
    }
    return coste;
}

ostream &operator<<(ostream &os, const Solucion &solucion) {
    os << "Solución al problema cual coste de bateria es ";
    os << solucion.getBateriaGastada()<<endl;
    if(solucion.bateriaGastada>solucion.problema.getBateria()){
        os<<"No tenemos Bateria Suficiente para llegar a ese punto, ya que disponemos de bateria: "<<solucion.problema.getBateria() << " y la batería mínima para llegar es "<< solucion.bateriaGastada<<endl;
    }else {
        os << ".\nEl camino será: \n";

        for (int i = 0; i < solucion.problema.getFilas(); ++i) {
            for (int j = 0; j < solucion.problema.getColumnas(); ++j) {
                os << solucion.memoria[i][j];
                os << " ";
            }
            os << endl;
        }
        os << "\nEl 0 indica el origen y la esquina superior derecha el destino, cuyo valor será la batería mínima para llegar a esta casilla\n";
    }
    return os;
}