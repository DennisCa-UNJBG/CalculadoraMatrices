#ifndef _LINEALES_
#define _LINEALES_

#include <iostream>
#include <iomanip> // crear una tabla
#include <random> // generar numeros aleatorios
#include <cmath> // para usar la funcion valor absoluto - abs()
//cabecera custom
#include <matriz_base.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::setw;
using std::setprecision;
using std::abs;

class EcuaLineales : public MatrizBase{
public:
    EcuaLineales(int cantIncognitas) : MatrizBase(cantIncognitas, cantIncognitas +1 ){};
    ~EcuaLineales(){ MatrizBase::~MatrizBase(); };
    void imprimir(int espacios = 7) override; // min 5
    void metodoGauss(void);
    void metodoGaussSeidel();
private:
    void imprimirIncognitas(double* array);
    // metodo para ordenar EcuaLineales por el primer elemento de mayor a menor
    void pivoteoMatriz(int fil, int col); // pivoteo
    bool DiagonalDominante(); // seidel
    bool EpsilonSeidel(double* oldSol, double* newSol, int cantidad); // seidel
protected:
};

#endif
