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
    unsigned short int static idGlobal;
    unsigned short int id;
    unsigned short int Edad;
    unsigned short int InteligenciaEmocional; //coeficiente
    unsigned short int CondicionFisica; //Test de Ruffier
    unsigned short int FuerzaTroncoSuperior; //Newtons
    unsigned short int FuerzaTroncoInferior; //Newtons

    unsigned short int Resistencia; //Vida

    unsigned short int ProbabilidadSupervivencia;
    unsigned short int GeneracionesSupervivencia;
public:
    Gladiador();

    Gladiador(unsigned short int Edad,
    unsigned short int InteligenciaEmocional,
    unsigned short int CondicionFisica,
    unsigned short int FuerzaTroncoSuperior,
    unsigned short int FuerzaTroncoInferior);

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
    unsigned short getResistencia() const;
    void setResistencia(unsigned short value);
};

#endif // GLADIADOR_H
