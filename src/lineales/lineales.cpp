// cabecera custom
#include <lineales.hpp>

void EcuaLineales::imprimirIncognitas(double* array){
    int caracter = 97;
    for(int i = 0; i < this->getFilas(); i++)
        cout << "\t" << (char)(caracter+i) << " = " << array[i] << endl;
}

bool EcuaLineales::EpsilonSeidel(double* oldSol, double* newSol, int cantidad){
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

bool EcuaLineales::DiagonalDominante(){
    for(int i=0; i < this->getFilas(); i++){
        float sumador = 0;
        for(int j=0; j < this->getColumnas()-1; j++){
            if(i == j)
                continue;

            sumador += abs(this->getMatriz()[i][j]);
        }
        if(abs(this->getMatriz()[i][i]) < sumador) // si la diagonal no es dominante abortamos
            return false;
    }

    return true;
}

void EcuaLineales::metodoGaussSeidel(){
    // usamos una variable temporal para no afectar a la matriz original
    EcuaLineales* temporal = new EcuaLineales(this->getFilas());
    // copiar datos de la matriz original
    for(int i=0; i < this->getFilas(); i++){
        for(int j=0; j < this->getColumnas(); j++){
            temporal->getMatriz()[i][j] = this->getMatriz()[i][j];
        }
    }
    // creando vector dominante
    for(int i = 0; i < this->getFilas(); i++)
        temporal->pivoteoMatriz(i, i); // ordenar ecuaciones por el primer elemento de mayor a menor

    cout << "\nLuego de ordenar las ecuaciones obtenemos el vector dominante: " << endl;
    temporal->imprimir();

    if(!temporal->DiagonalDominante()){
        cout << "ERROR: La diagonal no cumple con el requisito de ser dominante." << endl;
        return;
    }

    // crear nueva matriz para las incognitas
    double* incognitasOld = new double[temporal->getFilas()];
    double* incognitasNew = new double[temporal->getFilas()];
    for(int i = 0; i < temporal->getFilas(); i++)
        incognitasOld[i] = 0; // rellenando matriz para evitar errores

    for(int i = 0; i < temporal->getFilas(); i++)
        incognitasNew[i] = -10; // rellenando matriz para evitar errores

    // gauss seidel
    double sumador = 0;
    int k = 0;
    while (EpsilonSeidel(incognitasOld, incognitasNew, temporal->getFilas())){
        for(int i = 0; i < temporal->getFilas(); i++){
            for(int j = 0; j < temporal->getColumnas()-1; j++){
                if(i == j)
                    continue; // si i == J nose realiza ninguna operación
                sumador += temporal->getMatriz()[i][j] * incognitasOld[j];
            }
            incognitasOld[i] = incognitasNew[i];
            incognitasNew[i] = (temporal->getMatriz()[i][temporal->getColumnas()-1] - sumador) / temporal->getMatriz()[i][i];
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

void EcuaLineales::pivoteoMatriz(int fil, int col){
    float mayor, comparar, aux1, aux2;
    for(int k = fil; k < getFilas(); k++){
        mayor = abs(getMatriz()[k][col]);
        for(int i = k+1; i < getFilas(); i++){
            comparar = abs(getMatriz()[i][col]);
            if(mayor < comparar){
                mayor = comparar;
                for(int j = 0; j < getColumnas(); j++){ // intercambiamos filas
                    aux1 = getMatriz()[k][j];
                    aux2 = getMatriz()[i][j];
                    getMatriz()[k][j] = aux2;
                    getMatriz()[i][j] = aux1;
                }
            }
        }
    }
}

void EcuaLineales::metodoGauss(){
    EcuaLineales* temporal = new EcuaLineales(this->getFilas());
    // copiar datos de la matriz original
    for(int i=0; i < this->getFilas(); i++){
        for(int j=0; j < this->getColumnas(); j++){
            temporal->getMatriz()[i][j] = this->getMatriz()[i][j];
        }
    }

    temporal->pivoteoMatriz(0, 0); // ordenar ecuaciones por el primer elemento de mayor a menor
    cout << "\nLuego de ordenas las ecuaciones de mayor a menor obtenemos: " << endl;
    temporal->imprimir();

    int iterador = 1;
    // recorremos la diagonal para ver si existe un elemento igual a CERO
    for(int k = 0; k < getFilas(); k++){
        if(temporal->getMatriz()[k][k] == 0){
            cout << "La matriz no tiene solucion, un elemento de la diagonal es 0..." << endl;
            delete temporal; // liberar memoria
            return;
        } else {
            // metodo de gauss
            for(int i = k+1; i < getFilas(); i++){ // recorremos la fila
                double aux = temporal->getMatriz()[i][k]; // guardamos para evitar que se pierda el valor original al reemplazar la fila
                for(int j = k; j < getColumnas(); j++){ // recorremos las columnas de la fila
                    temporal->getMatriz()[i][j] = temporal->getMatriz()[i][j] - ((aux/temporal->getMatriz()[k][k]) * temporal->getMatriz()[k][j]);
                    temporal->getMatriz()[i][j] = trunc(temporal->getMatriz()[i][j]*1000)/1000;// redondear valor para trabajar con 3 decimales
                }
                cout << "\n0" << iterador++ << " iteracion:" << endl;
                temporal->imprimir();
            }
        }
    }

    // Vertificar que los elementos operados sean igual a CERO(matriz escalonada)
    bool fallo = false;
    for(int i=1; i < temporal->getFilas(); i++){
        for(int j=0; j < i; j++){
            if(temporal->getMatriz()[i][j] != 0)
                fallo = true; // alguno de los elementos de la escalera inferior es diferente de CERO
        }
    }

    if(fallo){
        cout << "Imposible calcular las incognitas, el metodo de GAUSS fallo..." << endl;
        delete temporal; // liberar memoria
        return;
    }

    /* obtener el valor de las incognitas */
    int filT = temporal->getFilas();
    int colT = temporal->getColumnas();
    double* incognitas = new double[filT];

    // obtenemos la ultima incognita para operar el resto
    incognitas[filT-1] = temporal->getMatriz()[filT-1][colT-1]/temporal->getMatriz()[filT-1][colT-2];
    double operacion = 0;
    for(int i=filT-2; i >= 0; i--){
        for(int j=i+1; j < colT-1; j++){
            operacion += temporal->getMatriz()[i][j] * incognitas[j];
        }
        incognitas[i] = (temporal->getMatriz()[i][temporal->getColumnas()-1]-operacion)/temporal->getMatriz()[i][i];
        operacion = 0; // reiniciando sumador
    }

    // imprimir valor de las incognitas
    int caracter = 97;
    for(int i = 0; i < filT; i++)
        cout << (char)(caracter+i) << " = " << incognitas[i] << endl;

    delete []incognitas; // liberar memoria
    delete temporal; // liberar memoria
}

void EcuaLineales::imprimir(int espacios){
    int caracter = 97;
    for(int i = 0 ; i < getFilas() ; i++){
        cout << "|";
        for(int j = 0 ; j < getColumnas() ; j++){
            if(j == getColumnas()-1){
                cout << "  = ";
                cout << setw(espacios-2)  << setprecision(3) << getMatriz()[i][j] << " ";
            } else {
                cout << setw(espacios)  << setprecision(3) << getMatriz()[i][j];
                cout << (char)(caracter+j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}

/*EcuaLineales::~EcuaLineales(){
    for (int i = 0; i < getFilas(); i++)
        delete[] getMatriz()[i]; // liberar memoria de la segunda dimension

    delete[] getMatriz(); // liberar memoria de la primera dimension
}*/
