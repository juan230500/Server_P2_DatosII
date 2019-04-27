#ifndef POBLACION_H
#define POBLACION_H
#include "Objetos/gladiador.h"

class Poblacion
{
private:
    Gladiador* ArrayGladidadores[90];
    int tam;
public:
    Poblacion(int tam);
    void Ordenar();
    void print();
};

#endif // POBLACION_H
