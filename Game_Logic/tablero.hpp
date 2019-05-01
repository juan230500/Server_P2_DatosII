#ifndef TABLERO_H
#define TABLERO_H

// Bibliotecas
#include <QString>
#include <iostream>
#include "qdebug.h"

using namespace std;
class Tablero
{
private:
    int (*ArrayDatos)[10];
    string obstaculos;
public:

    int (*Maze)[10];
    void ColocarObstaculo(int id, int fila, int columna);
    void Limpiar();
    void Print();
    string get_obstaculos(){
        return this->obstaculos;
    }
    Tablero();

};

#endif // TABLERO_H
