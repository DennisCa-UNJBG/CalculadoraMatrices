// cabecera custom
#include <nolineales.hpp>

void EcuNoLineales::metodoNewtonRaphson(void){
    return;
}

void EcuNoLineales::imprimir(int espacios){
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
