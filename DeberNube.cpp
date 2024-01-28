
//#include "pch.h"
#include <iostream>
#include <omp.h>
#include <random>

// Definicion de las variables
#define N 1000 // total observaciones
#define chuck 100 // total bloques
#define mostrar 10 // total elementos visualizados

using namespace std;

void imprimeArreglo(float* d);

int main()
{
    cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Configuración del generador de números aleatorios
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 1.0);

    for (i = 0; i < N; i++)
    {
        a[i] = dis(gen) * 10.0;
        b[i] = dis(gen) * 3.7;

    }

    int pedazos = chuck;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    cout << "Imprimiendo los primeros" << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a);
    cout << "Imprimiendo los primeros" << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(b);
    cout << "Imprimiendo los primeros" << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        cout << d[x] << " - ";
    cout << endl;
}
