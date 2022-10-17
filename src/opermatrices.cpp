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

// calcular inversa
string VariablesConfig::nameInverBuscar = "";
string VariablesConfig::nameInver = "";
bool VariablesConfig::mouseOverInver = false;
bool VariablesConfig::clickInver = false;

void OperacMatrices::inversaMatriz(void){
    int x = 440;
    int y = 100;
    Rectangle botonesInverMatriz[2] ={{(float)(x+220), (float)(y+80), 80.0f, 20.0f}, {(float)(x+310), (float)(y+80), 90.0f, 20.0f}};

    DrawText("CALCULAR INVERSA", x, y, 30, DARKBLUE);
    DrawText("  DE UNA MATRIZ ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz:", x, y+80, 20, BLACK);
    input_box(botonesInverMatriz[0], SKYBLUE, VariablesConfig::nameInverBuscar);

    // boton buscar
    DrawRectangleRec(botonesInverMatriz[1], (VariablesConfig::mouseOverInver) ? LIME : BLUE);
    DrawText("Buscar", botonesInverMatriz[1].x+10, botonesInverMatriz[1].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesInverMatriz[1])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombre - " << VariablesConfig::nameInverBuscar << endl;
            VariablesConfig::nameInver = VariablesConfig::nameInverBuscar;
            VariablesConfig::clickInver = true;
            VariablesConfig::nameInverBuscar = "";
        }
        VariablesConfig::mouseOverInver = true;
    } else {
        VariablesConfig::mouseOverInver = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickInver){
        if(this->buscarMatriz(VariablesConfig::nameInver)){
            ostringstream message; // almacena todos los caracteres para imprimir luego
            if(!this->matrices[VariablesConfig::nameInver]->getIsCuadrado()){
                message << "La matriz '" << VariablesConfig::nameInver << "' no tiene Inversa, no es cuadrada... ";
                DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
                return;
            }
            double det = this->matrices[VariablesConfig::nameInver]->calcularDeterminante();
            if(det == 0){
                message << "La determinante es CERO, la matriz no tiene inversa...";
                DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
                return;
            }

            message << "La determinante de la matriz ''" << VariablesConfig::nameMatriz << "'' es: " << det;
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            message.str("");
            Matriz matriz = *(this->matrices[VariablesConfig::nameInver]->calcularInversa(det));
            message << "La inversa de la matriz '" << VariablesConfig::nameInver << "' es :";
            DrawText((message.str()).c_str(), x-60, 290, 20, DARKBLUE);
            matriz.imprimirMatriz(7, 440, 330);
        }else {
            DrawText("La matriz indicada no existe", x-60, 260, 20, DARKBLUE);
        }
    }
}

// calcular Multi de matrices
string VariablesConfig::nameMultiBuscar01 = "";
string VariablesConfig::nameMultiBuscar02 = "";
string VariablesConfig::nameMulti01 = "";
string VariablesConfig::nameMulti02 = "";
bool VariablesConfig::mouseOverMulti = false;
bool VariablesConfig::cancelMulti = false;
bool VariablesConfig::clickMulti = false;

