#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <random> // generar numeros aleatorios
#include <iomanip> // crear una tabla
#include <sstream> // convertir string a int

using namespace std;
/* varibles globales de configuracion */
const int MIN = -10; // minimo valor aleatorio
const int MAX = 10; // maximo valor aleatorio
const int TABLA = 4; // espacios para ordenar valores en la tabla
bool ejecutando = true; // variable global que mantiene vivo el programa
bool opMenu = true; // true -> menu 01 , false -> menu 02

class Matriz{ /* clase base de una matriz */
public:
    Matriz(int orden);
    ~Matriz();
    void imprimirMatriz(int espacios = TABLA);
    void rellenarMatriz();
    double calcularDeterminante();
    Matriz* calcularInversa(double& deter);
    inline int getOrden() { return orden; }
    inline double** getInicio() { return M; }
private:
    double** M;
    int orden;
    double determinante(double** matriz, int orden);
    double cofactor(double** matriz, int orden, int fila, int columna);
    Matriz* traspuesta();
    // sobrecarga de operadores
    friend Matriz* operator+(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator-(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator*(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator*(Matriz& matriz, double numero);
protected:
};

class OperacMatrices{ /* clase global de operaciones */
public:
    map<string, Matriz*>matrices; // estructura clave/valor (contiene todas las matrices)
    void agregarMatriz(int& orden, string&nombre);
    void buscarMatriz(bool& cancelar, int& idMatriz, string& nombre);
    //operaciones disponibles
    void deterMatriz(OperacMatrices* misMatrices);
    void inversaMatriz(OperacMatrices* misMatrices);
    void sumarMatrices(OperacMatrices* misMatrices);
    void restarMatrices(OperacMatrices* misMatrices);
    void multiMatrices(OperacMatrices* misMatrices );
    void multiEscalarMatriz(OperacMatrices* misMatrices);
    void salirMenuOper(OperacMatrices* misMatrices);
private:
protected:
};

/* opciones del menu principal */
void menuPrincipal();
void menuOperacMatrices();
void opcionSelecMenuPrinc(OperacMatrices* misMatrices, int opcion);
void crearMatriz(OperacMatrices* misMatrices, int opcion);
void abrirMenuOpMatrices(OperacMatrices* misMatrices, int opcion);
void verMatrices(OperacMatrices* misMatrices, int opcion);
void salirPrograma(OperacMatrices* misMatrices, int opcion);

/* opciones del menu secundario(operaciones) */
void opcionSelecMenuOper(OperacMatrices* misMatrices, int opcion);

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
    void (OperacMatrices::*method) (OperacMatrices* misMatrices);
};

vector <OperMenu02> MenuOperaciones = { // opciones del menu de operaciones
    { "Calcular la inversa de una matriz",       &OperacMatrices::inversaMatriz }, // 1 matriz X
    { "Calcular la determinante de una matriz",  &OperacMatrices::deterMatriz }, // 1 matriz X
    { "Sumar matrices",                          &OperacMatrices::sumarMatrices }, // 2 matrices
    { "Restar matrices",                         &OperacMatrices::restarMatrices }, // 2 matrices
    { "multiplar matrices",                      &OperacMatrices::multiMatrices }, // 2 matrices
    { "multiplar matriz por un escalar",         &OperacMatrices::multiEscalarMatriz }, // 1 matriz X y 1 entero
    { "Regresar al menu Principal",              &OperacMatrices::salirMenuOper } // cambiar variable global
}; // empleamos los punteros a metodos de clase

int main(){ /* programa principal */
    OperacMatrices misMatrices = OperacMatrices();
    while(ejecutando){
        system("cls");

        string sOpcion;
        int iOpcion;
        opMenu ? menuPrincipal() : menuOperacMatrices();

        cout << "\nSelecciona una opcion del menu: ";
        cin.sync(); getline(cin,sOpcion);

        //convertir lo que se ingrese a entero omitiendo letras y signos
        stringstream ss;
        ss << sOpcion;
        ss >> iOpcion;

        opMenu ? opcionSelecMenuPrinc(&misMatrices, iOpcion) : opcionSelecMenuOper(&misMatrices, iOpcion);
    }
    return 0;
}

/* implementación de las funciones relacionadas al menu 02 */
void opcionSelecMenuOper(OperacMatrices* misMatrices, int opcion){
    if((size_t)opcion > MenuOperaciones.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (misMatrices->*MenuOperaciones[opcion-1].method)(misMatrices);

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
    opMenu = false;
    system("cls");
    menuOperacMatrices();
}

void crearMatriz(OperacMatrices* misMatrices, int /*opcion*/){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int orden;
    cout << "Ingrese un nombre(sin espacios) para la matriz:" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "Ingrese dimension de la matriz: " << endl;
    cin >> orden;

    misMatrices->agregarMatriz(orden, nombre);
}

void opcionSelecMenuPrinc(OperacMatrices* misMatrices, int opcion){
    if((size_t)opcion > MenuPrincipal.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        MenuPrincipal[opcion-1].func(misMatrices, 0);

    // no lanzar el pause si se elige el menu 02 por 1º vez
    if(opMenu != false)
        system("pause");
}

void menuOperacMatrices(){
    cout << "\n\tOPERACIONES CON MATRICES\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuOperaciones.size(); i++)
        cout << i+1 << ". " << MenuOperaciones[i].opciones << endl;
}

void menuPrincipal(){
    cout << "\n\tMENU PRINCIPAL\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuPrincipal.size(); i++)
        cout << i+1 << ". " << MenuPrincipal[i].opciones << endl;
}

/* implementación de los metodos de la clase  OperacMatrices */

void OperacMatrices::deterMatriz(OperacMatrices* misMatrices){
    string nombreMatriz;
    bool cancelar = false;
    int i = 0;
    // buscar la matriz que se necesita para la operacion
    misMatrices->buscarMatriz(cancelar, i, nombreMatriz);

    if(!cancelar){
        cout << "La determinante de la matriz " << nombreMatriz << " es: "
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
    opMenu = true;
};

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

/* implementación de los metodos de la clase  Matriz */
Matriz* operator+(Matriz& matriz01, Matriz& matriz02){
    int orden = matriz01.orden;
    Matriz* resultado = new Matriz(orden);
    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] + matriz02.M[i][j];
        }
    }
    return resultado;
}

Matriz* operator-(Matriz& matriz01, Matriz& matriz02){
    int orden = matriz01.orden;
    Matriz* resultado = new Matriz(orden);
    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] - matriz02.M[i][j];
        }
    }
    return resultado;
}

