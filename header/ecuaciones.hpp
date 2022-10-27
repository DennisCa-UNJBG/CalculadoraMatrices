#ifndef _ECUACIONES_
#define _ECUACIONES_

class Ecuaciones{
public:
    static int MIN; // minimo valor aleatorio
    static int MAX; // maximo valor aleatorio
    Ecuaciones(int cantIncognitas);
    ~Ecuaciones();
    void imprimir(int espacios = 7); // min 5
    void rellenarAleatoriamente(void);
    void rellenar(void);
    void metodoGauss(void);
    void metodoGaussSeidel(int cantIter);
    // metodo para ordenar ecuaciones por el primer elemento de mayor a menor
    void pivoteoMatriz(int fil, int col); // pivoteo
private:
    double** matriz;
    int filas;
    int columnas;
    void imprimirIncognitas(double* array);
protected:
};

#endif
