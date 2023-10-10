//
// Created by david on 24/05/22.
//

#include "Problema.h"

using namespace std;

Problema::Problema() {
    this->filas = 0;
    this->columnas = 0;
    this->bateria = 0;
    this->cantidadTerrenosDistintos = 0;
    this->ValorBateriaTerreno.clear();
    this->matrizAux.clear();
}

Problema::Problema(const Problema &other) {
    this->filas = other.filas;
    this->columnas = other.columnas;
    this->bateria = other.bateria;
    this->cantidadTerrenosDistintos = other.cantidadTerrenosDistintos;
    this->ValorBateriaTerreno = other.ValorBateriaTerreno;
    this->matrizAux = other.matrizAux;
}

Problema::Problema(const char *nombre): Problema() {
    std::ifstream fichero;

    fichero.open(nombre);
    fichero >> this->filas;//Aquí introducimos mediante el fichero la cantidad de filas del terreno total
    fichero >> this->columnas;//Aquí introducimos mediante el fichero la cantidad de columnas del terreno total
    fichero >> this->cantidadTerrenosDistintos;//Aquí introducimos la cantidad de terrenos distintos que vamos a tener
    fichero >> this->bateria;//Batería de la que dispone el robot

    int aux=0;
    for(int i=0;i<this->cantidadTerrenosDistintos;i++){
        fichero>>aux;
        this->ValorBateriaTerreno.push_back(aux);
    }

    for(int i=0; i<this->getFilas(); ++i)
        matrizAux.push_back(vector<int>(this->columnas,0));

    int valorAux = 0;
    for(int i=0;i<this->filas;++i){
        for(int j=0;j<this->columnas;++j){
            fichero >> valorAux;
            this->matrizAux[i][j]=valorAux;
        }
    }

    fichero.close();
}

const int Problema::getFilas() const {
    return this->filas;
}

const int Problema::getColumnas() const {
    return this->columnas;
}

const std::vector<int> Problema::getValorBateriaTerreno() const{
    return this->ValorBateriaTerreno;
}

const std::vector<std::vector<int>> Problema::getMatrizAux() const{
    return this->matrizAux;
}

const int Problema::getCosteCasilla(int posicion) const {
    return this->ValorBateriaTerreno[posicion];
}

const int Problema::getBateria() const {
    return this->bateria;
}

ostream &operator<<(ostream &os, const Problema &problema){
    os << "Detalles del problema:\nTamaño matriz ["+ std::to_string(problema.filas) +"][" + std::to_string(problema.columnas) + "] tendrmos " +
            std::to_string(problema.cantidadTerrenosDistintos) + " terrenos distintos\n";

    for(int i=0; i< problema.ValorBateriaTerreno.size(); ++i) {
        os <<  "Bateria de tipo de terreno " + std::to_string(i+1) + ": " + std::to_string(problema.ValorBateriaTerreno[i]);
        os << endl;
    }

    os<<"Nuestro robot dispone de bateria: "<<problema.bateria<<endl;

    os << "Matriz indicando de que tipo es cada casilla: \n";
    for(int i=0;i<problema.filas;++i){
        for(int j=0;j<problema.columnas;++j){
            os << problema.matrizAux[i][j];
            os << " ";
        }
        os << endl;
    }


    return os;
}
