#ifndef TABLERO_H
#define TABLERO_H
#include <QString>
#include "qdebug.h"


class Tablero
{
private:
    int ArrayDatos[10][10]={{0}};
public:
    void ColocarObstaculo(int id, int fila, int columna);
    void Limpiar();
    void Print();
    Tablero();
};

#endif // TABLERO_H
