#include <iostream>

    using namespace std;

    int main()
    {
        int filas;
        int columnas;

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
            cout<< "Ingrese un numero de columnas que sea multiplo de 8: " ;
            cin >> columnas;

            if (columnas > 0 && columnas % 8==0)
            {
                break;
            }
            cout<< "Intente nuevamente" << endl;
            cout<< "Ingrese un numero que sea multiplo de 8 (8,16,24..)" << endl;
        }

        cout<< "Tablero creado correctamente";

        return 0;
    }