void OperacMatrices::multiMatrices(void){
    int x = 440;
    int y = 100;
    Rectangle botonesMultirMatriz[3] ={{(float)(x+240), (float)(y+80), 80.0f, 20.0f}, {(float)(x+240), (float)(y+110), 80.0f, 20.0f},
                                        {(float)(x+330), (float)(y+90), 90.0f, 20.0f}};

    DrawText("CALCULAR MULTIPLICACION", x, y, 30, DARKBLUE);
    DrawText("          DE MATRICES ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz 01:", x, y+80, 20, BLACK);
    DrawText("Nombre de la matriz 02:", x, y+110, 20, BLACK);
    input_box(botonesMultirMatriz[0], SKYBLUE, VariablesConfig::nameMultiBuscar01);
    input_box(botonesMultirMatriz[1], SKYBLUE, VariablesConfig::nameMultiBuscar02);

    // boton buscar
    DrawRectangleRec(botonesMultirMatriz[2], (VariablesConfig::mouseOverMulti) ? LIME : BLUE);
    DrawText("Buscar", botonesMultirMatriz[2].x+10, botonesMultirMatriz[2].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesMultirMatriz[2])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombres: " << VariablesConfig::nameMultiBuscar01 << "*"  << VariablesConfig::nameMultiBuscar02 << endl;
            VariablesConfig::nameMulti01 = VariablesConfig::nameMultiBuscar01;
            VariablesConfig::nameMulti02 = VariablesConfig::nameMultiBuscar02;
            VariablesConfig::clickMulti = true;
            VariablesConfig::nameMultiBuscar01 = "";
            VariablesConfig::nameMultiBuscar02 = "";
        }
        VariablesConfig::mouseOverMulti = true;
    } else {
        VariablesConfig::mouseOverMulti = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickMulti){
        ostringstream message; // almacena todos los caracteres para imprimir luego
        if(!this->buscarMatriz(VariablesConfig::nameMulti01)){
            message << "La matriz ''" << VariablesConfig::nameMulti01 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(!this->buscarMatriz(VariablesConfig::nameMulti02)){
            message << "La matriz ''" << VariablesConfig::nameMulti02 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(this->noCumpleReqMulti(VariablesConfig::nameMulti01, VariablesConfig::nameMulti02))
            return;

        Matriz temp = *(*(this->matrices[VariablesConfig::nameMulti01]) * *(this->matrices[VariablesConfig::nameMulti02]));
        message << "\nLa Multiplicación de las matrices ( " << VariablesConfig::nameMulti01 << " * " << VariablesConfig::nameMulti02<< " ) es:";
        DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
        temp.imprimirMatriz();
    }
}

// calcular Multi de matrices
string VariablesConfig::nameEscalBuscar = "";
string VariablesConfig::nameEscalNum = "";
string VariablesConfig::nameEscal = "";
string VariablesConfig::Escalnum = "";
bool VariablesConfig::mouseOverEscal = false;
bool VariablesConfig::clickEscal = false;

void OperacMatrices::multiEscalarMatriz(void){
    int x = 440;
    int y = 100;
    Rectangle botonesMEscarMatriz[3] ={{(float)(x+240), (float)(y+80), 80.0f, 20.0f}, {(float)(x+240), (float)(y+110), 80.0f, 20.0f},
                                        {(float)(x+330), (float)(y+90), 90.0f, 20.0f}};

    DrawText("CALCULAR MULTIPLICACION", x, y, 30, DARKBLUE);
    DrawText(" DE MATRIZ POR ESCALAR", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz :", x, y+80, 20, BLACK);
    DrawText("Ingresar escalar(val):", x, y+110, 20, BLACK);
    input_box(botonesMEscarMatriz[0], SKYBLUE, VariablesConfig::nameEscalBuscar);
    input_box(botonesMEscarMatriz[1], SKYBLUE, VariablesConfig::nameEscalNum);

    // boton buscar
    DrawRectangleRec(botonesMEscarMatriz[2], (VariablesConfig::mouseOverEscal) ? LIME : BLUE);
    DrawText("Buscar", botonesMEscarMatriz[2].x+10, botonesMEscarMatriz[2].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesMEscarMatriz[2])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombres: " << VariablesConfig::nameEscalBuscar << "*"  << VariablesConfig::nameEscalNum << endl;
            VariablesConfig::nameEscal = VariablesConfig::nameEscalBuscar;
            VariablesConfig::Escalnum = VariablesConfig::nameEscalNum;
            VariablesConfig::clickEscal = true;
            VariablesConfig::nameEscalBuscar = "";
            VariablesConfig::nameEscalNum = "";
        }
        VariablesConfig::mouseOverEscal = true;
    } else {
        VariablesConfig::mouseOverEscal = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickEscal){
        ostringstream message; // almacena todos los caracteres para imprimir luego
        if(!this->buscarMatriz(VariablesConfig::nameEscal)){
            message << "La matriz ''" << VariablesConfig::nameEscal << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        Matriz temp = *(*(this->matrices[VariablesConfig::nameEscal]) * atof(VariablesConfig::Escalnum.c_str()));
        message << "\nLa multiplicación de la matriz ( " << VariablesConfig::nameEscal << " * " << VariablesConfig::Escalnum << " ) es:";
        DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
        temp.imprimirMatriz(7, 440, 300);
    }
}

// calcular Resta de matrices
string VariablesConfig::nameRestaBuscar01 = "";
string VariablesConfig::nameRestaBuscar02 = "";
string VariablesConfig::nameResta01 = "";
string VariablesConfig::nameResta02 = "";
bool VariablesConfig::mouseOverResta = false;
bool VariablesConfig::cancelResta = false;
bool VariablesConfig::clickResta = false;

void OperacMatrices::restarMatrices(void){
    int x = 440;
    int y = 100;
    Rectangle botonesRestarMatriz[3] ={{(float)(x+240), (float)(y+80), 80.0f, 20.0f}, {(float)(x+240), (float)(y+110), 80.0f, 20.0f},
                                        {(float)(x+330), (float)(y+90), 90.0f, 20.0f}};

    DrawText("CALCULAR RESTA", x, y, 30, DARKBLUE);
    DrawText("  DE MATRICES ", x, y+30, 30, DARKBLUE);
    DrawText("Nombre de la matriz 01:", x, y+80, 20, BLACK);
    DrawText("Nombre de la matriz 02:", x, y+110, 20, BLACK);
    input_box(botonesRestarMatriz[0], SKYBLUE, VariablesConfig::nameRestaBuscar01);
    input_box(botonesRestarMatriz[1], SKYBLUE, VariablesConfig::nameRestaBuscar02);

    // boton buscar
    DrawRectangleRec(botonesRestarMatriz[2], (VariablesConfig::mouseOverResta) ? LIME : BLUE);
    DrawText("Buscar", botonesRestarMatriz[2].x+10, botonesRestarMatriz[2].y, 20, DARKBLUE);
    if (CheckCollisionPointRec(GetMousePosition(), botonesRestarMatriz[2])){
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            cout << "clic agregar-> nombres: " << VariablesConfig::nameRestaBuscar01 << "-"  << VariablesConfig::nameRestaBuscar02 << endl;
            VariablesConfig::nameResta01 = VariablesConfig::nameRestaBuscar01;
            VariablesConfig::nameResta02 = VariablesConfig::nameRestaBuscar02;
            VariablesConfig::clickResta = true;
            VariablesConfig::nameRestaBuscar01 = "";
            VariablesConfig::nameRestaBuscar02 = "";
        }
        VariablesConfig::mouseOverResta = true;
    } else {
        VariablesConfig::mouseOverResta = false;
    }
    // fin boton buscar

    if(VariablesConfig::clickResta){
        ostringstream message; // almacena todos los caracteres para imprimir luego
        if(!this->buscarMatriz(VariablesConfig::nameResta01)){
            message << "La matriz ''" << VariablesConfig::nameResta01 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(!this->buscarMatriz(VariablesConfig::nameResta02)){
            message << "La matriz ''" << VariablesConfig::nameResta02 << "'' no existe";
            DrawText((message.str()).c_str(), x-60, 260, 20, DARKBLUE);
            return;
        }

        if(this->noCumpleReqSumRest(VariablesConfig::nameResta01, VariablesConfig::nameResta02))
            return;

        Matriz temp = *(*(this->matrices[VariablesConfig::nameResta01]) - *(this->matrices[VariablesConfig::nameResta02]));
        message << "\nLa Resta de las matrices ( " << VariablesConfig::nameResta01 << " - " << VariablesConfig::nameResta02<< " ) es:";
        DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
        temp.imprimirMatriz();
    }
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
    int x = 440;
    int y = 100;
    Rectangle botonesSumarMatriz[3] ={{(float)(x+240), (float)(y+80), 80.0f, 20.0f}, {(float)(x+240), (float)(y+110), 80.0f, 20.0f},
                                        {(float)(x+330), (float)(y+90), 90.0f, 20.0f}};

    DrawText("CALCULAR SUMA", x, y, 30, DARKBLUE);
    DrawText(" DE MATRICES ", x, y+30, 30, DARKBLUE);
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
        message << "\nLa suma de las matrices ( " << VariablesConfig::nameSuma01 << " + " << VariablesConfig::nameSuma02<< " ) es:";
        DrawText((message.str()).c_str(), x-60, 230, 20, DARKBLUE);
        temp.imprimirMatriz();
    }
}

