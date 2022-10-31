#ifndef _ECUACIONES_
#define _ECUACIONES_

#include <iostream>
#include <iomanip> // crear una tabla
#include <random> // generar numeros aleatorios
#include <cmath> // para usar la funcion valor absoluto - abs()

using std::cout;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;
using std::setprecision;
using std::abs;

class Ecuaciones{
public:
    static int MIN; // minimo valor aleatorio
    static int MAX; // maximo valor aleatorio
    Ecuaciones(int cantIncognitas);
    ~Ecuaciones();
    void imprimir(int espacios = 7); // min 5
    void rellenar(void);
    void metodoGauss(void);
    void metodoGaussSeidel(int cantIter);
    // metodo para ordenar ecuaciones por el primer elemento de mayor a menor
    void pivoteoMatriz(int fil, int col); // pivoteo
private:
    double** matriz;
    int filas;
    int columnas;
    void imprimirIncognitas(double* array);
protected:
};

#endif
