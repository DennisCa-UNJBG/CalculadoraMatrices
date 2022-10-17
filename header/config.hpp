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
    // calcular inversa
    static string nameInverBuscar;
    static string nameInver;
    static bool mouseOverInver;
    static bool clickInver;
    // sumar matrices
    static string nameSumaBuscar01;
    static string nameSumaBuscar02;
    static string nameSuma01;
    static string nameSuma02;
    static bool mouseOverSuma;
    static bool cancelSuma;
    static bool clickSuma;
    // restar matrices
    static string nameRestaBuscar01;
    static string nameRestaBuscar02;
    static string nameResta01;
    static string nameResta02;
    static bool mouseOverResta;
    static bool cancelResta;
    static bool clickResta;
    // multi matrices
    static string nameMultiBuscar01;
    static string nameMultiBuscar02;
    static string nameMulti01;
    static string nameMulti02;
    static bool mouseOverMulti;
    static bool cancelMulti;
    static bool clickMulti;
    // multi x escalar matrices
    static string nameEscalBuscar;
    static string nameEscalNum;
    static string nameEscal;
    static string Escalnum;
    static bool mouseOverEscal;
    static bool cancelEscal;
    static bool clickEscal;
private:
protected:
};
#endif
