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

    unsigned short int id; //!< Identificación del gladiador.
    unsigned short int Edad; //!< Edad del gladiador.
    unsigned short int InteligenciaEmocional; //!< coeficiente IQ del gladiador.
    unsigned short int CondicionFisica; //!< Test de Ruffier. Condicón física del gladiador.
    unsigned short int FuerzaTroncoSuperior; //!< Newtons. Fuerza superior del gladiador.
    unsigned short int FuerzaTroncoInferior; //!< Newtons. Fuerza inferior del gladiador.

    unsigned short int Resistencia; //!< Medida de resistencia, calculada segun los parametros anteriores.

    int ProbabilidadSupervivencia; //!< Probabilidad de supervivencia para la sgte generacion.
    int GeneracionesSupervivencia; //!< Generaciones aproximadas de supervivencia del individuo.

public:

    unsigned short int static idGlobal; //!< ID del gladiador

    void static resetIdGlobal(){
        idGlobal = 0;
    }

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

    //! \brief Sobrecarga del operador + para el cruce entre Gladiadores
    //! \param Gladiador: Gladiador con el que se cruzara el individuo.
    //! \return Un nuevo gladiador con la mezcla de las caracteristicas de ambos Padres
    Gladiador* operator+(const Gladiador& b);

    //! \brief Realiza un calculo de la resistencia del individuo
    void calc_Resistencia();

    //! \brief Calcula la probabilidad de supervivencia del individuo
    //! \param num_obstaculos : Cantidad de obstaculos que hay en la Zona de Intimidacion
    int calc_ProbSupervivencia(int num_obstaculos);

    //! \brief Calcula las generaciones aproximadas que el individuo permanecera en la poblacion
    //! \param pos
    int calc_GenSupervivencia(int pos);

    void print();

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
