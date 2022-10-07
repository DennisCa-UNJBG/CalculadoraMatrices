#include <iostream>
#include <matriz.hpp>
#include <opermatrices.hpp>

using std::cout;
using std::cin;
using std::endl;

/* implementación de los metodos de la clase  OperacMatrices */

void OperacMatrices::deterMatriz(OperacMatrices* misMatrices){
    string nombreMatriz;
    bool cancelar = false;
    int i = 0;
    // buscar la matriz que se necesita para la operacion
    misMatrices->buscarMatriz(cancelar, i, nombreMatriz);

    if(!cancelar){
        cout << "La determinante de la matriz '" << nombreMatriz << "' es: "
            << misMatrices->matrices[nombreMatriz]->calcularDeterminante()
            << endl;
    }
}

void OperacMatrices::inversaMatriz(OperacMatrices* misMatrices){
    string nombreMatriz;
    bool cancelar = false;
    int i = 0;
    // buscar la matriz que se necesita para la operacion
    misMatrices->buscarMatriz(cancelar, i, nombreMatriz);

    if(cancelar) // se cancela la operacion ?
        return;

    double det = misMatrices->matrices[nombreMatriz]->calcularDeterminante();
    if(det == 0){
        cout << "La determinante es CERO, la matriz no tiene inversa..." << endl;
        return;
    }

    Matriz* matriz = misMatrices->matrices[nombreMatriz]->calcularInversa(det);
    cout << "La inversa de la matriz '" << nombreMatriz << "' es :" << endl;
    matriz->imprimirMatriz(7);
    cout << "La determinante es: " << det << endl;
    delete matriz; // liberar memoria
}

void OperacMatrices::multiMatrices(OperacMatrices* misMatrices){
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        misMatrices->buscarMatriz(cancelar, i, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(!(misMatrices->matrices[nombreMatriz[0]]->getOrden() == misMatrices->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

    Matriz* temp = *(misMatrices->matrices[nombreMatriz[0]]) * *(misMatrices->matrices[nombreMatriz[1]]);
    cout << "\nLa multiplicacion de las matrices es:" << endl;
    temp->imprimirMatriz();
    delete temp; // liberar memoria
}

void OperacMatrices::multiEscalarMatriz(OperacMatrices* misMatrices){
    string nombreMatriz;
    bool cancelar = false;
    int i = 0;
    // buscar la matriz que se necesita para la operacion
    misMatrices->buscarMatriz(cancelar, i, nombreMatriz);

    if(cancelar) // se cancela la operacion ?
        return;

    double numero;
    cout << "Ingrese el escalar: " << endl;
    cin >> numero;

    Matriz* temp = *(misMatrices->matrices[nombreMatriz]) * numero;
    cout << "\nLa multiplicacion por el escalar es:" << endl;
    temp->imprimirMatriz();
    delete temp; // liberar memoria
}

void OperacMatrices::restarMatrices(OperacMatrices* misMatrices){
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        misMatrices->buscarMatriz(cancelar, i, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(!(misMatrices->matrices[nombreMatriz[0]]->getOrden() == misMatrices->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

    Matriz* temp = *(misMatrices->matrices[nombreMatriz[0]]) - *(misMatrices->matrices[nombreMatriz[1]]);
    cout << "\nLa resta de las matrices es:" << endl;
    temp->imprimirMatriz();
    delete temp;  // liberar memoria
}

void OperacMatrices::sumarMatrices(OperacMatrices* misMatrices){
    string nombreMatriz[2];
    bool cancelar = false;
    int i = 0;
    // buscar las 2 matrices que se necesitan para la operacion
    while (i < 2 && !cancelar){
        misMatrices->buscarMatriz(cancelar, i, nombreMatriz[i]);
        i++;
    }

    if(cancelar) // se cancela la operacion ?
        return;

    if(!(misMatrices->matrices[nombreMatriz[0]]->getOrden() == misMatrices->matrices[nombreMatriz[1]]->getOrden())){
        cout << "No se puede operar, las matrices son de orden distinto..." << endl;
        return;
    }

    Matriz* temp = *(misMatrices->matrices[nombreMatriz[0]]) + *(misMatrices->matrices[nombreMatriz[1]]);
    cout << "\nLa suma de las matrices es:" << endl;
    temp->imprimirMatriz();
    delete temp;  // liberar memoria
}

void OperacMatrices::salirMenuOper(OperacMatrices* /*misMatrices*/){
    OperacMatrices::openMenu = true;
}

void OperacMatrices::agregarMatriz(int& orden, string&nombre){
    Matriz* matriz = new Matriz(orden);
    matriz->rellenarMatriz();
    cout << "\nLa matriz ingresada tiene los valores es:" << endl;
    matriz->imprimirMatriz();
    matrices[nombre] = matriz;
}

void OperacMatrices::buscarMatriz(bool& cancelar, int& idMatriz, string& nombre){
    bool matrizEncontrada = false;
    int intentos = 2;
    do{
        cout << "\nIngrese el nombre de la matriz 0" << idMatriz+1 << ": " << endl;
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
