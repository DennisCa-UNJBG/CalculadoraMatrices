#include <iostream>
#include <matriz.hpp>
#include <opermatrices.hpp>

using std::cout;
using std::cin;
using std::endl;

/* implementación de los metodos de la clase  OperacMatrices */

void OperacMatrices::deterMatriz(void){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(!cancelar){
        cout << "La determinante de la matriz '" << nombreMatriz << "' es: "
            << this->matrices[nombreMatriz]->calcularDeterminante()
            << endl;
    }
}

void OperacMatrices::inversaMatriz(void){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar) // se cancela la operacion ?
        return;

    double det = this->matrices[nombreMatriz]->calcularDeterminante();

    if(!this->matrices[nombreMatriz]->getIsCuadrado()){
        cout << "La matriz '" << nombreMatriz << "' no es cuadrada y no tiene inversa..." << endl;
        return;
    }

    if(det == 0){
        cout << "La determinante es CERO, la matriz no tiene inversa..." << endl;
        return;
    }

    Matriz* matriz = this->matrices[nombreMatriz]->calcularInversa(det);
    cout << "La inversa de la matriz '" << nombreMatriz << "' es :" << endl;
    matriz->imprimirMatriz(7);
    cout << "La determinante es: " << det << endl;
    delete matriz; // liberar memoria
}

void OperacMatrices::multiMatrices(void){
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

    if(this->matrices[nombreMatriz[0]]->getIsCuadrado() && this->matrices[nombreMatriz[1]]->getIsCuadrado()){
        Matriz* temp = *(this->matrices[nombreMatriz[0]]) * *(this->matrices[nombreMatriz[1]]);
        cout << "\nLa multiplicacion de las matrices ( " << nombreMatriz[0] << " * " << nombreMatriz[1] << " ) es:" << endl;
        temp->imprimirMatriz();
        delete temp; // liberar memoria
    } else {
        cout << "Por el momento es imposible operar este tipo de matrices ... " << endl;
    }
}

void OperacMatrices::multiEscalarMatriz(void){
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
}

void OperacMatrices::restarMatrices(void){
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
}

void OperacMatrices::sumarMatrices(void){
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
}

void OperacMatrices::salirMenuOper(void){
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
            cout << "No se puede operar, las matrices son de orden distinto..." << endl;
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
        if(this->matrices[Matriz01]->getFilas() != this->matrices[Matriz02]->getColumnas()){
            cout << "No se puede operar, las matrices son de orden distinto..." << endl;
            return true; // nocumple todos los requisitos de matrices NxM
        }
    }
    return false; // cumple todos los requisitos
}
