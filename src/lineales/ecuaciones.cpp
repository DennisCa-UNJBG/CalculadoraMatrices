#include <iostream>
#include <iomanip> // crear una tabla
#include <random> // generar numeros aleatorios
// libreria custom
#include <ecuaciones.hpp>

using std::cout;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;
using std::setprecision;


void Ecuaciones::imprimir(int espacios){
    int caracter = 97;
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            if(j == columnas-1){
                cout << "  = ";
                cout << setw(espacios-2)  << setprecision(3) << matriz[i][j] << " ";
            } else {
                cout << setw(espacios)  << setprecision(3) << matriz[i][j];
                cout << (char)(caracter+j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void Ecuaciones::rellenar(void){
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matriz[i][j] = distribution(generator);
        }
    }
}

Ecuaciones::~Ecuaciones(){
    for (int i = 0; i < filas; i++)
        delete[] matriz[i]; // liberar memoria de la segunda dimension

    delete[] matriz; // liberar memoria de la primera dimension
}

Ecuaciones::Ecuaciones(int cantIncognitas){
    this->filas = cantIncognitas;
    this->columnas = cantIncognitas + 1; // las columnas deben tener un espacio mas para la incognita
    matriz = new double*[this->filas];
    for(int i = 0; i < this->filas; i++)
        matriz[i] = new double[this->columnas];
}
