//cabecera custom
#include <matriz_base.hpp>

void MatrizBase::rellenar(void){
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if(j != columnas-1)
                cout << "Ingrese el valor de la matriz [" << i << "][" << j << "]: ";
            else
                cout << "Ingrese el valor independiente: ";
            cin >> matriz[i][j];
            cout << endl;
        }
    }
}

void MatrizBase::rellenarAleatoriamente(void){
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matriz[i][j] = distribution(generator);
        }
    }
}

void MatrizBase::imprimir(int espacios){
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            cout << setw(espacios) << matriz[i][j] << " ";
            }
        cout << "|" << endl;
    }
    cout << endl;
}

MatrizBase::MatrizBase(int orden){
    this->isCuadrado = true;
    this->orden = orden;
    this->filas = orden;
    this->columnas = orden;
    matriz = new double*[this->orden];
    for(int i = 0; i < this->orden; i++)
        matriz[i] = new double[this->orden];
}

MatrizBase::MatrizBase(int filas, int columnas){
    this->orden = filas; // para establecer compatibilidad con el código anterior
    this->filas = filas;
    this->columnas = columnas;
    matriz = new double*[this->filas];
    for(int i = 0; i < this->filas; i++)
        matriz[i] = new double[this->columnas];
}

MatrizBase::~MatrizBase(){
    for (int i = 0; i < orden; i++)
        delete[] matriz[i]; // liberar memoria de la segunda dimension

    delete[] matriz; // liberar memoria de la primera dimension
}
