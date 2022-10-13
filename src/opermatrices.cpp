#include <iostream>
#include <sstream> // contatenar variables en una sola
// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>
#include <config.hpp>
// raylib
#include <raylib.h>

using std::cout;
using std::cin;
using std::ostringstream;
using std::stoi;
using std::endl;

// calcular determinante
string VariablesConfig::nameMatrizBuscar = "";
string VariablesConfig::nameMatriz = "";
bool VariablesConfig::mouseOverDeter = false;
bool VariablesConfig::CancelDeter = false;
bool VariablesConfig::clickDeter = false;

void OperacMatrices::deterMatriz(void){
    int x = 440;
    int y = 100;
    Rectangle botonesDeterMatriz[2] ={{(float)(x+220), (float)(y+80), 80.0f, 20.0f}, {(float)(x+310), (float)(y+80), 90.0f, 20.0f}};

    DrawText("CALCULAR DETERMINANTE", x, y, 30, DARKBLUE);
    DrawText("    DE UNA MATRIZ    ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz:", x, y+80, 20, BLACK);
    input_box(botonesDeterMatriz[0], SKYBLUE, VariablesConfig::nameMatrizBuscar);

    // boton buscar
    DrawRectangleRec(botonesDeterMatriz[1], (VariablesConfig::mouseOverDeter) ? LIME : BLUE);
    DrawText("Buscar", botonesDeterMatriz[1].x+10, botonesDeterMatriz[1].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesDeterMatriz[1])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombre - " << VariablesConfig::nameMatrizBuscar << endl;
            VariablesConfig::nameMatriz = VariablesConfig::nameMatrizBuscar;
            VariablesConfig::clickDeter = true;
            VariablesConfig::nameMatrizBuscar = "";
        }
        VariablesConfig::mouseOverDeter = true;
    } else {
        VariablesConfig::mouseOverDeter = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickDeter){
        if(this->buscarMatriz(VariablesConfig::nameMatriz)){
            ostringstream message; // almacena todos los caracteres para imprimir luego
            if(!this->matrices[VariablesConfig::nameMatriz]->getIsCuadrado()){
                message << "La matriz '" << VariablesConfig::nameMatriz << "' no tiene determinante, no es cuadrada... ";
                DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
                return;
            }
            message << "La determinante de la matriz ''" << VariablesConfig::nameMatriz << "'' es: " << this->matrices[VariablesConfig::nameMatriz]->calcularDeterminante();
            DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
            DrawText("Y sus valores son: ", x-60, 260, 20, DARKBLUE);
            this->matrices[VariablesConfig::nameMatriz]->imprimirMatriz();
        }else {
            DrawText("La matriz indicada no existe", x-60, 260, 20, DARKBLUE);
        }
    }
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

// calcular suma de matrices
string VariablesConfig::nameSumaBuscar01 = "";
string VariablesConfig::nameSumaBuscar02 = "";
string VariablesConfig::nameSuma01 = "";
string VariablesConfig::nameSuma02 = "";
bool VariablesConfig::mouseOverSuma = false;
bool VariablesConfig::cancelSuma = false;
bool VariablesConfig::clickSuma = false;

