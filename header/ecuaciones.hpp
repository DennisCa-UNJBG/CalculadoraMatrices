#ifndef _ECUACIONES_
#define _ECUACIONES_

class Ecuaciones{
public:
    static int MIN; // minimo valor aleatorio
    static int MAX; // maximo valor aleatorio
    Ecuaciones(int cantIncognitas);
    ~Ecuaciones();
    void imprimir(int espacios = 7); // min 5
    void rellenar(void);
    void metodoGauss(void);
    // metodo para ordenar ecuaciones por el primer elemento de mayor a menor
    void pivoteoMatriz(); // pivoteo
private:
    double** matriz;
    int filas;
    int columnas;
protected:
};

#endif
