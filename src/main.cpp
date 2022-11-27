#include <vector>
#include <map>
#include <iostream>
#include <sstream> // convertir string a int

// incluir librerias custom
#include <opermatrices.hpp>
#include <operlineales.hpp>
#include <opernolineales.hpp>

using namespace std;

/* varibles globales de configuracion */
int MatrizBase::MIN = -10;
int MatrizBase::MAX = 10;
int MatrizBase::TABLA = 4;
bool ejecutando = true; // variable global que mantiene vivo el programa
bool OperacMatrices::openMenu = false; // true -> abrir menu , false -> cerrar menu
OperacMatrices misMatrices = OperacMatrices();
bool OperEcuaLineales::openMenu = false; // true -> abrir menu , false -> cerrar menu
OperEcuaLineales EcuacionesLin = OperEcuaLineales();
bool OperEcuNoLineales::openMenu = false; // true -> abrir menu , false -> cerrar menu
OperEcuNoLineales EcuacionesNoLin = OperEcuNoLineales();

/* opciones del menu principal */
void menuPrincipal(void);
void opcionSelecMenuPrinc(int opcion);
void abrirMenuMatrices(int opcion);
void abrirMenuLineales(int opcion);
void abrirMenuNoLineales(int opcion);
void salirPrograma(int opcion);

struct OperMenu{ /* estructura para controlar las opciones del menu principal */
    string opciones;
    void (*func) (int opcion);
};

vector<OperMenu> MenuPrincipal = { // opciones del menu principal
    { "Operaciones con matrices",               abrirMenuMatrices },
    { "Operaciones con ecuaciones lineales",    abrirMenuLineales },
    { "Operaciones con ecuaciones no lineales",    abrirMenuNoLineales },
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
    map<string, Matrices*>::iterator iterador01;
    for (iterador01 = misMatrices.matrices.begin(); iterador01 != misMatrices.matrices.end(); iterador01++){
        Matrices* valor = iterador01->second;
        delete valor; // liberando memoria de cada matriz
    }
    //borrar memoria de las operaciones con ecuaciones lineales
    map<string, EcuaLineales*>::iterator iterador02;
    for (iterador02 = EcuacionesLin.matrices.begin(); iterador02 != EcuacionesLin.matrices.end(); iterador02++){
        EcuaLineales* valor = iterador02->second;
        delete valor; // liberando memoria de cada matriz
    }
    //borrar memoria de las operaciones con ecuaciones no lineales
    map<string, EcuNoLineales*>::iterator iterador03;
    for (iterador03 = EcuacionesNoLin.matrices.begin(); iterador03 != EcuacionesNoLin.matrices.end(); iterador03++){
        EcuNoLineales* valor = iterador03->second;
        EcuNoLineales* derivadas = valor->getDerivada();
        delete derivadas;
        delete valor; // liberando memoria de cada matriz
    }
    ejecutando = false;
}

void abrirMenuNoLineales(int /*opcion*/){
    OperEcuNoLineales::openMenu = true;
    system("cls");
    EcuacionesNoLin.mostrarMenu();
}

void abrirMenuLineales(int /*opcion*/){
    OperEcuaLineales::openMenu = true;
    system("cls");
    EcuacionesLin.mostrarMenu();
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
