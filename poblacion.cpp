#include "poblacion.h"

Poblacion::Poblacion(int tam)
{
    for (int i=0;i<tam;i++){
        this->ArrayGladidadores[i]=new Gladiador();
    }
    this->tam=tam;
}

void swap(Gladiador *xp, Gladiador *yp)
{
    Gladiador temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void Poblacion::Ordenar()
{
    int i, j, min_idx;
    Gladiador** arr=this->ArrayGladidadores;
    int n=this->tam;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j]->getResistencia() > arr[min_idx]->getResistencia())
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(arr[min_idx], arr[i]);
    }
}

void Poblacion::print()
{
    qDebug()<<"RESUMEN: RESISTENCIA DE POBLACION";
    Gladiador* G;
    float sum=0;
    for (int i=0;i<tam;i++){
        G=this->ArrayGladidadores[i];
        sum+=G->getResistencia();
        qDebug()<<i<<")"<<G->getResistencia();
    }
    sum/=tam;
    qDebug()<<"PROMEDIO:"<<sum;
}
