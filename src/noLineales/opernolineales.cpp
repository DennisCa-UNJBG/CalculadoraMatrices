#include <opernolineales.hpp>

struct Operaciones{  /* estructura para controlar las opciones del menu de operaciones */
    string opciones;
    void (OperEcuNoLineales::*method)(void);
};

vector <Operaciones> MenuNoLineales = { // opciones del menu de operaciones
    { "Crear nueva ecuacion",                   &OperEcuNoLineales::crearEcuacion }
    ,{ "Calcular incognitas - newton Raphson",  &OperEcuNoLineales::calcularNewtonRaphson }
    ,{ "Regresar",                              &OperEcuNoLineales::salirMenu }
}; // empleamos los punteros a metodos de clase

void OperEcuNoLineales::mostrarMenu(){
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

void OperEcuNoLineales::agregarMatriz(int& cantIncognitas, string&nombre){
    EcuNoLineales* matriz = new EcuNoLineales(cantIncognitas);
    char numAleatorios = false;
    cout << "\nRellenar los valores de forma aleatoria?(y/n): " << endl;
    cin >> numAleatorios;
    (numAleatorios == 'y') ? matriz->rellenarAleatoriamente() : matriz->rellenar();
    cout << "\nLa matriz de NuevaEcuacion tiene los valores:" << endl;
    matriz->imprimir();
    matrices[nombre] = matriz;
}

void OperEcuNoLineales::crearEcuacion() {
    string nombre;
    int cantIncognitas;
    cout << "\nIngrese un nombre(sin espacios):" << endl;
    cin.sync(); getline(cin,nombre);

    cout << "\nIngrese la cantidad de incognitas: " << endl;
    cin >> cantIncognitas;
    this->agregarMatriz(cantIncognitas, nombre) ;
}

void OperEcuNoLineales::calcularNewtonRaphson(void){
    string nombreMatriz;
    bool cancelar = false;
    // buscar la matriz que se necesita para la operacion
    this->buscarMatriz(cancelar, 1, nombreMatriz);

    if(cancelar)
        return;

    this->matrices[nombreMatriz]->metodoNewtonRaphson();
}

void OperEcuNoLineales::buscarMatriz(bool& cancelar, int cantMatriz, string& nombre){
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

void  OperEcuNoLineales::mostrarOpciones(){
    cout << "\n\tOPERACIONES CON ECUACIONES\n"
        << "******************************************\n"
        << endl;

    for(size_t i = 0; i < MenuNoLineales.size(); i++)
        cout << i+1 << ". " << MenuNoLineales[i].opciones << endl;
}

void OperEcuNoLineales::seleccionarOpcion(int opcion){
    if((size_t)opcion > MenuNoLineales.size() || opcion <= 0)
        cout << "ERROR: Valor ingresado no valido" << endl;
    else
        (this->*MenuNoLineales[opcion-1].method)();

    // no lanzar el pause si se elige la ultima opcion
    if((size_t)opcion != MenuNoLineales.size())
        system("pause");
}

void OperEcuNoLineales::salirMenu(void){
    openMenu = false;
}
