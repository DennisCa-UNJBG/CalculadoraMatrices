#include <vector>
#include <map>
#include <iostream>
#include <sstream> // convertir string a int

// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>
#include <ecuaciones.hpp>
#include <operecuaciones.hpp>

using namespace std;

/* varibles globales de configuracion */
bool ejecutando = true; // variable global que mantiene vivo el programa
bool OperacMatrices::openMenu = false; // true -> abrir menu , false -> cerrar menu
int Matriz::MIN = -10; // minimo valor aleatorio
int Matriz::MAX = 10; // maximo valor aleatorio
int Matriz::TABLA = 4; // espacios para ordenar valores en la tabla
OperacMatrices misMatrices = OperacMatrices();
bool OperEcuaciones::openMenu = false; // true -> abrir menu , false -> cerrar menu
int Ecuaciones::MIN = -10; // minimo valor aleatorio
int Ecuaciones::MAX = 10; // maximo valor aleatorio
OperEcuaciones misEcuaciones = OperEcuaciones();

/* opciones del menu principal */
void menuPrincipal(void);
void opcionSelecMenuPrinc(int opcion);
void abrirMenuMatrices(int opcion);
void abrirMenuEcuaciones(int opcion);
void salirPrograma(int opcion);

struct OperMenu{ /* estructura para controlar las opciones del menu principal */
    string opciones;
    void (*func) (int opcion);
};

vector<OperMenu> MenuPrincipal = { // opciones del menu principal
    { "Operaciones con matrices",               abrirMenuMatrices },
    { "Operaciones con ecuaciones lineales",    abrirMenuEcuaciones },
    { "Salir",                                  salirPrograma }
}; // empleamos los punteros a funciones

int main(/*int argc, char *argv[]*/){ /* programa principal */
    while(ejecutando){
        system("cls");

        string sOpcion;
        int iOpcion;
        menuPrincipal();

        cout << "\nSelecciona una opcion del menu: ";
        cin.sync(); getline(cin,sOpcion);

        //convertir lo que se ingrese a entero omitiendo letras y signos
        stringstream ss;
        ss << sOpcion;
        ss >> iOpcion;

        opcionSelecMenuPrinc(iOpcion);
    }
    return 0;
}

void salirPrograma(int /*opcion*/){
    //borrar memoria de las operaciones con matrices
    map<string, Matriz*>::iterator iterador01;
    for (iterador01 = misMatrices.matrices.begin(); iterador01 != misMatrices.matrices.end(); iterador01++){
        Matriz* valor = iterador01->second;
        delete valor; // liberando memoria de cada matriz
    }
    //borrar memoria de las operaciones con ecuaciones
    map<string, Ecuaciones*>::iterator iterador02;
    for (iterador02 = misEcuaciones.matrices.begin(); iterador02 != misEcuaciones.matrices.end(); iterador02++){
        Ecuaciones* valor = iterador02->second;
        delete valor; // liberando memoria de cada matriz
    }
    ejecutando = false;
}

void abrirMenuEcuaciones(int /*opcion*/){
    OperEcuaciones::openMenu = true;
    system("cls");
    misEcuaciones.mostrarMenu();
}

void abrirMenuMatrices(int /*opcion*/){
    OperacMatrices::openMenu = true;
    system("cls");
    misMatrices.mostrarMenu();
}

void opcionSelecMenuPrinc(int opcion){
    if((size_t)opcion > MenuPrincipal.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        MenuPrincipal[opcion-1].func(0);

    // no lanzar el pause si se elige el menu de matrices por 1º vez
    if(OperacMatrices::openMenu != false)
        system("pause");
}

void menuPrincipal(void){
    cout << "\n\tMENU PRINCIPAL\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuPrincipal.size(); i++)
        cout << i+1 << ". " << MenuPrincipal[i].opciones << endl;
}
