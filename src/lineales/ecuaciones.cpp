// cabecera custom
#include <ecuaciones.hpp>

void Ecuaciones::imprimirIncognitas(double* array){
    int caracter = 97;
    for(int i = 0; i < this->filas; i++)
        cout << "\t" << (char)(caracter+i) << " = " << array[i] << endl;
}

bool Ecuaciones::EpsilonSeidel(double* oldSol, double* newSol, int cantidad){
    double EPSILON = 0.01; // error iterativo como tolerancia
    double aux = 0;
    for(int i = 0; i < cantidad; i++){
        aux = ((newSol[i] - oldSol[i]) / newSol[i]) * 100;
        //cout << newSol[i] << " - " << oldSol[i] << " '"<< aux <<"' --"; // para ver los calculos
        if(abs(aux) < EPSILON)
            return false;
    }
    cout << endl;
    return true;
}

bool Ecuaciones::DiagonalDominante(){
    for(int i=0; i < this->filas; i++){
        float sumador = 0;
        for(int j=0; j < this->columnas-1; j++){
            if(i == j)
                continue;

            sumador += abs(this->matriz[i][j]);
        }
        if(abs(this->matriz[i][i]) < sumador) // si la diagonal no es dominante abortamos
            return false;
    }

    return true;
}

void Ecuaciones::metodoGaussSeidel(){
    // usamos una variable temporal para no afectar a la matriz original
    Ecuaciones* temporal = new Ecuaciones(this->filas);
    // copiar datos de la matriz original
    for(int i=0; i < this->filas; i++){
        for(int j=0; j < this->columnas; j++){
            temporal->matriz[i][j] = this->matriz[i][j];
        }
    }
    // creando vector dominante
    for(int i = 0; i < this->filas; i++)
        temporal->pivoteoMatriz(i, i); // ordenar ecuaciones por el primer elemento de mayor a menor

    cout << "\nLuego de ordenar las ecuaciones obtenemos el vector dominante: " << endl;
    temporal->imprimir();

    if(!temporal->DiagonalDominante()){
        cout << "ERROR: La diagonal no cumple con el requisito de ser dominante." << endl;
        return;
    }

    // crear nueva matriz para las incognitas
    double* incognitasOld = new double[temporal->filas];
    double* incognitasNew = new double[temporal->filas];
    for(int i = 0; i < temporal->filas; i++)
        incognitasOld[i] = 0; // rellenando matriz para evitar errores

    for(int i = 0; i < temporal->filas; i++)
        incognitasNew[i] = -10; // rellenando matriz para evitar errores

    // gauss seidel
    double sumador = 0;
    int k = 0;
    while (EpsilonSeidel(incognitasOld, incognitasNew, temporal->filas)){
        for(int i = 0; i < temporal->filas; i++){
            for(int j = 0; j < temporal->columnas-1; j++){
                if(i == j)
                    continue; // si i == J nose realiza ninguna operación
                sumador += temporal->matriz[i][j] * incognitasOld[j];
            }
            incognitasOld[i] = incognitasNew[i];
            incognitasNew[i] = (temporal->matriz[i][temporal->columnas-1] - sumador) / temporal->matriz[i][i];
            sumador = 0;
        }
        cout << "\n\t0" << k+1 << " iteracion:" << endl;
        temporal->imprimirIncognitas(incognitasNew);
        k++;
    }

    // liberar memoria
    delete []incognitasOld;
    delete []incognitasNew;
    delete temporal;
}

void Ecuaciones::pivoteoMatriz(int fil, int col){
    float mayor, comparar, aux1, aux2;
    for(int k = fil; k < filas; k++){
        mayor = abs(matriz[k][col]);
        for(int i = k+1; i < filas; i++){
            comparar = abs(matriz[i][col]);
            if(mayor < comparar){
                mayor = comparar;
                for(int j = 0; j < columnas; j++){ // intercambiamos filas
                    aux1 = matriz[k][j];
                    aux2 = matriz[i][j];
                    matriz[k][j] = aux2;
                    matriz[i][j] = aux1;
                }
            }
        }
    }
}

