#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

// ─── FIGURAS ───────────────────────────────────────────────────
void figura_I(unsigned char* fila, int& alto, int& ancho)
{
    alto = 4;
    ancho = 1;
    fila[0] = 0b00000001;
    fila[1] = 0b00000001;
    fila[2] = 0b00000001;
    fila[3] = 0b00000001;
}

void figura_O(unsigned char* fila, int& alto, int& ancho)
{
    alto = 2;
    ancho = 2;
    fila[0] = 0b00000011;
    fila[1] = 0b00000011;
}

void figura_T(unsigned char* fila, int& alto, int& ancho)
{
    alto = 2;
    ancho = 3;
    fila[0] = 0b00000111;
    fila[1] = 0b00000010;
}

void figura_L(unsigned char* fila, int& alto, int& ancho)
{
    alto = 3;
    ancho = 2;
    fila[0] = 0b00000010;
    fila[1] = 0b00000010;
    fila[2] = 0b00000011;
}

void figura_J(unsigned char* fila, int& alto, int& ancho)
{
    alto = 3;
    ancho = 2;
    fila[0] = 0b00000001;
    fila[1] = 0b00000001;
    fila[2] = 0b00000011;
}

void figura_S(unsigned char* fila, int& alto, int& ancho)
{
    alto = 2;
    ancho = 3;
    fila[0] = 0b00000011;
    fila[1] = 0b00000110;
}

void figura_Z(unsigned char* fila, int& alto, int& ancho)
{
    alto = 2;
    ancho = 3;
    fila[0] = 0b00000110;
    fila[1] = 0b00000011;
}

void generarFiguraAleatoria(unsigned char* fila, int& alto, int& ancho)
{
    for (int i = 0; i < 4; i++)
        fila[i] = 0;

    int opcion = rand() % 7;

    if (opcion == 0) figura_I(fila, alto, ancho);
    if (opcion == 1) figura_O(fila, alto, ancho);
    if (opcion == 2) figura_T(fila, alto, ancho);
    if (opcion == 3) figura_L(fila, alto, ancho);
    if (opcion == 4) figura_J(fila, alto, ancho);
    if (opcion == 5) figura_S(fila, alto, ancho);
    if (opcion == 6) figura_Z(fila, alto, ancho);
}

// ─── ROTACIÓN ──────────────────────────────────────────────────
void rotarPieza(unsigned char* pieza, int& alto, int& ancho)
{
    unsigned char rotada[4] = {};
    int nuevoAlto  = ancho;
    int nuevoAncho = alto;

    for (int r = 0; r < alto; r++)
    {
        for (int c = 0; c < ancho; c++)
        {
            if (pieza[r] & (1 << c))
                rotada[c] |= (1 << (alto - 1 - r));
        }
    }

    alto  = nuevoAlto;
    ancho = nuevoAncho;

    for (int i = 0; i < 4; i++)
        pieza[i] = rotada[i];
}

// ─── TABLERO ───────────────────────────────────────────────────
void crearTablero(unsigned char*& tablero, int& filas, int& columnas)
{
    for (;;)
    {
        cout << "Ingrese numero de filas (minimo 1): ";
        cin >> filas;
        if (filas > 0)
            break;
        cout << "Debe ser mayor a 0\n";
    }

    for (;;)
    {
        cout << "Ingrese numero de columnas (multiplo de 8): ";
        cin >> columnas;
        if (columnas >= 8 && columnas % 8 == 0)
            break;
        cout << "Debe ser multiplo de 8\n";
    }

    tablero = new unsigned char[filas * (columnas / 8)]();
    cout << "Tablero creado correctamente\n";
}

void colocarPieza(unsigned char* tablero, unsigned char* pieza,
                  int columnas, int altoPieza,
                  int colPieza, int filaPieza)
{
    int bytesFila = columnas / 8;

    for (int r = 0; r < altoPieza; r++)
    {
        int byteIndex = colPieza / 8;
        int offset    = colPieza % 8;
        tablero[(filaPieza + r) * bytesFila + byteIndex] |=
            (unsigned int)(pieza[r]) << offset;
    }
}

void quitarPieza(unsigned char* tablero, unsigned char* pieza,
                 int columnas, int altoPieza,
                 int colPieza, int filaPieza)
{
    int bytesFila = columnas / 8;

    for (int r = 0; r < altoPieza; r++)
    {
        int byteIndex = colPieza / 8;
        int offset    = colPieza % 8;
        tablero[(filaPieza + r) * bytesFila + byteIndex] &=
            ~((unsigned int)(pieza[r]) << offset);
    }
}

bool hayColision(unsigned char* tablero, unsigned char* pieza,
                 int filas, int columnas,
                 int altoPieza, int anchoPieza,
                 int colPieza, int filaPieza)
{
    int bytesFila = columnas / 8;

    if (filaPieza + altoPieza > filas)
        return true;
    if (colPieza < 0)
        return true;
    if (colPieza + anchoPieza > columnas)
        return true;

    for (int r = 0; r < altoPieza; r++)
    {
        int byteIndex = colPieza / 8;
        int offset    = colPieza % 8;
        if (tablero[(filaPieza + r) * bytesFila + byteIndex] &
            ((unsigned int)(pieza[r]) << offset))
            return true;
    }

    return false;
}

