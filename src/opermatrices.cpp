#include <iostream>
// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>
#include <config.hpp>
// raylib
#include <raylib.h>

using std::cout;
using std::cin;
using std::endl;

/* implementación de los metodos de la clase  OperacMatrices */

void OperacMatrices::deterMatriz(void){
    DrawText("Test: calcular determinante de una matriz:", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    if(!this->matrices[nombreMatriz]->getIsCuadrado()){
        cout <<  "La matriz '" << nombreMatriz << "' no tiene determinante, no es cuadrada... " << endl;
        return;
    }

    cout << "La determinante de la matriz '" << nombreMatriz << "' es: "
        << this->matrices[nombreMatriz]->calcularDeterminante()
        << endl;
    */
}

void OperacMatrices::inversaMatriz(void){
    DrawText("Test: calcular inversa de una matriz", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar) // se cancela la operacion ?
        return;

    if(!this->matrices[nombreMatriz]->getIsCuadrado()){
        cout << "La matriz '" << nombreMatriz << "' no tiene inversa, no es cuadrada..." << endl;
        return;
    }

    double det = this->matrices[nombreMatriz]->calcularDeterminante();
    if(det == 0){
        cout << "La determinante es CERO, la matriz no tiene inversa..." << endl;
        return;
    }

    Matriz* matriz = this->matrices[nombreMatriz]->calcularInversa(det);
    cout << "La inversa de la matriz '" << nombreMatriz << "' es :" << endl;
    matriz->imprimirMatriz(7);
    cout << "La determinante es: " << det << endl;
    delete matriz; // liberar memoria
    */
}

void OperacMatrices::multiMatrices(void){
    DrawText("Test: multiplicar matrices:", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        this->buscarMatriz(cancelar, i+1, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(this->noCumpleReqMulti(nombreMatriz[0], nombreMatriz[1]))
        return;

    Matriz* temp = *(this->matrices[nombreMatriz[0]]) * *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa multiplicacion de las matrices ( " << nombreMatriz[0] << " * " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimirMatriz();
    delete temp; // liberar memoria
    */
}

void OperacMatrices::multiEscalarMatriz(void){
    DrawText("Test: multiplicar matriz por un escalar:", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar) // se cancela la operacion ?
        return;

    double numero;
    cout << "Ingrese el escalar: " << endl;
    cin >> numero;

    Matriz* temp = *(this->matrices[nombreMatriz]) * numero;
    cout << "\nLa multiplicacion de la matriz ( " << nombreMatriz << " * " << numero << " ) es:" << endl;
    temp->imprimirMatriz(7);
    delete temp; // liberar memoria
    */
}

void OperacMatrices::restarMatrices(void){
    DrawText("Test: restar matrices:", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        this->buscarMatriz(cancelar, i+1, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(this->noCumpleReqSumRest(nombreMatriz[0], nombreMatriz[1]))
        return;

    Matriz* temp = *(this->matrices[nombreMatriz[0]]) - *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa resta de las matrices ( " << nombreMatriz[0] << " - " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimirMatriz();
    delete temp;  // liberar memoria
    */
}

void OperacMatrices::sumarMatrices(void){
    DrawText("Test: sumar matrices:", 340, 30, 20, DARKBLUE);
    /*
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        this->buscarMatriz(cancelar, i+1, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(this->noCumpleReqSumRest(nombreMatriz[0], nombreMatriz[1]))
        return;

    Matriz* temp = *(this->matrices[nombreMatriz[0]]) + *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa suma de las matrices ( " << nombreMatriz[0] << " + " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimirMatriz();
    delete temp;  // liberar memoria
    */
}

void OperacMatrices::mostrarMenuPrincipal(void){
    OperacMatrices::openMenu = true;
}

void OperacMatrices::agregarMatriz(int& filas, int& columnas, string&nombre){
    Matriz* matriz;                 //crear matriz cuadrada         // crear matriz no cuadrada
    (filas == columnas) ? matriz = new Matriz(filas) : matriz = new Matriz(filas, columnas);
    matriz->rellenarMatriz();
    cout << "\nLa matriz ingresada tiene los valores es:" << endl;
    matriz->imprimirMatriz();
    matrices[nombre] = matriz;
}

void OperacMatrices::buscarMatriz(bool& cancelar, int cantMatriz, string& nombre){
    bool matrizEncontrada = false;
    int intentos = 2;
    do{
        cout << "\nIngrese el nombre de la matriz 0" << cantMatriz << ": " << endl;
        cin.sync(); getline(cin,nombre);

        if (this->matrices.count(nombre)){ // count() -> verifica si existe un item con X nombre
            cout << "Sus elementos son:" << endl;
            this->matrices[nombre]->imprimirMatriz();
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

bool OperacMatrices::noCumpleReqSumRest(string& Matriz01, string& Matriz02){
    if((this->matrices[Matriz01]->getIsCuadrado() && this->matrices[Matriz02]->getIsCuadrado())){
        if(this->matrices[Matriz01]->getOrden() != this->matrices[Matriz02]->getOrden()){
        cout << "No se puede operar, las matrices son de dimensiones distintas..." << endl;
        return true; // no cumple todos los requisitos de matrices NxN
        }
    } else {
        if(this->matrices[Matriz01]->getFilas() != this->matrices[Matriz02]->getFilas() ||
            this->matrices[Matriz01]->getColumnas() != this->matrices[Matriz02]->getColumnas()){
            cout << "No se puede operar, las matrices no coinciden en sus dimensiones..." << endl;
            return true; // nocumple todos los requisitos de matrices NxM
        }
    }
    return false; // cumple todos los requisitos
}

bool OperacMatrices::noCumpleReqMulti(string& Matriz01, string& Matriz02){
    if((this->matrices[Matriz01]->getIsCuadrado() && this->matrices[Matriz02]->getIsCuadrado())){
        if(this->matrices[Matriz01]->getOrden() != this->matrices[Matriz02]->getOrden()){
        cout << "No se puede operar, las matrices son de dimensiones distintas..." << endl;
        return true; // no cumple todos los requisitos de matrices NxN
        }
    } else {
        if(this->matrices[Matriz01]->getColumnas() != this->matrices[Matriz02]->getFilas()){
            cout << "No se puede operar, las columnas de la matriz'" << Matriz01
                << "' y las filas de la matriz '" << Matriz02 << "' no coinciden ..." << endl;
            return true; // nocumple todos los requisitos de matrices NxM
        }
    }
    return false; // cumple todos los requisitos
}

void OperacMatrices::crearMatriz(){ // se omite la variable opcion en la compilacion del programa
    DrawText("Test: Crear matriz:", 340, 30, 20, DARKBLUE);
    /*
    string nombre;
    int filas, columnas;
    cout << "Ingrese un nombre(sin espacios) para la matriz:" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;

    this->agregarMatriz(filas, columnas, nombre) ;
    */
}

void OperacMatrices::mostrarMenuOpMatrices(){
    OperacMatrices::openMenu = false;
    VariablesConfig::clickOpcion = -1;
}

void OperacMatrices::verMatrices(){
    DrawText("Test: ver matrices:", 340, 30, 20, DARKBLUE);
    /*
    map<string, Matriz*>::iterator iterador;
    cout << "\n\nImprimiendo matrices almacenadas: \n" << endl;
    for (iterador = this->matrices.begin(); iterador != this->matrices.end(); iterador++){
        // "first" tiene la clave. "second" el valor
        string clave = iterador->first;
        Matriz* valor = iterador->second;
        // usamos las variables Clave/Valor para mostrar resultados en pantalla
        cout << "La matriz : " << clave
            << "\nTiene los  valores:" << endl;
        valor->imprimirMatriz();
    }
    */
}

void OperacMatrices::salirPrograma(){
    map<string, Matriz*>::iterator iterador;
    for (iterador = this->matrices.begin(); iterador != this->matrices.end(); iterador++){
        Matriz* valor = iterador->second;
        delete valor; // liberando memoria de cada matriz
    }
    CloseWindow();
}