void OperacMatrices::mostrarMenuPrincipal(void){
    VariablesConfig::openMenu = true;
}

void OperacMatrices::agregarMatriz(int filas, int columnas, string&nombre){
    Matriz* matriz;                 //crear matriz cuadrada         // crear matriz no cuadrada
    (filas == columnas) ? matriz = new Matriz(filas) : matriz = new Matriz(filas, columnas);
    matriz->rellenarMatriz();
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
            DrawText("No se puede operar!!!", 380, 260, 20, DARKBLUE);
            DrawText("Las matrices son de orden distintas...", 380, 290, 20, DARKBLUE);
            return true; // no cumple todos los requisitos de matrices NxN
        }
    } else {
        if(this->matrices[Matriz01]->getFilas() != this->matrices[Matriz02]->getFilas() ||
            this->matrices[Matriz01]->getColumnas() != this->matrices[Matriz02]->getColumnas()){
            DrawText("No se puede operar!!!", 380, 260, 20, DARKBLUE);
            DrawText("Las matrices no coinciden en sus dimensiones...", 380, 290, 20, DARKBLUE);
            return true; // nocumple todos los requisitos de matrices NxM
        }
    }
    return false; // cumple todos los requisitos
}

bool OperacMatrices::noCumpleReqMulti(string& Matriz01, string& Matriz02){
    if((this->matrices[Matriz01]->getIsCuadrado() && this->matrices[Matriz02]->getIsCuadrado())){
        if(this->matrices[Matriz01]->getOrden() != this->matrices[Matriz02]->getOrden()){
            DrawText("No se puede operar!!!", 380, 260, 20, DARKBLUE);
            DrawText("Las matrices son de orden distintas...", 380, 290, 20, DARKBLUE);
            return true; // no cumple todos los requisitos de matrices NxN
        }
    } else {
        if(this->matrices[Matriz01]->getColumnas() != this->matrices[Matriz02]->getFilas()){
            ostringstream message; // almacena todos los caracteres para imprimir luego
            DrawText("No se puede operar!!!", 380, 260, 20, DARKBLUE);
            message << "Las columnas de la matriz'" << Matriz01 << "'";
            DrawText(message.str().c_str(), 380, 290, 20, DARKBLUE);
            message.str("");
            message << "y las filas de la matriz '" << Matriz02 << "' no coinciden ..." << endl;
            DrawText(message.str().c_str(), 380, 320, 20, DARKBLUE);
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