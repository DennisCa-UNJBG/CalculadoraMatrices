// cabecera custom
#include <nolineales.hpp>

double EcuNoLineales::calcFuncion(double valX){
    double valorFuncion = 0.0;
    for(int i = 0; i < getColumnas(); i++)
        valorFuncion += getMatriz()[0][i]*(pow(valX, getColumnas()-1-i));

    return valorFuncion;
}

void EcuNoLineales::metodoNewtonRaphson(double valX){
    double EPSILON = 0.001;
    bool cancelar = false;

    if(derivada == nullptr)
        derivada = new EcuNoLineales(getColumnas()-1);

    cout << "La derivada de la ecuacion es:" << endl;
    obtenerDerivar();

    double xOld = valX; // x0 inicial
    double xNew = xOld;
    double resultado = 0;
    int iterador = 1;

    cout << "Resultados:" << endl;
    while (!cancelar)
    {
        xNew = xOld - (this->calcFuncion(xOld) / derivada->calcFuncion(xOld));
        xNew = trunc(xNew*10000)/10000;// redondear valor para trabajar con 3 decimales
        resultado = abs(xNew - xOld);

        cout << setw(10) << iterador
        << setw(10) << xOld
        << setw(10) << xNew
        << setw(10) << resultado << endl;

        if(EPSILON > resultado)
            cancelar = true;

        xOld = xNew;
        iterador++;
    }

    return;
}

void EcuNoLineales::obtenerDerivar(void){
    int aux = derivada->getColumnas();

    for(int i = 0; i < aux; i++){
        if(i != aux-1){
            derivada->getMatriz()[0][i] = getMatriz()[0][i] * (aux-i);
        } else
            derivada->getMatriz()[0][i] = getMatriz()[0][i];
    }

    derivada->imprimir();
    return;
}

void EcuNoLineales::imprimir(int espacios){
    for(int i = 0 ; i < getFilas() ; i++){
        for(int j = 0 ; j < getColumnas() ; j++){
            if(j != getColumnas()-1)
                cout << setw(espacios) << getMatriz()[i][j] << "X^" << getColumnas()-1-j;
            else
                cout << setw(espacios) << getMatriz()[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
