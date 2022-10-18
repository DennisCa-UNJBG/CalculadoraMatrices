#ifndef _MATRIZ_
#define _MATRIZ_

class Matriz{ /* clase base de una matriz */
public:
    /* varibles de configuracion */
    static int MIN; // minimo valor aleatorio
    static int MAX; // maximo valor aleatorio
    static int TABLA; // espacios para ordenar valores en la tabla

    Matriz(int orden);
    Matriz(int filas, int columnas);
    ~Matriz();
    void imprimirMatriz(int espacios = TABLA);
    void rellenarMatriz(void);
    double calcularDeterminante(void);
    Matriz* calcularInversa(double& deter);
    inline int getOrden(void) { return orden; }
    inline bool getIsCuadrado(void) { return isCuadrado; }
    inline int getFilas(void) { return filas; }
    inline int getColumnas(void) { return columnas; }
    inline double** getInicio(void) { return M; }
private:
    double** M;
    int orden;
    int filas;
    int columnas;
    bool isCuadrado = false;
    double determinante(double** matriz, int orden);
    double cofactor(double** matriz, int orden, int fila, int columna);
    Matriz* traspuesta(void);
    // sobrecarga de operadores
    friend Matriz* operator+(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator-(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator*(Matriz& matriz01, Matriz& matriz02);
    friend Matriz* operator*(Matriz& matriz, double numero);
protected:
};

#endif
