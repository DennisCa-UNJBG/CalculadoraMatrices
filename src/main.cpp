#include <vector>
#include <map>
#include <iostream>
#include <sstream> // convertir string a int
// raylib
#include <raylib.h>
// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>

using namespace std;

/* varibles globales de configuracion */
bool ejecutando = true; // variable global que mantiene vivo el programa
bool OperacMatrices::openMenu = true; // true -> menu 01 , false -> menu 02

/* opciones del menu principal */
void menuPrincipal(vector<Rectangle>& botonesMenuPrincipal, int& mouseHoverRec);
void menuOperacMatrices(vector<Rectangle>& botonesMenuOperaciones, int& mouseHoverRec);
void opcionSelecMenuPrinc(OperacMatrices* misMatrices, int opcion);
void crearMatriz(OperacMatrices* misMatrices, int opcion);
void abrirMenuOpMatrices(OperacMatrices* misMatrices, int opcion);
void verMatrices(OperacMatrices* misMatrices, int opcion);
void salirPrograma(OperacMatrices* misMatrices, int opcion);

/* opciones del menu secundario(operaciones) */
void opcionSelecMenuOper(OperacMatrices* misMatrices, int opcion);
/* raylib */
void selecMouse(vector<Rectangle>& botonesMenuPrincipal, int& mouseHoverRec);

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
    { "Calcular la inversa",            &OperacMatrices::inversaMatriz }, // 1 matriz X
    { "Calcular la determinante",       &OperacMatrices::deterMatriz }, // 1 matriz X
    { "Sumar matrices",                 &OperacMatrices::sumarMatrices }, // 2 matrices
    { "Restar matrices",                &OperacMatrices::restarMatrices }, // 2 matrices
    { "Multiplicar matrices",           &OperacMatrices::multiMatrices }, // 2 matrices
    { "Multiplicar por escalar",        &OperacMatrices::multiEscalarMatriz }, // 1 matriz X y 1 entero
    { "Menu anterior",                  &OperacMatrices::salirMenuOper } // cambiar variable global
}; // empleamos los punteros a metodos de clase

int main(/*int argc, char *argv[]*/){ /* programa principal */
    // Initialization
    //--------------------------------------------------------------------------------------
    const int anchoVentana = 1000;
    const int altooVentana = 600;
    int mouseHoverRec = -1;
                                            // titulo de la ventana
    InitWindow(anchoVentana, altooVentana, "RAYLIB [core] - Calculadora de Matrices");

    SetTargetFPS(60);               // limite en los FPS por segundo  ¡NO BORRAR!
    //--------------------------------------------------------------------------------------

    // sector de operaciones
    Rectangle cuadradoOper = Rectangle{0.0f, 0.0f, 320.0f, 600.0f};
    // crear botones menu principal
    vector<Rectangle> botonesMenuPrincipal;
    for (size_t i = 0; i < MenuPrincipal.size(); i++)
        botonesMenuPrincipal.push_back({ 20.0f, (float)(80 + 60*i), 280.0f, 40.0f });

    // crear botones menu de operaciones
    vector<Rectangle> botonesMenuOperaciones;
    for (size_t i = 0; i < MenuOperaciones.size(); i++)
        botonesMenuOperaciones.push_back({ 20.0f, (float)(80 + 60*i), 280.0f, 40.0f });

    // Main window loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Actualizat variables aquí
        //----------------------------------------------------------------------------------
        selecMouse(botonesMenuPrincipal, mouseHoverRec);

        // Draw/Dibujado de elementos en la ventana
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY); // color de fonde de la ventana

        DrawRectangleRec(cuadradoOper, GRAY);
        DrawText("MENU:", 100, 30, 40, DARKBLUE);
        menuPrincipal(botonesMenuPrincipal, mouseHoverRec);
        //menuOperacMatrices(botonesMenuOperaciones, mouseHoverRec);

        DrawText("Ejecutando una ventana de Raylib", 340, 100, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    /*
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
    */
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
    //menuOperacMatrices();
}

void crearMatriz(OperacMatrices* misMatrices, int /*opcion*/){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int filas, columnas;
    cout << "Ingrese un nombre(sin espacios) para la matriz:" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;

    misMatrices->agregarMatriz(filas, columnas, nombre) ;
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

void menuOperacMatrices(vector<Rectangle>& botonesMenuOperaciones, int& mouseHoverRec){
    for (size_t i = 0; i < MenuOperaciones.size(); i++){
        DrawRectangleRec(botonesMenuOperaciones[i], ((int)i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)botonesMenuOperaciones[i].x, (int)botonesMenuOperaciones[i].y, (int)botonesMenuOperaciones[i].width, (int)botonesMenuOperaciones[i].height, BLUE);
        DrawText( MenuOperaciones[i].opciones.c_str(), (int)( botonesMenuOperaciones[i].x + botonesMenuOperaciones[i].width/2 - MeasureText(MenuOperaciones[i].opciones.c_str(), 20)/2), (int) botonesMenuOperaciones[i].y + 11, 20, DARKBLUE);
    }
}

void menuPrincipal(vector<Rectangle>& botonesMenuPrincipal, int& mouseHoverRec){
    for (size_t i = 0; i < MenuPrincipal.size(); i++){
        DrawRectangleRec(botonesMenuPrincipal[i], ((int)i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)botonesMenuPrincipal[i].x, (int)botonesMenuPrincipal[i].y, (int)botonesMenuPrincipal[i].width, (int)botonesMenuPrincipal[i].height, BLUE);
        DrawText( MenuPrincipal[i].opciones.c_str(), (int)( botonesMenuPrincipal[i].x + botonesMenuPrincipal[i].width/2 - MeasureText(MenuPrincipal[i].opciones.c_str(), 20)/2), (int) botonesMenuPrincipal[i].y + 11, 20, DARKBLUE);
    }
}

void selecMouse(vector<Rectangle>& botonesMenuPrincipal, int& mouseHoverRec){
        for (size_t i = 0; i < MenuPrincipal.size(); i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), botonesMenuPrincipal[i]))
            {
                mouseHoverRec = i;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    /*
                    currentProcess = i;
                    textureReload = true;
                    */
                    cout << "Seleciono menu: " << i << endl;
                }
                break;
            }
            else mouseHoverRec = -1;
        }
}
