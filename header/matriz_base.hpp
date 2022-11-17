#ifndef _MATRIZ_BASE_
#define _MATRIZ_BASE_

#include <iostream>
#include <cmath>
#include <random> // generar numeros aleatorios
#include <iomanip> // crear una tabla

using std::cout;
using std::cin;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;

class MatrizBase{ /* clase base de una matriz */
public:
    static int TABLA;
    static int MIN;
    static int MAX;
    MatrizBase(int orden);
    MatrizBase(int filas, int columnas);
    virtual ~MatrizBase();
    virtual void imprimir(int espacios = TABLA);
    void rellenar(void);
    void rellenarAleatoriamente(void);
    inline int getOrden(void) { return orden; }
    inline bool getIsCuadrado(void) { return isCuadrado; }
    inline int getFilas(void) { return filas; }
    inline int getColumnas(void) { return columnas; }
    inline void setFilas(int cant) { filas = cant; }
    inline void setColumnas(int cant) { columnas = cant; }
    inline double** getMatriz(void) { return matriz; }
private:
    double** matriz;
    int orden;
    int filas;
    int columnas;
    bool isCuadrado = false;
protected:
};

#endif
