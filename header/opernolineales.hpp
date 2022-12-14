/*
https://youtu.be/8M7zmRbv4oc?t=586
https://www.youtube.com/watch?v=3ntJqA_aF-0
https://youtu.be/Con1JRZLbqM?t=383
*/

#ifndef _OPER_NO_LINEALES_
#define _OPER_NO_LINEALES_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream> // convertir string a int
// cabecera custom
#include <nolineales.hpp>

using std::map;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::stringstream;

class OperEcuNoLineales{
public:
    map<string, EcuNoLineales*>matrices; // estructura clave/valor (contiene todas las matrices)
    static bool openMenu;
    // menu
    void mostrarMenu(void);
    void verMatrices(void);
    void salirMenu(void);
    void mostrarOpciones(void);
    void seleccionarOpcion(int opcion);
    // operaciones
    void crearEcuacion(void);
    void calcularNewtonRaphson(void);
private:
    void agregarMatriz(int& cantIncognitas, string&nombre);
    void buscarMatriz(bool& cancelar, int cantMatriz, string& nombre /* retorna el nombre de la matriz*/);
protected:
};

#endif