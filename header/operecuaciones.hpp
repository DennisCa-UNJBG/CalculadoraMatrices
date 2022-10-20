/*
https://youtu.be/8M7zmRbv4oc?t=586
https://www.youtube.com/watch?v=3ntJqA_aF-0

*/

#ifndef _LINEALES_
#define _LINEALES_

#include <map>
#include <string>
#include <ecuaciones.hpp>

using std::map;
using std::string;

class OperEcuaciones{
public:
    map<string, Ecuaciones*>matrices; // estructura clave/valor (contiene todas las matrices)
    static bool openMenu;
    // menu
    void mostrarMenu(void);
    void mostrarOpciones(void);
    void seleccionarOpcion(int opcion);
    // operaciones
    void crearMatriz();
    void salirMenu(void);
private:
    void agregarMatriz(int& cantIncognitas, string&nombre);
protected:
};

#endif