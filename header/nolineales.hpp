#ifndef _NO_LINEALES_
#define _NO_LINEALES_

#include <iostream>
#include <iomanip> // crear una tabla
#include <random> // generar numeros aleatorios
#include <cmath> // para usar la funcion valor absoluto - abs()
// cabecera custom
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

class EcuNoLineales : public MatrizBase{
public:
    EcuNoLineales(int cantIncognitas) : MatrizBase(1, cantIncognitas){};
    ~EcuNoLineales(){ MatrizBase::~MatrizBase(); };
    inline EcuNoLineales* getDerivada(void) { return derivada; }
    void imprimir(int espacios = 5) override; // min 4
    void metodoNewtonRaphson(double valX);
    // biseccion
    // punto fijo multivariable
    // raphson modificado
private:
    EcuNoLineales* derivada = nullptr;
    void obtenerDerivar(void); // newton-raphson
    double calcFuncion(double valX); // newton-raphson
protected:
};

#endif
