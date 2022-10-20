#include <iostream>
#include <vector>
#include <sstream> // convertir string a int
// libreria custom
#include <operecuaciones.hpp>
#include <ecuaciones.hpp>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::stringstream;
using std::endl;

struct Operaciones{  /* estructura para controlar las opciones del menu de operaciones */
    string opciones;
    void (OperEcuaciones::*method)(void);
};

vector <Operaciones> MenuEcuaciones = { // opciones del menu de operaciones
    { "Crear nueva matriz",                      &OperEcuaciones::crearMatriz }
    ,{ "Ver matrices de ecuaciones existentes",  &OperEcuaciones::crearMatriz }
    ,{ "Calcular incognitas - Gauss",            &OperEcuaciones::crearMatriz }
    ,{ "Regresar al menu Principal",             &OperEcuaciones::salirMenu }
}; // empleamos los punteros a metodos de clase

void OperEcuaciones::mostrarMenu(){
    while(openMenu){
        system("cls");

        string sOpcion;
        int iOpcion;
        mostrarOpciones();

        cout << "\nSelecciona una opcion del menu: ";
        cin.sync(); getline(cin,sOpcion);

        //convertir lo que se ingrese a entero omitiendo letras y signos
        stringstream ss;
        ss << sOpcion;
        ss >> iOpcion;

        seleccionarOpcion(iOpcion);
    }
}

void OperEcuaciones::crearMatriz(){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int cantIncognitas;
    cout << "\nIngrese un nombre(sin espacios):" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "\nIngrese la cantidad de incognitas: " << endl;
    cin >> cantIncognitas;
    this->agregarMatriz(cantIncognitas, nombre) ;
}

void OperEcuaciones::agregarMatriz(int& cantIncognitas, string&nombre){
    Ecuaciones* matriz = new Ecuaciones(cantIncognitas);
    matriz->rellenar();
    cout << "\nLa matriz de ecuaciones tiene los valores es:" << endl;
    matriz->imprimir();
    matrices[nombre] = matriz;
}

void OperEcuaciones::salirMenu(void){
    openMenu = false;
}

void  OperEcuaciones::mostrarOpciones(){
    cout << "\n\tOPERACIONES CON ECUACIONES\n"
        << "******************************************\n"
        << endl;

    for(size_t i = 0; i < MenuEcuaciones.size(); i++)
        cout << i+1 << ". " << MenuEcuaciones[i].opciones << endl;
}

void OperEcuaciones::seleccionarOpcion(int opcion){
    if((size_t)opcion > MenuEcuaciones.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (this->*MenuEcuaciones[opcion-1].method)();

    // no lanzar el pause si se elige la ultima opcion
    if((size_t)opcion != MenuEcuaciones.size())
        system("pause");
}