void Ecuaciones::metodoGauss(){
    Ecuaciones* temporal = new Ecuaciones(this->filas);
    // copiar datos de la matriz original
    for(int i=0; i < this->filas; i++){
        for(int j=0; j < this->columnas; j++){
            temporal->matriz[i][j] = this->matriz[i][j];
        }
    }

    temporal->pivoteoMatriz(0, 0); // ordenar ecuaciones por el primer elemento de mayor a menor
    cout << "\nLuego de ordenas las ecuaciones de mayor a menor obtenemos: " << endl;
    temporal->imprimir();

    int iterador = 1;
    // recorremos la diagonal para ver si existe un elemento igual a CERO
    for(int k = 0; k < filas; k++){
        if(temporal->matriz[k][k] == 0){
            cout << "La matriz no tiene solucion, un elemento de la diagonal es 0..." << endl;
            delete temporal; // liberar memoria
            return;
        } else {
            // metodo de gauss
            for(int i = k+1; i < filas; i++){ // recorremos la fila
                double aux = temporal->matriz[i][k]; // guardamos para evitar que se pierda el valor original al reemplazar la fila
                for(int j = k; j < columnas; j++){ // recorremos las columnas de la fila
                    temporal->matriz[i][j] = temporal->matriz[i][j] - ((aux/temporal->matriz[k][k]) * temporal->matriz[k][j]);
                    temporal->matriz[i][j] = trunc(temporal->matriz[i][j]*1000)/1000;// redondear valor para trabajar con 3 decimales
                }
                cout << "\n0" << iterador++ << " iteracion:" << endl;
                temporal->imprimir();
            }
        }
    }

    // Vertificar que los elementos operados sean igual a CERO(matriz escalonada)
    bool fallo = false;
    for(int i=1; i < temporal->filas; i++){
        for(int j=0; j < i; j++){
            if(temporal->matriz[i][j] != 0)
                fallo = true; // alguno de los elementos de la escalera inferior es diferente de CERO
        }
    }

    if(fallo){
        cout << "Imposible calcular las incognitas, el metodo de GAUSS fallo..." << endl;
        delete temporal; // liberar memoria
        return;
    }

    /* obtener el valor de las incognitas */
    int filT = temporal->filas;
    int colT = temporal->columnas;
    double* incognitas = new double[filT];

    // obtenemos la ultima incognita para operar el resto
    incognitas[filT-1] = temporal->matriz[filT-1][colT-1]/temporal->matriz[filT-1][colT-2];
    double operacion = 0;
    for(int i=filT-2; i >= 0; i--){
        for(int j=i+1; j < colT-1; j++){
            operacion += temporal->matriz[i][j] * incognitas[j];
        }
        incognitas[i] = (temporal->matriz[i][temporal->columnas-1]-operacion)/temporal->matriz[i][i];
        operacion = 0; // reiniciando sumador
    }

    // imprimir valor de las incognitas
    int caracter = 97;
    for(int i = 0; i < filT; i++)
        cout << (char)(caracter+i) << " = " << incognitas[i] << endl;

    delete []incognitas; // liberar memoria
    delete temporal; // liberar memoria
}

void Ecuaciones::imprimir(int espacios){
    int caracter = 97;
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            if(j == columnas-1){
                cout << "  = ";
                cout << setw(espacios-2)  << setprecision(3) << matriz[i][j] << " ";
            } else {
                cout << setw(espacios)  << setprecision(3) << matriz[i][j];
                cout << (char)(caracter+j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void Ecuaciones::rellenar(void){
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

void Ecuaciones::rellenarAleatoriamente(void){
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<int> distribution(MIN, MAX);

    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matriz[i][j] = distribution(generator);
        }
    }
}

Ecuaciones::~Ecuaciones(){
    for (int i = 0; i < filas; i++)
        delete[] matriz[i]; // liberar memoria de la segunda dimension

    delete[] matriz; // liberar memoria de la primera dimension
}

Ecuaciones::Ecuaciones(int cantIncognitas){
    this->filas = cantIncognitas;
    this->columnas = cantIncognitas + 1; // las columnas deben tener un espacio mas para la incognita
    matriz = new double*[this->filas];
    for(int i = 0; i < this->filas; i++)
        matriz[i] = new double[this->columnas];
}
