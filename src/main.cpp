#include <vector>
#include <map>
#include <iostream>
#include <sstream> // convertir string a int

// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>

using namespace std;

/* varibles globales de configuracion */
bool ejecutando = true; // variable global que mantiene vivo el programa
bool OperacMatrices::openMenu = true; // true -> menu 01 , false -> menu 02

/* opciones del menu principal */
void menuPrincipal();
void menuOperacMatrices();
void opcionSelecMenuPrinc(OperacMatrices* misMatrices, int opcion);
void crearMatriz(OperacMatrices* misMatrices, int opcion);
void abrirMenuOpMatrices(OperacMatrices* misMatrices, int opcion);
void verMatrices(OperacMatrices* misMatrices, int opcion);
void salirPrograma(OperacMatrices* misMatrices, int opcion);

/* opciones del menu secundario(operaciones) */
void opcionSelecMenuOper(OperacMatrices* misMatrices, int opcion);

struct OperMenu{ /* estructura para controlar las opciones del menu principal */
    string opciones;
    void (*func) (OperacMatrices* misMatrices, int opcion);
};

vector<OperMenu> MenuPrincipal = { // opciones del menu principal
    { "Crear nueva matriz",          crearMatriz },
    { "Operaciones con matrices",    abrirMenuOpMatrices },
    { "Ver matrices existentes",     verMatrices },
    { "Salir",                       salirPrograma }
}; // empleamos los punteros a funciones

struct OperMenu02{  /* estructura para controlar las opciones del menu de operaciones */
    string opciones;
    void (OperacMatrices::*method) (void);
};

vector <OperMenu02> MenuOperaciones = { // opciones del menu de operaciones
    { "Calcular la inversa de una matriz",       &OperacMatrices::inversaMatriz }, // 1 matriz X
    { "Calcular la determinante de una matriz",  &OperacMatrices::deterMatriz }, // 1 matriz X
    { "Sumar matrices",                          &OperacMatrices::sumarMatrices }, // 2 matrices
    { "Restar matrices",                         &OperacMatrices::restarMatrices }, // 2 matrices
    { "multiplar matrices",                      &OperacMatrices::multiMatrices }, // 2 matrices
    { "multiplar matriz por un escalar",         &OperacMatrices::multiEscalarMatriz }, // 1 matriz X y 1 entero
    { "Regresar al menu Principal",              &OperacMatrices::salirMenuOper } // cambiar variable global
}; // empleamos los punteros a metodos de clase

int main(/*int argc, char *argv[]*/){ /* programa principal */
    OperacMatrices misMatrices = OperacMatrices();
    while(ejecutando){
        system("cls");

        string sOpcion;
        int iOpcion;
        OperacMatrices::openMenu ? menuPrincipal() : menuOperacMatrices();

        cout << "\nSelecciona una opcion del menu: ";
        cin.sync(); getline(cin,sOpcion);

        //convertir lo que se ingrese a entero omitiendo letras y signos
        stringstream ss;
        ss << sOpcion;
        ss >> iOpcion;

        OperacMatrices::openMenu ? opcionSelecMenuPrinc(&misMatrices, iOpcion) : opcionSelecMenuOper(&misMatrices, iOpcion);
    }
    return 0;
}

/* implementación de las funciones relacionadas al menu 02 */
void opcionSelecMenuOper(OperacMatrices* misMatrices, int opcion){
    if((size_t)opcion > MenuOperaciones.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (misMatrices->*MenuOperaciones[opcion-1].method)();

    // no lanzar el pause si se elige la ultima opcion
    if((size_t)opcion != MenuOperaciones.size())
        system("pause");
}

/* implementación de las funciones relacionadas al menu 01 */
void salirPrograma(OperacMatrices* misMatrices, int /*opcion*/){
    map<string, Matriz*>::iterator iterador;
    for (iterador = misMatrices->matrices.begin(); iterador != misMatrices->matrices.end(); iterador++){
        Matriz* valor = iterador->second;
        delete valor; // liberando memoria de cada matriz
    }

    delete misMatrices; // liberando memoria
    ejecutando = false;
}

void verMatrices(OperacMatrices* misMatrices, int /*opcion*/){
    map<string, Matriz*>::iterator iterador;
    cout << "\n\nImprimiendo matrices almacenadas: \n" << endl;
    for (iterador = misMatrices->matrices.begin(); iterador != misMatrices->matrices.end(); iterador++){
        // "first" tiene la clave. "second" el valor
        string clave = iterador->first;
        Matriz* valor = iterador->second;
        // usamos las variables Clave/Valor para mostrar resultados en pantalla
        cout << "La matriz : " << clave
            << "\nTiene los  valores:" << endl;
        valor->imprimirMatriz();
    }
}

void abrirMenuOpMatrices(OperacMatrices* /*misMatrices*/, int /*opcion*/){
    OperacMatrices::openMenu = false;
    system("cls");
    menuOperacMatrices();
}

void crearMatriz(OperacMatrices* misMatrices, int /*opcion*/){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int orden;
    cout << "Ingrese un nombre(sin espacios) para la matriz:" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "Ingrese dimension de la matriz: " << endl;
    cin >> orden;

    misMatrices->agregarMatriz(orden, nombre);
}

void opcionSelecMenuPrinc(OperacMatrices* misMatrices, int opcion){
    if((size_t)opcion > MenuPrincipal.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        MenuPrincipal[opcion-1].func(misMatrices, 0);

    // no lanzar el pause si se elige el menu 02 por 1º vez
    if(OperacMatrices::openMenu != false)
        system("pause");
}

void menuOperacMatrices(){
    cout << "\n\tOPERACIONES CON MATRICES\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuOperaciones.size(); i++)
        cout << i+1 << ". " << MenuOperaciones[i].opciones << endl;
}

void menuPrincipal(){
    cout << "\n\tMENU PRINCIPAL\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuPrincipal.size(); i++)
        cout << i+1 << ". " << MenuPrincipal[i].opciones << endl;
}
