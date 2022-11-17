#ifndef _MATRICES_
#define _MATRICES_

#include <iostream>
#include <cmath>
#include <random> // generar numeros aleatorios
#include <iomanip> // crear una tabla
//cabecera custom
#include <matriz_base.hpp>

using std::cout;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;

class Matrices : public MatrizBase{
public:
    Matrices(int orden) : MatrizBase(orden){};
    Matrices(int filas, int columnas) : MatrizBase(filas, columnas){};
    ~Matrices() { MatrizBase::~MatrizBase(); };
    double calcularDeterminante(void);
    Matrices* calcularInversa(double& deter);
private:
    double determinante(double** matriz, int orden);
    double cofactor(double** matriz, int orden, int fila, int columna);
    Matrices* traspuesta(void);
    // sobrecarga de operadores
    friend Matrices* operator+(Matrices& Matrices01, Matrices& Matrices02);
    friend Matrices* operator-(Matrices& Matrices01, Matrices& Matrices02);
    friend Matrices* operator*(Matrices& Matrices01, Matrices& matriz02);
    friend Matrices* operator*(Matrices& Matrices, double numero);
protected:
};

#endif
