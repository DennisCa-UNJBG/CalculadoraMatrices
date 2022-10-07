#ifndef _OPERCMATRICES_
#define _OPERCMATRICES_

#include <map>
#include <string>
#include <matriz.hpp>

using std::map;
using std::string;

class OperacMatrices{ /* clase global de operaciones */
public:
    map<string, Matriz*>matrices; // estructura clave/valor (contiene todas las matrices)
    void agregarMatriz(int& orden, string&nombre);
    void buscarMatriz(bool& cancelar, int& idMatriz, string& nombre);
    //operaciones disponibles
    void deterMatriz(OperacMatrices* misMatrices);
    void inversaMatriz(OperacMatrices* misMatrices);
    void sumarMatrices(OperacMatrices* misMatrices);
    void restarMatrices(OperacMatrices* misMatrices);
    void multiMatrices(OperacMatrices* misMatrices );
    void multiEscalarMatriz(OperacMatrices* misMatrices);
    void salirMenuOper(OperacMatrices* misMatrices);
    static bool openMenu;
private:
protected:
};

#endif
