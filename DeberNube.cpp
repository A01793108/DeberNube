
//#include "pch.h"
#include <iostream>
#include <omp.h>
#include <random>

// Definicion de las variables
#define N 1000 // total observaciones
#define chuck 100 // total bloques
#define mostrar 10 // total elementos visualizados

using namespace std; // permite omitir la abreviacion standar::std

void imprimeArreglo(float* d); // declaramos la funcion que imprmiran los mensajes

// construimos el programa de sumatoria en paralelo
int main()
{
    cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N]; // declaramos las variables donde alojaremos los resultados
    int i;

    // Configuración del generador de números aleatorios
    random_device rd; 
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0, 1.0);

    // asignamos valores aleatorios a cada elemento de a y b de los 1000
    // lo multiplicamos para una constate para que los valores sean mayores a 1
    for (i = 0; i < N; i++)
    {
        a[i] = dis(gen) * 10.0;
        b[i] = dis(gen) * 3.7;

    }

    // inicialia los pedazos con los se separaran los 1000 elementos
    int pedazos = chuck;

    // Iniciamos una región paralela con la directiva OpenMP parallel for.
    // shared(a, b, c): Indica que las variables a, b, y c son compartidas entre los hilos.
    // private(i): Indica que cada hilo debe tener su propia copia privada de la variable i.
    // schedule(static, pedazos): Especifica la planificación estática con bloques de tamaño pedazos.
    #pragma omp parallel for shared(a, b, c) private(i) schedule(static, pedazos)
    for (int i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimeArreglo(b);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        cout << d[x] << " - ";
    cout << endl;
}
