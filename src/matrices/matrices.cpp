//cabecera custom
#include <matrices.hpp>

/* implementación de los metodos de la clase  Matriz */
Matrices* operator+(Matrices& matriz01, Matrices& matriz02){
    Matrices* resultado = new Matrices(matriz01.getFilas(), matriz01.getColumnas());
    for (int i = 0; i < matriz01.getFilas(); i++){
        for (int j = 0; j < matriz01.getColumnas(); j++){
            resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->getMatriz()[i][j] = matriz01.getMatriz()[i][j] + matriz02.getMatriz()[i][j];
        }
    }
    return resultado;
}

Matrices* operator-(Matrices& matriz01, Matrices& matriz02){
    Matrices* resultado = new Matrices(matriz01.getFilas(), matriz01.getColumnas());
    for (int i = 0; i < matriz01.getFilas(); i++){
        for (int j = 0; j < matriz01.getColumnas(); j++){
            resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->getMatriz()[i][j] = matriz01.getMatriz()[i][j] - matriz02.getMatriz()[i][j];
        }
    }
    return resultado;
}

Matrices* operator*(Matrices& matriz01, Matrices& matriz02){
    Matrices* resultado;
    if(matriz01.getIsCuadrado() && matriz02.getIsCuadrado()){ // la matriz es cuadrada ?
        //fuente: https://www.lawebdelprogramador.com/foros/Dev-C/1371193-MULTIPLICACION-DE-MATRICES.html
        resultado = new Matrices(matriz01.getOrden());
        // multiplicar matrices usando otra para almacenar datos
        for(int i = 0; i < matriz01.getOrden(); i++){
            for(int j = 0; j < matriz01.getOrden(); j++){
                resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
                for(int z = 0; z < matriz01.getOrden(); z++){
                    resultado->getMatriz()[i][j] += matriz01.getMatriz()[i][z] * matriz02.getMatriz()[z][j];
                }
            }
        }
    } else { // fuente: https://www.youtube.com/watch?v=Tjrm3HsqBXE
        // toma la cantidad de getFilas() de la primera matriz
        // toma la cantidad de getColumnas() de la segunda matriz
        resultado = new Matrices(matriz01.getFilas(), matriz02.getColumnas());
        for(int i = 0; i < matriz01.getFilas(); i++){
            for(int j = 0; j < matriz02.getColumnas(); j++){
                resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
                for(int z = 0; z < matriz01.getColumnas(); z++){
                    resultado->getMatriz()[i][j] += matriz01.getMatriz()[i][z] * matriz02.getMatriz()[z][j];
                }
            }
        }
    }
    return resultado;
}

Matrices* operator*(Matrices& matriz01, double numero){
    Matrices* resultado = new Matrices(matriz01.getFilas(), matriz01.getColumnas());
    for (int i = 0; i < matriz01.getFilas(); i++){
        for (int j = 0; j < matriz01.getColumnas(); j++){
            resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->getMatriz()[i][j] = matriz01.getMatriz()[i][j] * numero;
            // aplicamos 'trunc' para limitar los decimales
            resultado->getMatriz()[i][j] = trunc((resultado->getMatriz()[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
}

Matrices* Matrices::traspuesta(void){
    Matrices* resultado = new Matrices(this->getOrden());
    for (int i = 0; i < this->getOrden(); i++){
        for (int j = 0; j < this->getOrden(); j++){
            resultado->getMatriz()[i][j] = this->getMatriz()[j][i];
        }
    }
    return resultado;
}

Matrices* Matrices::calcularInversa(double& deter){
    Matrices* resultado = new Matrices(this->getOrden());
    // encontramos la matriz de cofactores
    for(int i = 0; i < this->getOrden(); i++){
        for(int j = 0; j < this->getOrden(); j++){
            resultado->getMatriz()[i][j] = 0; // para evitar problemas primero llenamos la casilla con un valor
            resultado->getMatriz()[i][j] = cofactor(this->getMatriz(), getOrden(), i, j);
        }
    }
    // hacemos la traspuesta de la matriz
    Matrices* aux = resultado;
    resultado = aux->traspuesta();
    delete aux;
    // aplicamos la multiplicacion por la determinante
    for(int i = 0; i < this->getOrden(); i++){
        for(int j = 0; j < this->getOrden(); j++){
            resultado->getMatriz()[i][j] = resultado->getMatriz()[i][j] / deter;
            // aplicamos 'trunc' para limitar los decimales
            resultado->getMatriz()[i][j] = trunc((resultado->getMatriz()[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
}

double Matrices::cofactor(double** matriz, int orden, int fila, int columna){
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

double Matrices::determinante(double** matriz, int orden){
    int det = 0;
    if (orden == 1)
        det = matriz[0][0];
    else{
        for (int j = 0; j < orden; j++)
            det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
    }
    return det;
}

double Matrices::calcularDeterminante(void){
	/* fuentes:
    https://www.youtube.com/watch?v=VMe384nPYi4
    https://algoritmosyalgomas.com/determinante-de-una-matriz-de-cualquier-orden-c/#Codigo-fuente-en-C
    */
    double deter = (this->getIsCuadrado()) ? determinante(getMatriz(), getOrden()) : 0 ;
	return deter;
}
