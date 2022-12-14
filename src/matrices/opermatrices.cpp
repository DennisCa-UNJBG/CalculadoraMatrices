// cabecera custom
#include <opermatrices.hpp>

struct OperMatrices{  /* estructura para controlar las opciones del menu de operaciones */
    string opciones;
    void (OperacMatrices::*method)(void);
};

vector <OperMatrices> MenuMatrices = { // opciones del menu de operaciones
    { "Crear nueva matriz",                      &OperacMatrices::crearMatriz},
    { "Ver matrices existentes",                 &OperacMatrices::verMatrices},
    { "Calcular la determinante de una matriz",  &OperacMatrices::deterMatriz }, // 1 matriz X
    { "Calcular la inversa de una matriz",       &OperacMatrices::inversaMatriz }, // 1 matriz X
    { "Sumar matrices",                          &OperacMatrices::sumarMatrices }, // 2 matrices
    { "Restar matrices",                         &OperacMatrices::restarMatrices }, // 2 matrices
    { "multiplar matrices",                      &OperacMatrices::multiMatrices }, // 2 matrices
    { "multiplar matriz por un escalar",         &OperacMatrices::multiEscalarMatriz }, // 1 matriz X y 1 entero
    { "Regresar al menu Principal",              &OperacMatrices::salirMenuOper } // cambiar variable global
}; // empleamos los punteros a metodos de clase

void OperacMatrices::mostrarMenu(){
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

void OperacMatrices::seleccionarOpcion(int opcion){
    if((size_t)opcion > MenuMatrices.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (this->*MenuMatrices[opcion-1].method)();

    // no lanzar el pause si se elige la ultima opcion
    if((size_t)opcion != MenuMatrices.size())
        system("pause");
}

void  OperacMatrices::mostrarOpciones(){
    cout << "\n\tOPERACIONES CON MATRICES\n"
        << "******************************\n"
        << endl;

    for(size_t i = 0; i < MenuMatrices.size(); i++)
        cout << i+1 << ". " << MenuMatrices[i].opciones << endl;
}

void OperacMatrices::crearMatriz(){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int filas, columnas;
    cout << "Ingrese un nombre(sin espacios) para la matriz:" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;

    this->agregarMatriz(filas, columnas, nombre) ;
}

void OperacMatrices::verMatrices(){
    map<string, Matrices*>::iterator iterador;
    cout << "\n\nImprimiendo matrices almacenadas: \n" << endl;
    for (iterador = this->matrices.begin(); iterador != this->matrices.end(); iterador++){
        // "first" tiene la clave. "second" el valor
        string clave = iterador->first;
        Matrices* valor = iterador->second;
        // usamos las variables Clave/Valor para mostrar resultados en pantalla
        cout << "La matriz : " << clave
            << "\nTiene los  valores:" << endl;
        valor->imprimir();
    }
}

/* implementaci??n de los metodos de la clase  OperacMatrices */

void OperacMatrices::deterMatriz(void){
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
}

void OperacMatrices::inversaMatriz(void){
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

    Matrices* matriz = this->matrices[nombreMatriz]->calcularInversa(det);
    cout << "La inversa de la matriz '" << nombreMatriz << "' es :" << endl;
    matriz->imprimir(7);
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

    Matrices* temp = *(this->matrices[nombreMatriz[0]]) * *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa multiplicacion de las matrices ( " << nombreMatriz[0] << " * " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimir();
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

    Matrices* temp = *(this->matrices[nombreMatriz]) * numero;
    cout << "\nLa multiplicacion de la matriz ( " << nombreMatriz << " * " << numero << " ) es:" << endl;
    temp->imprimir(7);
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

    Matrices* temp = *(this->matrices[nombreMatriz[0]]) - *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa resta de las matrices ( " << nombreMatriz[0] << " - " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimir();
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

    Matrices* temp = *(this->matrices[nombreMatriz[0]]) + *(this->matrices[nombreMatriz[1]]);
    cout << "\nLa suma de las matrices ( " << nombreMatriz[0] << " + " << nombreMatriz[1] << " ) es:" << endl;
    temp->imprimir();
    delete temp;  // liberar memoria
}

void OperacMatrices::salirMenuOper(void){
    openMenu = false;
}

void OperacMatrices::agregarMatriz(int& filas, int& columnas, string&nombre){
    Matrices* matriz;                 //crear matriz cuadrada         // crear matriz no cuadrada
    (filas == columnas) ? matriz = new Matrices(filas) : matriz = new Matrices(filas, columnas);
    matriz->rellenarAleatoriamente();
    cout << "\nLa matriz ingresada tiene los valores es:" << endl;
    matriz->imprimir();
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
