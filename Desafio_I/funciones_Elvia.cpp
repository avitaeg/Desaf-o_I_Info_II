#include <iostream>
using namespace std;

void crearTablero(unsigned char*& tablero, int& filas, int& columnas) {
    for (;;) {
        cout << "Ingrese el numero de filas (minimo 8): ";
        cin >> filas;
        if (filas >= 8)
            break;
        cout << "Intente nuevamente." << endl;
        cout << "El numero debe ser mayor o igual a 8." << endl;
    }

    for (;;) {
        cout << "Ingrese el numero de columnas (minimo 8, multiplo de 8): ";
        cin >> columnas;
        if (columnas >= 8 && columnas % 8 == 0)
            break;
        cout << "Intente nuevamente." << endl;
        cout << "El numero debe ser multiplo de 8 (8, 16, 24...)." << endl;
    }

    tablero = new unsigned char[filas * (columnas / 8)];

    for (int r = 0; r < filas * (columnas / 8); r++)
        tablero[r] = 0;

    cout << "Tablero creado correctamente." << endl;
}

//Funcion para colocar pieza
void colocarPieza(unsigned char* tablero, unsigned char* filasPieza,
                  int altoPieza, int colPieza, int filaPieza) {
    for (int r = 0; r < altoPieza; r++) {
        tablero[filaPieza + r] |= (filasPieza[r] << colPieza);
    }
}

//Funcion para quitar pieza

void quitarPieza(unsigned char* tablero, unsigned char* filasPieza,
                 int altoPieza, int colPieza, int filaPieza) {
    for (int r = 0; r < altoPieza; r++) {
        tablero[filaPieza + r] &= ~(filasPieza[r] << colPieza);
    }
}


void imprimirTablero(unsigned char* tablero, unsigned char* filasPieza,
                     int filas, int columnas, int altoPieza,
                     int colPieza, int filaPieza) {

    for (int r = 0; r < filas; r++) {
        unsigned char filaVisible = tablero[r];

        // agregar la pieza visualmente sin modificar el tablero
        if (r >= filaPieza && r < filaPieza + altoPieza) {
            filaVisible |= (filasPieza[r - filaPieza] << colPieza);
        }

        // imprimir bit a bit de izquierda a derecha
        for (int b = columnas - 1; b >= 0; b--) {
            if ((filaVisible >> b) & 1)
                cout << "# ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}


bool hayColision(unsigned char* tablero, unsigned char* filasPieza,
                 int filas, int columnas, int altoPieza, int anchoPieza,
                 int colPieza, int filaPieza) {

    // se sale por abajo
    if (filaPieza + altoPieza > filas)
        return true;

    // se sale por la derecha
    if (colPieza + anchoPieza > columnas)
        return true;

    // se sale por la izquierda
    if (colPieza < 0)
        return true;

    // choca con algo en el tablero
    for (int r = 0; r < altoPieza; r++) {
        if (tablero[filaPieza + r] & (filasPieza[r] << colPieza))
            return true;
    }

    return false;
}