Matriz* operator*(Matriz& matriz01, Matriz& matriz02){
    //fuente: https://www.lawebdelprogramador.com/foros/Dev-C/1371193-MULTIPLICACION-DE-MATRICES.html
    int orden = matriz01.orden;
    int filas = orden, columnas = orden;
    Matriz* resultado = new Matriz(orden);
    // multiplicar matrices usando otra para almacenar datos
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            for(int z = 0; z < columnas; z++){
                resultado->M[i][j] += matriz01.M[i][z] * matriz02.M[z][j];
            }
        }
    }

    return resultado;
}

Matriz* operator*(Matriz& matriz01, double numero){
    int orden = matriz01.orden;
    Matriz* resultado = new Matriz(orden);
    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = matriz01.M[i][j] * numero;
        }
    }
    return resultado;
}

Matriz* Matriz::traspuesta(){
    Matriz* resultado = new Matriz(this->orden);
    for (int i = 0; i < this->orden; i++){
        for (int j = 0; j < this->orden; j++){
            resultado->M[i][j] = this->M[j][i];
        }
    }
    return resultado;
}

Matriz* Matriz::calcularInversa(double& deter){
    Matriz* resultado = new Matriz(this->orden);
    // encontramos la matriz de cofactores
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->M[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->M[i][j] = cofactor(this->M, orden, i, j);
        }
    }
    // hacemos la traspuesta de la matriz
    Matriz* aux = resultado;
    resultado = aux->traspuesta();
    delete aux;
    // aplicamos la multiplicacion por la determinante
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->M[i][j] = resultado->M[i][j] / deter;
            // aplicamos 'trunc' para limitar los decimales
            resultado->M[i][j] = trunc((resultado->M[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
}

double Matriz::cofactor(double** matriz, int orden, int fila, int columna){
    int n = orden - 1;
    double** submatriz = new double*[n];

    for (int i = 0; i < n; i++)
        submatriz[i] = new double[n];

    int x = 0;
    int y = 0;

    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            if (i != fila && j != columna){
                submatriz[x][y] = matriz[i][j];
                y++;
                if (y >= n){
                    x++;
                    y = 0;
                }
            }
        }
    }
    int det = determinante(submatriz, n);
    delete []submatriz; // liberar memoria
    return pow(-1.0, fila + columna) * det;
}

double Matriz::determinante(double** matriz, int orden){
    int det = 0;
    if (orden == 1)
        det = matriz[0][0];
    else{
        for (int j = 0; j < orden; j++)
            det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
    }
    return det;
}

double Matriz::calcularDeterminante(){
	/* fuentes:
    https://www.youtube.com/watch?v=VMe384nPYi4
    https://algoritmosyalgomas.com/determinante-de-una-matriz-de-cualquier-orden-c/#Codigo-fuente-en-C
    */
    double deter = determinante(M, orden);
	return deter;
}

void Matriz::rellenarMatriz(){
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);

    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            M[i][j] = distribution(generator);
        }
    }
}

void Matriz::imprimirMatriz(int espacios){
    for(int i = 0 ; i < orden ; i++){
        cout << "|";
        for(int j = 0 ; j < orden ; j++){
            cout << setw(espacios) << M[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

Matriz::Matriz(int orden){
    this->orden = orden;
    M = new double*[this->orden];
    for(int i = 0; i < this->orden; i++)
        M[i] = new double[this->orden];
}

Matriz::~Matriz(){
    for (int i = 0; i < orden; i++)
        delete[] M[i]; // liberar memoria de la segunda dimension

    delete[] M; // liberar memoria de la primera dimension
}