void OperacMatrices::sumarMatrices(void){
    //DrawText("Test: sumar matrices:", 340, 30, 20, DARKBLUE);
    int x = 440;
    int y = 100;
    Rectangle botonesSumarMatriz[3] ={{(float)(x+240), (float)(y+80), 80.0f, 20.0f}, {(float)(x+240), (float)(y+110), 80.0f, 20.0f},
                                        {(float)(x+330), (float)(y+90), 90.0f, 20.0f}};

    DrawText("CALCULAR DETERMINANTE", x, y, 30, DARKBLUE);
    DrawText("    DE UNA MATRIZ    ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz 01:", x, y+80, 20, BLACK);
    DrawText("Nombre de la matriz 02:", x, y+110, 20, BLACK);
    input_box(botonesSumarMatriz[0], SKYBLUE, VariablesConfig::nameSumaBuscar01);
    input_box(botonesSumarMatriz[1], SKYBLUE, VariablesConfig::nameSumaBuscar02);

    // boton buscar
    DrawRectangleRec(botonesSumarMatriz[2], (VariablesConfig::mouseOverSuma) ? LIME : BLUE);
    DrawText("Buscar", botonesSumarMatriz[2].x+10, botonesSumarMatriz[2].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesSumarMatriz[2])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombres: " << VariablesConfig::nameSumaBuscar01 << "-"  << VariablesConfig::nameSumaBuscar02 << endl;
            VariablesConfig::nameSuma01 = VariablesConfig::nameSumaBuscar01;
            VariablesConfig::nameSuma02 = VariablesConfig::nameSumaBuscar02;
            VariablesConfig::clickSuma = true;
            VariablesConfig::nameSumaBuscar01 = "";
            VariablesConfig::nameSumaBuscar02 = "";
        }
        VariablesConfig::mouseOverSuma = true;
    } else {
        VariablesConfig::mouseOverSuma = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickSuma){
        ostringstream message; // almacena todos los caracteres para imprimir luego
        if(!this->buscarMatriz(VariablesConfig::nameSuma01)){
            message << "La matriz ''" << VariablesConfig::nameSuma01 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(!this->buscarMatriz(VariablesConfig::nameSuma02)){
            message << "La matriz ''" << VariablesConfig::nameSuma02 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(this->noCumpleReqSumRest(VariablesConfig::nameSuma01, VariablesConfig::nameSuma02))
            return;


        Matriz temp = *(*(this->matrices[VariablesConfig::nameSuma01]) + *(this->matrices[VariablesConfig::nameSuma02]));
        message << "\nLa suma de las matrices ( " << VariablesConfig::nameSuma01 << " + " << VariablesConfig::nameSuma01<< " ) es:";
        //cout << message.str() << endl;
        DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
        temp.imprimirMatriz();
    }
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
    VariablesConfig::openMenu = true;
}

void OperacMatrices::agregarMatriz(int filas, int columnas, string&nombre){
    Matriz* matriz;                 //crear matriz cuadrada         // crear matriz no cuadrada
    (filas == columnas) ? matriz = new Matriz(filas) : matriz = new Matriz(filas, columnas);
    matriz->rellenarMatriz();
    cout << "\nLa matriz ingresada tiene los valores es:" << endl;
    matriz->imprimirMatriz();
    matrices[nombre] = matriz;
}

bool OperacMatrices::buscarMatriz(string& nombre){
    if (this->matrices.count(nombre)) // count() -> verifica si existe un item con X nombre
        return true;
    else
        return false;
}

bool OperacMatrices::noCumpleReqSumRest(string& Matriz01, string& Matriz02){
    if((this->matrices[Matriz01]->getIsCuadrado() && this->matrices[Matriz02]->getIsCuadrado())){
        if(this->matrices[Matriz01]->getOrden() != this->matrices[Matriz02]->getOrden()){
            DrawText("No se puede operar, las matrices son de dimensiones distintas...", 380, 260, 20, DARKBLUE);
            cout << "No se puede operar, las matrices son de dimensiones distintas..." << endl;
            return true; // no cumple todos los requisitos de matrices NxN
        }
    } else {
        if(this->matrices[Matriz01]->getFilas() != this->matrices[Matriz02]->getFilas() ||
            this->matrices[Matriz01]->getColumnas() != this->matrices[Matriz02]->getColumnas()){
            DrawText("No se puede operar, las matrices no coinciden en sus dimensiones...", 380, 260, 20, DARKBLUE);
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

// crear matriz
string VariablesConfig::name = "";
string VariablesConfig::filas = "";
string VariablesConfig::columnas = "";
bool VariablesConfig::clicAgregar = false;
string VariablesConfig::impriMatriz = "";

void OperacMatrices::crearMatriz(){ // se omite la variable opcion en la compilacion del programa
    int x = 440;
    int y = 30;
    Rectangle botonesCrearMatriz[4] ={
        {(float)(x+250), (float)(y+80), 80.0f, 20.0f}, {(float)(x+250), (float)(y+110), 80.0f, 20.0f},
        {(float)(x+250), (float)(y+140), 80.0f, 20.0f}, {(float)(x+340), (float)(y+100), 45.0f, 40.0f}
        };

    DrawText("INGRESE  LOS DATOS", x, y, 30, DARKBLUE);
    DrawText("DE LA NUEVA MATRIZ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz:", x, y+80, 20, BLACK);
    DrawText("Tamaño de filas:", x, y+110, 20, BLACK);
    DrawText("Tamaño de columnas:", x, y+140, 20, BLACK);
    input_box(botonesCrearMatriz[0], SKYBLUE, VariablesConfig::name);
    input_box(botonesCrearMatriz[1], SKYBLUE, VariablesConfig::filas);
    input_box(botonesCrearMatriz[2], SKYBLUE, VariablesConfig::columnas);

    // boton agregar
    DrawRectangleRec(botonesCrearMatriz[3], (VariablesConfig::clicAgregar) ? LIME : BLUE);
    DrawText("+", botonesCrearMatriz[3].x+10, botonesCrearMatriz[3].y, 45, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesCrearMatriz[3])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            this->agregarMatriz(stoi(VariablesConfig::filas), stoi(VariablesConfig::columnas), VariablesConfig::name) ;
            cout << "clic agregar-> nombre: " << VariablesConfig::name << " : " << stoi(VariablesConfig::filas) <<"*" << stoi(VariablesConfig::columnas) << endl;
            VariablesConfig::impriMatriz = VariablesConfig::name;
            VariablesConfig::name = "";
            VariablesConfig::filas = "";
            VariablesConfig::columnas = "";
        }
        VariablesConfig::clicAgregar = true;
    } else
        VariablesConfig::clicAgregar = false;

    // imprimir matriz si existe
    if(VariablesConfig::impriMatriz.size() > 0){
        string matrizTemp = "La matriz ''" + VariablesConfig::impriMatriz + "'' los valores";
        DrawText(matrizTemp.c_str(), x, 260, 20, DARKBLUE);
        this->matrices[VariablesConfig::impriMatriz]->imprimirMatriz();
    }
}

void OperacMatrices::mostrarMenuOpMatrices(){
    VariablesConfig::openMenu = false;
    VariablesConfig::clickMenu = -1;
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

void OperacMatrices::input_box(Rectangle& boton, Color color, string& variable){
    DrawRectangleRec(boton, color);
    DrawText(variable.c_str(), (int)boton.x + 8, (int)boton.y, 20, BLACK);
    if (CheckCollisionPointRec(GetMousePosition(), boton)){
        int key = GetCharPressed();
        while (key > 0)
        {
            variable += key;
            cout << "Valor ingresado: " << variable << endl;

            key = GetCharPressed();  // Check next character in the queue
        }
        DrawText("_", (int)boton.x + 8 + MeasureText(variable.c_str(), 20), (int)boton.y, 20, DARKBROWN);
    }
}