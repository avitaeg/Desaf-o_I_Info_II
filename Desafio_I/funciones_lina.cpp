
// CREAR TAMAÑO DE TABLERO//
#include <iostream>

using namespace std;

void funcion_tablero (int &filas, int &columnas)
{

    for (; ; )
    {
        cout<< "Ingrese un numero de filas que sea multiplo de 8: " ;
        cin >> filas;

        if (filas > 0 && filas % 8==0)
        {
            break;
        }
        cout<< "Intente nuevamente." << endl;
        cout<< "Ingrese un numero que sea multiplo de 8 (8,16,24..). " << endl;
    }

    for (; ; )
    {
        cout<< "Ingrese un numero de columnas que sea mayor a 8: " ;
        cin >> columnas;

        if (columnas > 8 )
        {
            break;
        }
        cout<< "Intente nuevamente" << endl;
        cout<< "El numero debe ser mayor a 8" << endl;
    }

    cout<< "Tablero creado correctamente";

    return 0;
}


//FUNCIONES PARA DEFINIR LAS FIGURAS


// Figura I
void figura_I ( unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 4;
    Ancho = 1;
    fila[0] = 0b00000001;
    fila[1] = 0b00000001;
    fila[2] = 0b00000001;
    fila[3] = 0b00000001;
}

// Figura T

void figura_O (unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 2;
    Ancho = 3;
    fila[0] = 0b00000111;
    fila[1] = 0b00000010;
}
// Figura L

void figura_L (unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 3;
    Ancho = 2;
    fila[0] = 0b00000010;
    fila[1] = 0b00000010;
    fila[2] = 0b00000011;
}
// Figura J

void figura_J (unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 3;
    Ancho = 2;
    fila[0] = 0b00000001;
    fila[1] = 0b00000001;
    fila[2] = 0b00000011;
}
// Figura S

void figura_S (unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 2;
    Ancho = 3;
    fila[0] = 0b00000011;
    fila[1] = 0b00000110;
    ;
}
// Figura Z

void figura_Z (unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 2;
    Ancho = 3;
    fila[0] = 0b00000110;
    fila[1] = 0b00000011;

}
//ROTACIÓN DE LAS FIGURAS//

void Rotarfigura(unsigned char* figuraOriginal, unsigned char* figuraRotada, int alto, int ancho)
{
    for (int i = 0; i < ancho; i++)
    {
        figuraRotada[i] = 0;
    }

    for (int r = 0; r < alto; r++)
    {
        for (int c = 0; c < ancho; c++)
        {
            if (figuraOriginal[r] & (1 << c))
            {
                figuraRotada[c] |= (1 << (alto - 1 - r));
            }
        }
    }
}



