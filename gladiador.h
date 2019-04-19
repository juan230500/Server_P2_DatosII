#ifndef GLADIADOR_H
#define GLADIADOR_H

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "qdebug.h"
#include <QString>

class Gladiador
{
private:
    int unsigned short static idGlobal;
    int unsigned short id;
    int unsigned short Edad;
    int unsigned short InteligenciaEmocional; //coeficiente
    int unsigned short CondicionFisica; //Test de Ruffier
    int unsigned short FuerzaTroncoSuperior; //Newtons
    int unsigned short FuerzaTroncoInferior; //Newtons

    int Resistencia; //Vida

    int ProbabilidadSupervivencia;
    int GeneracionesSupervivencia;
public:
    Gladiador();

    Gladiador(int unsigned short Edad,
    int unsigned short InteligenciaEmocional,
    int unsigned short CondicionFisica,
    int unsigned short FuerzaTroncoSuperior,
    int unsigned short FuerzaTroncoInferior);

    void print();
    Gladiador* operator+(const Gladiador& b);

    unsigned short getEdad() const;
    void setEdad(unsigned short value);
    unsigned short getInteligenciaEmocional() const;
    void setInteligenciaEmocional(unsigned short value);
    unsigned short getCondicionFisica() const;
    void setCondicionFisica(unsigned short value);
    unsigned short getFuerzaTroncoSuperior() const;
    void setFuerzaTroncoSuperior(unsigned short value);
    unsigned short getFuerzaTroncoInferior() const;
    void setFuerzaTroncoInferior(unsigned short value);
};

#endif // GLADIADOR_H
