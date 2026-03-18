
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

void figura_O(unsigned char* fila, int& Alto, int& Ancho)
{
    Alto = 2;
    Ancho = 2;
    fila[0] = 0b00000011;
    fila[1] = 0b00000011;
}
// Figura T

void figura_T (unsigned char* fila, int& Alto, int& Ancho)
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

//GENERAR FIGURAS DE MANERA ALEATORIA

#include <cstdlib>
#include <ctime>

void generarFiguraAleatoria(unsigned char* fila, int &alto, int &ancho)
{
    int opcion = rand() % 7;

    switch(opcion)
    {
    case 0:
        figura_I(fila, alto, ancho);
        break;
    case 1:
        figura_O(fila, alto, ancho);
        break;
    case 2:
        figura_Z(fila, alto, ancho);
        break;
    case 3:
        figura_L(fila, alto, ancho);
        break;
    case 4:
        figura_J(fila, alto, ancho);
        break;
    case 5:
        figura_S(fila, alto, ancho);
        break;
    case 6:
        figura_Z(fila, alto, ancho);
        break;
    }
}
// GENERAR UN NUMERO ENTRE 1 Y 7
int main()
{
    srand(time(0));

    unsigned char figura[4]; // tamaño máximo
    int alto, ancho;

    generarFiguraAleatoria(figura, alto, ancho);

    cout << "Figura generada: " << endl;

    for(int i = 0; i < alto; i++)
    {
        for(int j = 0; j < ancho; j++)
        {
            if(figura[i] & (1 << j))
                cout << "[] ";
            else
                cout << " ";
        }
        cout << endl;
    }
