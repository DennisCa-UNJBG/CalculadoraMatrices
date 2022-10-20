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
    // Falta implementar: metodo para ordenar la matriz de menor a mayor
    void matrizEscalonada(int espacios = 7);
private:
    double** matriz;
    int filas;
    int columnas;
protected:
};

#endif
