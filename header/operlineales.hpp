/*
https://youtu.be/8M7zmRbv4oc?t=586
https://www.youtube.com/watch?v=3ntJqA_aF-0
https://youtu.be/Con1JRZLbqM?t=383
*/

#ifndef _OPER_LINEALES_
#define _OPER_LINEALES_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream> // convertir string a int
// cabecera custom
#include <lineales.hpp>

using std::map;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::stringstream;

class OperEcuaLineales{
public:
    map<string, EcuaLineales*>matrices; // estructura clave/valor (contiene todas las matrices)
    static bool openMenu;
    // menu
    void mostrarMenu(void);
    void mostrarOpciones(void);
    void seleccionarOpcion(int opcion);
    // operaciones
    void crearMatriz(void);
    void verMatrices(void);
    void calcularGauss(void);
    void calcularGaussSiedel(void);
    void salirMenu(void);
private:
    void agregarMatriz(int& cantIncognitas, string&nombre);
    void buscarMatriz(bool& cancelar, int cantMatriz, string& nombre /* retorna el nombre de la matriz*/);
protected:
};

#endif