#include <iostream>
#include <cmath>
#include <random> // generar numeros aleatorios
#include <iomanip> // crear una tabla
// incluir librerias custom
#include <matriz.hpp>

using std::cout;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;

/* varibles globales de configuracion */
const int MIN = -10; // minimo valor aleatorio
const int MAX = 10; // maximo valor aleatorio

/* implementación de los metodos de la clase  Matriz */
Matriz* operator+(Matriz& matriz01, Matriz& matriz02){
    Matriz* resultado = new Matriz(matriz01.filas, matriz01.columnas);
    for (int i = 0; i < matriz01.filas; i++){
        for (int j = 0; j < matriz01.columnas; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] + matriz02.M[i][j];
        }
    }
    return resultado;
}

Matriz* operator-(Matriz& matriz01, Matriz& matriz02){
    Matriz* resultado = new Matriz(matriz01.filas, matriz01.columnas);
    for (int i = 0; i < matriz01.filas; i++){
        for (int j = 0; j < matriz01.columnas; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] - matriz02.M[i][j];
        }
    }
    return resultado;
}

Matriz* operator*(Matriz& matriz01, Matriz& matriz02){
    Matriz* resultado;
    if(matriz01.getIsCuadrado() && matriz02.getIsCuadrado()){ // la matriz es cuadrada ?
        //fuente: https://www.lawebdelprogramador.com/foros/Dev-C/1371193-MULTIPLICACION-DE-MATRICES.html
        resultado = new Matriz(matriz01.orden);
        // multiplicar matrices usando otra para almacenar datos
        for(int i = 0; i < matriz01.orden; i++){
            for(int j = 0; j < matriz01.orden; j++){
                resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
                for(int z = 0; z < matriz01.orden; z++){
                    resultado->M[i][j] += matriz01.M[i][z] * matriz02.M[z][j];
                }
            }
        }
    } else { // fuente: https://www.youtube.com/watch?v=Tjrm3HsqBXE
        // toma la cantidad de filas de la primera matriz
        // toma la cantidad de columnas de la segunda matriz
        resultado = new Matriz(matriz01.filas, matriz02.columnas);
        for(int i = 0; i < matriz01.filas; i++){
            for(int j = 0; j < matriz02.columnas; j++){
                resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
                for(int z = 0; z < matriz01.columnas; z++){
                    resultado->M[i][j] += matriz01.M[i][z] * matriz02.M[z][j];
                }
            }
        }
    }

    return resultado;
}

Matriz* operator*(Matriz& matriz01, double numero){
    Matriz* resultado = new Matriz(matriz01.filas, matriz01.columnas);
    for (int i = 0; i < matriz01.filas; i++){
        for (int j = 0; j < matriz01.columnas; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] * numero;
            // aplicamos 'trunc' para limitar los decimales
            resultado->M[i][j] = trunc((resultado->M[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
}

Matriz* Matriz::traspuesta(){
    Matriz* resultado = new Matriz(this->orden);
    for (int i = 0; i < this->orden; i++){
        for (int j = 0; j < this->orden; j++){
            resultado->M[i][j] = this->M[j][i];
        }
    }
    return resultado;
}

Matriz* Matriz::calcularInversa(double& deter){
    Matriz* resultado = new Matriz(this->orden);
    // encontramos la matriz de cofactores
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = cofactor(this->M, orden, i, j);
        }
    }
    // hacemos la traspuesta de la matriz
    Matriz* aux = resultado;
    resultado = aux->traspuesta();
    delete aux;
    // aplicamos la multiplicacion por la determinante
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->M[i][j] = resultado->M[i][j] / deter;
            // aplicamos 'trunc' para limitar los decimales
            resultado->M[i][j] = trunc((resultado->M[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
}

double Matriz::cofactor(double** matriz, int orden, int fila, int columna){
    int n = orden - 1;
    double** submatriz = new double*[n];

    for (int i = 0; i < n; i++)
        submatriz[i] = new double[n];

    int x = 0;
    int y = 0;

    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            if (i != fila && j != columna){
                submatriz[x][y] = matriz[i][j];
                y++;
                if (y >= n){
                    x++;
                    y = 0;
                }
            }
        }
    }
    int det = determinante(submatriz, n);
    delete []submatriz; // liberar memoria
    return pow(-1.0, fila + columna) * det;
}

double Matriz::determinante(double** matriz, int orden){
    int det = 0;
    if (orden == 1)
        det = matriz[0][0];
    else{
        for (int j = 0; j < orden; j++)
            det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
    }
    return det;
}

double Matriz::calcularDeterminante(){
	/* fuentes:
    https://www.youtube.com/watch?v=VMe384nPYi4
    https://algoritmosyalgomas.com/determinante-de-una-matriz-de-cualquier-orden-c/#Codigo-fuente-en-C
    */
    double deter = (this->getIsCuadrado()) ? determinante(M, orden) : 0 ;
	return deter;
}

void Matriz::rellenarMatriz(){
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            M[i][j] = distribution(generator);
        }
    }
}

void Matriz::imprimirMatriz(int espacios){
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            cout << setw(espacios) << M[i][j] << " ";
            }
        cout << "|" << endl;
    }
    cout << endl;
}

Matriz::Matriz(int orden){
    this->isCuadrado = true;
    this->orden = orden;
    this->filas = orden;
    this->columnas = orden;
    M = new double*[this->orden];
    for(int i = 0; i < this->orden; i++)
        M[i] = new double[this->orden];
}

Matriz::Matriz(int filas, int columnas){
    this->orden = filas; // para establecer compatibilidad con el código anterior
    this->filas = filas;
    this->columnas = columnas;
    M = new double*[this->filas];
    for(int i = 0; i < this->filas; i++)
        M[i] = new double[this->columnas];
}

Matriz::~Matriz(){
    for (int i = 0; i < orden; i++)
        delete[] M[i]; // liberar memoria de la segunda dimension

    delete[] M; // liberar memoria de la primera dimension
}