void eliminarFilasLlenas(unsigned char* tablero, int filas, int columnas)
{
    int bytesFila = columnas / 8;

    for (int r = filas - 1; r >= 0; r--)
    {
        bool llena = true;

        for (int b = 0; b < bytesFila; b++)
        {
            if (tablero[r * bytesFila + b] != 0xFF)
            {
                llena = false;
                break;
            }
        }

        if (llena)
        {
            for (int f = r; f > 0; f--)
                for (int b = 0; b < bytesFila; b++)
                    tablero[f * bytesFila + b] = tablero[(f - 1) * bytesFila + b];

            for (int b = 0; b < bytesFila; b++)
                tablero[b] = 0;

            r++;
        }
    }
}

void imprimirTablero(unsigned char* tablero, int filas, int columnas,
                     unsigned char* pieza, int altoPieza,
                     int colPieza, int filaPieza)
{
    colocarPieza(tablero, pieza, columnas, altoPieza, colPieza, filaPieza);

    int bytesFila = columnas / 8;

    for (int r = 0; r < filas; r++)
    {
        for (int b = 0; b < columnas; b++)
        {
            int byteIndex = b / 8;
            int offset    = b % 8;

            if ((tablero[r * bytesFila + byteIndex] >> offset) & 1)
                cout << "# ";
            else
                cout << ". ";
        }
        cout << "\n";
    }

    quitarPieza(tablero, pieza, columnas, altoPieza, colPieza, filaPieza);
}

// ─── MAIN ──────────────────────────────────────────────────────
int main()
{
    srand(time(NULL));

    unsigned char* tablero;
    int filas, columnas;
    crearTablero(tablero, filas, columnas);

    unsigned char pieza[4] = {};
    int altoPieza  = 0;
    int anchoPieza = 0;
    generarFiguraAleatoria(pieza, altoPieza, anchoPieza);

    int filaPieza = 0;
    int colPieza  = columnas / 2;

    if (colPieza + anchoPieza > columnas)
        colPieza = columnas - anchoPieza;

    while (true)
    {
        system("cls");
        imprimirTablero(tablero, filas, columnas,
                        pieza, altoPieza, colPieza, filaPieza);
        cout << "\nA: bajar | I: izquierda | D: derecha | R: rotar | ESC: salir\n";

        char tecla = _getch();

        if (tecla == 'a' || tecla == 'A')
        {
            if (!hayColision(tablero, pieza, filas, columnas,
                             altoPieza, anchoPieza,
                             colPieza, filaPieza + 1))
            {
                filaPieza++;
            }
            else
            {
                colocarPieza(tablero, pieza, columnas,
                             altoPieza, colPieza, filaPieza);
                eliminarFilasLlenas(tablero, filas, columnas);

                generarFiguraAleatoria(pieza, altoPieza, anchoPieza);
                filaPieza = 0;
                colPieza  = columnas / 2;

                if (colPieza + anchoPieza > columnas)
                    colPieza = columnas - anchoPieza;

                if (hayColision(tablero, pieza, filas, columnas,
                                altoPieza, anchoPieza,
                                colPieza, filaPieza))
                {
                    system("cls");
                    cout << "\n\n";
                    cout << "  +---------------------------+\n";
                    cout << "  |                           |\n";
                    cout << "  |     G A M E  O V E R     |\n";
                    cout << "  |                           |\n";
                    cout << "  +---------------------------+\n\n";
                    delete[] tablero;
                    return 0;
                }
            }
        }

        if (tecla == 'i' || tecla == 'I')
        {
            if (!hayColision(tablero, pieza, filas, columnas,
                             altoPieza, anchoPieza,
                             colPieza - 1, filaPieza))
                colPieza--;
        }

        if (tecla == 'd' || tecla == 'D')
        {
            if (!hayColision(tablero, pieza, filas, columnas,
                             altoPieza, anchoPieza,
                             colPieza + 1, filaPieza))
                colPieza++;
        }

        if (tecla == 'r' || tecla == 'R')
        {
            unsigned char piezaTemp[4] = {};
            int altoTemp  = altoPieza;
            int anchoTemp = anchoPieza;

            for (int i = 0; i < 4; i++)
                piezaTemp[i] = pieza[i];

            rotarPieza(piezaTemp, altoTemp, anchoTemp);

            if (!hayColision(tablero, piezaTemp, filas, columnas,
                             altoTemp, anchoTemp,
                             colPieza, filaPieza))
            {
                for (int i = 0; i < 4; i++)
                    pieza[i] = piezaTemp[i];
                altoPieza  = altoTemp;
                anchoPieza = anchoTemp;
            }
        }

        if (tecla == 27)
        {
            delete[] tablero;
            return 0;
        }
    }

    delete[] tablero;
    return 0;
}
