#ifndef _OPERCMATRICES_
#define _OPERCMATRICES_

#include <map>
#include <string>
// incluir librerias custom
#include "matriz.hpp"

using std::map;
using std::string;

class OperacMatrices{ /* clase global de operaciones */
public:
    map<string, Matriz*>matrices; // estructura clave/valor (contiene todas las matrices)
    void agregarMatriz(int& filas, int& columnas, string&nombre);
    void buscarMatriz(bool& cancelar, int cantMatriz, string& nombre /* retorna el nombre de la matriz*/);
    bool noCumpleReqSumRest(string& Matriz01, string& Matriz02);
    bool noCumpleReqMulti(string& Matriz01, string& Matriz02);
    //operaciones disponibles
    void deterMatriz(void);
    void inversaMatriz(void);
    void sumarMatrices(void);
    void restarMatrices(void);
    void multiMatrices(void );
    void multiEscalarMatriz(void);
    void salirMenuOper(void);
    static bool openMenu;
private:
protected:
};

#endif
