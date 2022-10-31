#ifndef _OPERCMATRICES_
#define _OPERCMATRICES_

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream> // convertir string a int
// cabecera custom
#include <matriz.hpp>

using std::map;
using std::string;
using std::cout;
using std::vector;
using std::cin;
using std::stringstream;
using std::endl;

class OperacMatrices{ /* clase global de operaciones */
public:
    map<string, Matriz*>matrices; // estructura clave/valor (contiene todas las matrices)
    static bool openMenu;
    // menu
    void mostrarMenu(void);
    void mostrarOpciones(void);
    void seleccionarOpcion(int opcion);
    //operaciones disponibles
    void crearMatriz(void);
    void verMatrices(void);
    void deterMatriz(void);
    void inversaMatriz(void);
    void sumarMatrices(void);
    void restarMatrices(void);
    void multiMatrices(void );
    void multiEscalarMatriz(void);
    void salirMenuOper(void);
private:
    void agregarMatriz(int& filas, int& columnas, string&nombre);
    void buscarMatriz(bool& cancelar, int cantMatriz, string& nombre /* retorna el nombre de la matriz*/);
    bool noCumpleReqSumRest(string& Matriz01, string& Matriz02);
    bool noCumpleReqMulti(string& Matriz01, string& Matriz02);
protected:
};

#endif
