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
    ,{ "Ver matrices de ecuaciones existentes",  &OperEcuaciones::verMatrices }
    ,{ "Calcular incognitas - Gauss",            &OperEcuaciones::calcularGauss }
    ,{ "Calcular incognitas - Gauss Seidel",     &OperEcuaciones::calcularGaussSiedel }
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
void OperEcuaciones::calcularGaussSiedel(){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    int iteraciones = 0;
    cout << "ingrese la cantidad de iteraciones :" << endl;
    cin >> iteraciones;
    cout << "La matriz '" << nombreMatriz
        << "' esta siendo procesada empleando Gauss-Seidel." << endl;
    this->matrices[nombreMatriz]->metodoGaussSeidel(iteraciones);
}

void OperEcuaciones::calcularGauss(){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    cout << "La matriz '" << nombreMatriz
        << "' esta siendo procesada empleando Gauss." << endl;
    this->matrices[nombreMatriz]->metodoGauss();
}

void OperEcuaciones::verMatrices(){
    map<string, Ecuaciones*>::iterator iterador;
    cout << "\n\nImprimiendo matrices de ecuaciones lineales almacenadas: \n" << endl;
    for (iterador = this->matrices.begin(); iterador != this->matrices.end(); iterador++){
        // "first" tiene la clave. "second" el valor
        string clave = iterador->first;
        Ecuaciones* valor = iterador->second;
        // usamos las variables Clave/Valor para mostrar resultados en pantalla
        cout << "La matriz de ecuaciones lineales: '" << clave
            << "'\nTiene los  valores:" << endl;
        valor->imprimir();
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
    char numAleatorios = false;
    cout << "\nRellenar los valores de forma aleatoria?(y/n): " << endl;
    cin >> numAleatorios;
    (numAleatorios == 'y') ? matriz->rellenarAleatoriamente() : matriz->rellenar();
    cout << "\nLa matriz de ecuaciones tiene los valores:" << endl;
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

void OperEcuaciones::buscarMatriz(bool& cancelar, int cantMatriz, string& nombre){
    bool matrizEncontrada = false;
    int intentos = 2; // cantidad de intentos para buscar una matriz
    do{
        cout << "\nIngrese el nombre de la matriz 0" << cantMatriz << ": " << endl;
        cin.sync(); getline(cin,nombre);

        if (this->matrices.count(nombre)){ // count() -> verifica si existe un item con X nombre
            cout << "Sus elementos son:" << endl;
            this->matrices[nombre]->imprimir();
            matrizEncontrada = true;
        } else {
            cout << "La matriz '" << nombre <<"' no se encuentra...\n"
                << "Le queda " << intentos << " intentos." << endl;

            if(intentos == 0)
                cancelar = true;

            intentos--;
        }
    }while (intentos >= 0 && !matrizEncontrada);
}
