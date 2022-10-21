#include <iostream>
#include <vector>
#include <array>
#include <iomanip> // crear una tabla
#include <random> // generar numeros aleatorios
// libreria custom
#include <ecuaciones.hpp>
#include <cmath> // para usar la funcion valor absoluto - abs()

using std::cout;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;
using std::setprecision;
using std::abs;
using std::vector;
using std::array;

void Ecuaciones::metodoGauss(){
    Ecuaciones* temporal = new Ecuaciones(this->filas);
    // copiar datos de la matriz original
    for(int i=0; i < this->filas; i++){
        for(int j=0; j < this->columnas; j++){
            temporal->matriz[i][j] = this->matriz[i][j];
        }
    }

    // buscamos el índice con coeficiente menor
    float menor, comparar, aux1, aux2;
    //int iter = 1;
    // pivote - intercambiamos filas en la matriz de menor a mayor
    for(int k = 0; k < filas; k++){
        menor = abs(temporal->matriz[k][0]);
        for(int i = k+1; i < filas; i++){
            comparar = abs(temporal->matriz[i][0]);
            if(menor > comparar){
                menor = comparar;
                for(int j = 0; j < columnas; j++){ // intercambiamos filas
                    aux1 = temporal->matriz[k][j];
                    aux2 = temporal->matriz[i][j];
                    temporal->matriz[k][j] = aux2;
                    temporal->matriz[i][j] = aux1;
                }
                /*cout << "\n0" << iter++ << " iteracion: " << menor << endl;
                temporal->imprimir();*/
            }
        }
    }
    cout << "\nLuego de ordenas las ecuaciones de menor a mayor obtenemos: " << endl;
    temporal->imprimir();

    int iterador = 1;
    // recorremos la diagonal para ver si existe un elemento igual a CERO
    for(int k = 0; k < filas; k++){
        if(temporal->matriz[k][k] == 0){
            cout << "La matriz no tiene solucion, un elemento de la diagonal es 0..." << endl;
            return;
        } else {
            // metodo de gauss
            for(int i = k+1; i < filas; i++){ // recorremos la fila
                double aux = temporal->matriz[i][k]; // guardamos para evitar que se pierda el valor original al reemplazar la fila
                for(int j = k; j < columnas; j++){ // recorremos las columnas de la fila
                    //cout << temporal->matriz[i][j]<<"=" << temporal->matriz[i][j]<<" - "<<aux<<"/"<<temporal->matriz[k][k]<<" * " <<temporal->matriz[k][j] <<  endl; // verificar formulas
                    temporal->matriz[i][j] = temporal->matriz[i][j] - (aux/temporal->matriz[k][k]) * temporal->matriz[k][j];
                }
                cout << "\n0" << iterador++ << " iteracion:" << endl;
                temporal->imprimir();
            }
        }
    }

    // Vertificar que los elementos operados sean igual a CERO(matriz escalonada)
    bool fallo = false;
    for(int i=1; i < temporal->filas; i++){
        for(int j=0; j < i; j++){
            if(temporal->matriz[i][j] != 0)
                fallo = true; // alguno de los elementos de la escalera inferior es diferente de CERO
        }
    }

    if(fallo){
        cout << "Imposible calcular las incognitas, el metodo de GAUSS fallo..." << endl;
        return;
    }
    system("pause");
    // imprimir resultado de las incognitas
    int filT = temporal->filas;
    int colT = temporal->columnas;
    double* incognitas = new double[filT];
    // ultima incognita
    incognitas[filT-1] = temporal->matriz[filT-1][colT-1]/temporal->matriz[filT-1][colT-2];
    double operacion = 0;
    cout << incognitas[filT-1] << endl;
    for(int i=filT-2; i >= 0; i--){
        for(int j=i+1; j < colT-1; j++){
            //cout << temporal->matriz[i][j] << "*" << incognitas[j]<< " + " << endl;
            //system("pause");
            operacion += temporal->matriz[i][j] * incognitas[j];
        }
        //cout << endl;
        incognitas[i] = (temporal->matriz[i][temporal->columnas-1]-operacion)/temporal->matriz[i][i];
        //cout << temporal->matriz[i][temporal->columnas-1] <<"-"<< operacion << "/"<<temporal->matriz[i][i] <<endl;
        //cout << incognitas[i] << endl;
        //cout << endl;
        //system("pause");
    }
    // imprimir valor de las incognitas
    int caracter = 97;
    for(int i = 0; i < filT; i++){
        cout << (char)(caracter+i) << " = " << incognitas[i] << endl;
    }
    system("pause");
    delete temporal; // liberar memoria
}

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
