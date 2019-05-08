#ifndef GLADIADOR_H
#define GLADIADOR_H

// Bibliotecas
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>
#include <bitset>
#include "qdebug.h"
#include <QString>
#include <boost/numeric/conversion/cast.hpp>

using namespace std;
//! Un gladiador es el CROMOSOMA del ALGORITMO GENETICO
class Gladiador
{
private:

    // UNSIGNED solo guardará valores positivos
    // SHORT


    unsigned short int id; // Identificación del gladiador
    unsigned short int Edad; // Edad del gladiador
    unsigned short int InteligenciaEmocional; // coeficiente IQ del gladiador
    unsigned short int CondicionFisica; //Test de Ruffier. Condicón física del gladiador
    unsigned short int FuerzaTroncoSuperior; //Newtons. Fuerza superior del gladiador
    unsigned short int FuerzaTroncoInferior; //Newtons.

    unsigned short int Resistencia; //Vida

    int ProbabilidadSupervivencia;
    int GeneracionesSupervivencia;

public:
    unsigned short int static idGlobal;

    //! @brief Constructor
    Gladiador();

    //! \brief Constructor
    //! \param Edad
    //! \param InteligenciaEmocional
    //! \param CondicionFisica
    //! \param FuerzaTroncoSuperior
    //! \param FuerzaTroncoInferior
    Gladiador(unsigned short int Edad,
    unsigned short int InteligenciaEmocional,
    unsigned short int CondicionFisica,
    unsigned short int FuerzaTroncoSuperior,
    unsigned short int FuerzaTroncoInferior);

    /***************************************
     *            METODOS UTIL             *
     ***************************************/

    void print();

    Gladiador* operator+(const Gladiador& b);

    void calc_Resistencia();

    int calc_ProbSupervivencia(int num_obstaculos);

    int calc_GenSupervivencia(int pos);

    /***************************************
     *         GETTERS & SETTER            *
     ***************************************/
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

    unsigned short getId() const{
        return id;
    }
};

#endif // GLADIADOR_H
