#ifndef _OPERCMATRICES_
#define _OPERCMATRICES_

#include <map>
#include <string>
// incluir librerias custom
#include <matriz.hpp>
// raylib
#include <raylib.h>

using std::map;
using std::string;

class OperacMatrices{ /* clase global de operaciones */
public:
    map<string, Matriz*>matrices; // estructura clave/valor (contiene todas las matrices)
    static bool openMenu;
    //operaciones disponibles menu 01
    void crearMatriz();
    void mostrarMenuOpMatrices();
    void verMatrices();
    void salirPrograma();
    //operaciones disponibles menu 02
    void deterMatriz(void);
    void inversaMatriz(void);
    void sumarMatrices(void);
    void restarMatrices(void);
    void multiMatrices(void );
    void multiEscalarMatriz(void);
    void mostrarMenuPrincipal(void);
private:
    void agregarMatriz(int filas, int columnas, string&nombre);
    void buscarMatriz(bool& cancelar, int cantMatriz, string& nombre /* retorna el nombre de la matriz*/);
    bool noCumpleReqSumRest(string& Matriz01, string& Matriz02);
    bool noCumpleReqMulti(string& Matriz01, string& Matriz02);
    // extras
    void input_box(Rectangle& boton, Color color, string& variable);
protected:
};

#endif
