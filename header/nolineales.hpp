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
    void imprimir(int espacios = 7) override; // min 5
    void metodoNewtonRaphson(void);
private:
protected:
};

#endif
