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

    if(!(this->matrices[nombreMatriz[0]]->getOrden() == this->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

    Matriz* temp = *(this->matrices[nombreMatriz[0]]) * *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa multiplicacion de las matrices ( " << nombreMatriz[0] << " * " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimirMatriz();
    delete temp; // liberar memoria
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
    temp->imprimirMatriz();
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

    if(!(this->matrices[nombreMatriz[0]]->getOrden() == this->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

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

    if(!(this->matrices[nombreMatriz[0]]->getOrden() == this->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

    Matriz* temp = *(this->matrices[nombreMatriz[0]]) + *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa suma de las matrices ( " << nombreMatriz[0] << " + " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimirMatriz();
    delete temp;  // liberar memoria
}

void OperacMatrices::salirMenuOper(void){
    OperacMatrices::openMenu = true;
}

void OperacMatrices::agregarMatriz(int& orden, string&nombre){
    Matriz* matriz = new Matriz(orden);
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
