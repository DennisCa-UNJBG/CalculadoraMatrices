// cabecera custom
#include <operlineales.hpp>

struct Operaciones{  /* estructura para controlar las opciones del menu de operaciones */
    string opciones;
    void (OperEcuaLineales::*method)(void);
};

vector <Operaciones> MenuLineales = { // opciones del menu de operaciones
    { "Crear nueva matriz de Ecuaciones",        &OperEcuaLineales::crearMatriz }
    ,{ "Ver matrices de ecuaciones existentes",  &OperEcuaLineales::verMatrices }
    ,{ "Calcular incognitas - Gauss",            &OperEcuaLineales::calcularGauss }
    ,{ "Calcular incognitas - Gauss Seidel",     &OperEcuaLineales::calcularGaussSiedel }
    ,{ "Regresar al menu Principal",             &OperEcuaLineales::salirMenu }
}; // empleamos los punteros a metodos de clase

void OperEcuaLineales::mostrarMenu(){
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

void OperEcuaLineales::calcularGaussSiedel(){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    this->matrices[nombreMatriz]->metodoGaussSeidel();
}

void OperEcuaLineales::calcularGauss(){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    cout << "La matriz '" << nombreMatriz
        << "' esta siendo procesada empleando Gauss." << endl;
    this->matrices[nombreMatriz]->metodoGauss();
}

void OperEcuaLineales::verMatrices(){
    map<string, EcuaLineales*>::iterator iterador;
    cout << "\n\nImprimiendo matrices de ecuaciones lineales almacenadas: \n" << endl;
    for (iterador = this->matrices.begin(); iterador != this->matrices.end(); iterador++){
        // "first" tiene la clave. "second" el valor
        string clave = iterador->first;
        EcuaLineales* valor = iterador->second;
        // usamos las variables Clave/Valor para mostrar resultados en pantalla
        cout << "La matriz de ecuaciones lineales: '" << clave
            << "'\nTiene los  valores:" << endl;
        valor->imprimir();
    }
}

void OperEcuaLineales::crearMatriz(){ // se omite la variable opcion en la compilacion del programa
    string nombre;
    int cantIncognitas;
    cout << "\nIngrese un nombre(sin espacios):" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "\nIngrese la cantidad de incognitas: " << endl;
    cin >> cantIncognitas;
    this->agregarMatriz(cantIncognitas, nombre) ;
}

void OperEcuaLineales::agregarMatriz(int& cantIncognitas, string&nombre){
    EcuaLineales* matriz = new EcuaLineales(cantIncognitas);
    char numAleatorios = false;
    cout << "\nRellenar los valores de forma aleatoria?(y/n): " << endl;
    cin >> numAleatorios;
    (numAleatorios == 'y') ? matriz->rellenarAleatoriamente() : matriz->rellenar();
    cout << "\nLa matriz de ecuaciones tiene los valores:" << endl;
    matriz->imprimir();
    matrices[nombre] = matriz;
}

void OperEcuaLineales::salirMenu(void){
    openMenu = false;
}

void  OperEcuaLineales::mostrarOpciones(){
    cout << "\n\tOPERACIONES CON ECUACIONES\n"
        << "******************************************\n"
        << endl;

    for(size_t i = 0; i < MenuLineales.size(); i++)
        cout << i+1 << ". " << MenuLineales[i].opciones << endl;
}

void OperEcuaLineales::seleccionarOpcion(int opcion){
    if((size_t)opcion > MenuLineales.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (this->*MenuLineales[opcion-1].method)();

    // no lanzar el pause si se elige la ultima opcion
    if((size_t)opcion != MenuLineales.size())
        system("pause");
}

void OperEcuaLineales::buscarMatriz(bool& cancelar, int cantMatriz, string& nombre){
    bool matrizEncontrada = false;
    int intentos = 2; // cantidad de intentos para buscar una matriz
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
