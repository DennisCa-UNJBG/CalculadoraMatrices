#ifndef _CONFIGVAR_
#define _CONFIGVAR_

#include <iostream>

using std::string;

class VariablesConfig{
public:
    // imprimir matrices
    static int TABLA;
    static int coordenadaY;
    static int coordenadaX;
    // menus
    static bool openMenu;
    static int clickMenu;
    // crear matriz
    static bool clicAgregar;
    static string name;
    static string filas;
    static string columnas;
    static string impriMatriz;
    // calcular determinante
    static string nameMatrizBuscar;
    static string nameMatriz;
    static bool mouseOverDeter;
    static bool CancelDeter;
    static bool clickDeter;
private:
    void test();
protected:
};
#endif
