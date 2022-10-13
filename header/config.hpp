#ifndef _CONFIGVAR_
#define _CONFIGVAR_

#include <iostream>

using std::string;

class VariablesConfig{
public:
    // menus
    static int clickMenu;
    // imprimir matrices
    static int TABLA;
    static int coordenadaY;
    static int coordenadaX;
    // crear matriz
    static bool clicAgregar;
    static string name;
    static string filas;
    static string columnas;
    static string impriMatriz;
private:
protected:
};

#endif
