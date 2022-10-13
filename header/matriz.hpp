#ifndef _MATRIZ_
#define _MATRIZ_
#include <config.hpp>
class Matriz{ /* clase base de una matriz */
public:
    Matriz(int orden);
    Matriz(int filas, int columnas);
    ~Matriz();
    void imprimirMatriz(int espacios = VariablesConfig::TABLA, int coorX = VariablesConfig::coordenadaX, int coorY = VariablesConfig::coordenadaY);
    void rellenarMatriz();
    double calcularDeterminante();
    Matriz* calcularInversa(double& deter);
    inline int getOrden() { return orden; }
    inline bool getIsCuadrado() { return isCuadrado; }
    inline int getFilas() { return filas; }
    inline int getColumnas() { return columnas; }
    inline double** getInicio() { return M; }
private:
    double** M;
    int orden;
    int filas;
    int columnas;
    bool isCuadrado = false;
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

#endif
