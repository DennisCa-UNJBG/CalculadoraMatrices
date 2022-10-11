#include <vector>
#include <map>
#include <iostream>
#include <sstream> // convertir string a int
// raylib
#include <raylib.h>
// incluir librerias custom
#include <matriz.hpp>
#include <opermatrices.hpp>
#include <config.hpp>

using namespace std;

/* varibles globales de configuracion */
bool OperacMatrices::openMenu = true; // true -> menu 01 , false -> menu 02
int VariablesConfig::clickOpcion = -1;

struct OperMenu{ /* estructura para controlar las opciones del menu principal */
    string opciones;
    void (OperacMatrices::*method) (void);
};

vector<OperMenu> MenuPrincipal = { // opciones del menu principal
    { "Crear nueva matriz",          &OperacMatrices::crearMatriz },
    { "Operaciones con matrices",    &OperacMatrices::mostrarMenuOpMatrices },
    { "Ver matrices existentes",     &OperacMatrices::verMatrices },
    { "Salir",                       &OperacMatrices::salirPrograma }
}; // empleamos los punteros a metodos de clase

vector <OperMenu> MenuOperaciones = { // opciones del menu de operaciones
    { "Calcular la inversa",            &OperacMatrices::inversaMatriz }, // 1 matriz X
    { "Calcular la determinante",       &OperacMatrices::deterMatriz }, // 1 matriz X
    { "Sumar matrices",                 &OperacMatrices::sumarMatrices }, // 2 matrices
    { "Restar matrices",                &OperacMatrices::restarMatrices }, // 2 matrices
    { "Multiplicar matrices",           &OperacMatrices::multiMatrices }, // 2 matrices
    { "Multiplicar por escalar",        &OperacMatrices::multiEscalarMatriz }, // 1 matriz X y 1 entero
    { "Menu anterior",                  &OperacMatrices::mostrarMenuPrincipal } // cambiar variable global
}; // empleamos los punteros a metodos de clase

void selecMouse(vector<Rectangle>& botones, vector<OperMenu>& menu, int& mouseHoverRec);
void dibujarMenus(vector<Rectangle>& botonesMenuPrincipal, vector<OperMenu>& menu, int& mouseHoverRec);
void dibujarEventos(OperacMatrices* misMatrices, vector<OperMenu>& menu);

int main(/*int argc, char *argv[]*/){ /* programa principal */
    // Initialization
    //--------------------------------------------------------------------------------------
    const int anchoVentana = 1000;
    const int altooVentana = 600;
    int mouseHoverRec = -1;
                                            // titulo de la ventana
    InitWindow(anchoVentana, altooVentana, "RAYLIB [core] - Calculadora de Matrices");

    SetTargetFPS(60);               // limite en los FPS por segundo  ¡NO BORRAR!

    // dibujar sector de operaciones
    Rectangle cuadradoOper = Rectangle{0.0f, 0.0f, 320.0f, 600.0f};

    // crear botones menu principal
    vector<Rectangle> botonesMenuPrincipal;
    for (size_t i = 0; i < MenuPrincipal.size(); i++)
        botonesMenuPrincipal.push_back({ 20.0f, (float)(80 + 60*i), 280.0f, 40.0f });

    // crear botones menu de operaciones
    vector<Rectangle> botonesMenuOperaciones;
    for (size_t i = 0; i < MenuOperaciones.size(); i++)
        botonesMenuOperaciones.push_back({ 20.0f, (float)(80 + 60*i), 280.0f, 40.0f });

    OperacMatrices misMatrices = OperacMatrices();
    //--------------------------------------------------------------------------------------
    // Main window loop
    while (!WindowShouldClose()){
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Actualizar variables aquí
        OperacMatrices::openMenu ?
            selecMouse(botonesMenuPrincipal, MenuPrincipal, mouseHoverRec)
            :
            selecMouse(botonesMenuOperaciones, MenuOperaciones, mouseHoverRec);
        //----------------------------------------------------------------------------------
        // Draw/Dibujado de elementos en la ventana
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY); // color de fonde de la ventana

        DrawRectangleRec(cuadradoOper, GRAY);
        DrawText("MENU:", 100, 30, 40, DARKBLUE);
        OperacMatrices::openMenu ?
            dibujarMenus(botonesMenuPrincipal, MenuPrincipal, mouseHoverRec)
            :
            dibujarMenus(botonesMenuOperaciones, MenuOperaciones, mouseHoverRec);

        OperacMatrices::openMenu ?
            dibujarEventos(&misMatrices, MenuPrincipal)
            :
            dibujarEventos(&misMatrices, MenuOperaciones);

        DrawText("Ejecutando una ventana de Raylib", 340, 100, 20, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

void dibujarMenus(vector<Rectangle>& botones, vector<OperMenu>& menu, int& mouseHoverRec){
    for (size_t i = 0; i < menu.size(); i++){
        DrawRectangleRec(botones[i], ((int)i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleLines((int)botones[i].x, (int)botones[i].y, (int)botones[i].width, (int)botones[i].height, BLUE);
        DrawText( menu[i].opciones.c_str(), (int)( botones[i].x + botones[i].width/2 - MeasureText(menu[i].opciones.c_str(), 20)/2), (int) botones[i].y + 11, 20, DARKBLUE);
    }
}

void dibujarEventos(OperacMatrices* misMatrices, vector<OperMenu>& menu){
    if(VariablesConfig::clickOpcion != -1 && (size_t)VariablesConfig::clickOpcion < menu.size()){
        (misMatrices->*menu[VariablesConfig::clickOpcion].method)();
        //DrawText("test 02:", 340, 120, 40, DARKBLUE);
    }
}

void selecMouse(vector<Rectangle>& botones, vector<OperMenu>& menu, int& mouseHoverRec){
        for (size_t i = 0; i < menu.size(); i++){
            if (CheckCollisionPointRec(GetMousePosition(), botones[i])){
                mouseHoverRec = i;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    cout << "Seleciono en menu el index: " << mouseHoverRec << endl;
                    VariablesConfig::clickOpcion = i;
                }
                break;
            }
            else mouseHoverRec = -1;
        }
}
