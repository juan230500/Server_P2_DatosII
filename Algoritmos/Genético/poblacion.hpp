#ifndef POBLACION_HPP
#define POBLACION_HPP

// Bibliotecas
#include <iostream>

#include "../../Game_Logic/gladiador.h"
#include "../../Data_Structures/lista.hpp"

#define TAM 90

//! Implementación de una población de Gladiadores
class Poblacion
{
private:

    Gladiador* ArrayGladidadores[TAM]; //!< Array que almacena los gladiadores
    float tam;//!< Tamaño de la población
    float res_prom; //!< Promedio de la Resistencia de la Población

    //! \brief Calcula el promedio de la resistencia de la Población
    void calc_prom();

public:

    //! \brief Constructor
    //! \param tam
    Poblacion(int tam);

    //! \brief Ordenar la población de mayor a menor Resistencia
    void Ordenar();

    //! \brief Muestra los gladiadores de la población en consola
    void print_Gladiadores();

    //! \brief Muestra la estadística de Resistencia y porcentajes
    void print_Estadistica(int generacion,int N);

    //! \brief Retorna una lista con los cuatro mejores gladiadores de la población
    Lista<Gladiador*> get_Mejores();
    //! \brief Retorna al mejor gladiador de la población (El de Resistencia más alta)
    Gladiador* get_Mejor(){
        return ArrayGladidadores[0];
    }

    //! \brief Retorna la población
    Gladiador** get_poblacion(){
        return ArrayGladidadores;
    }

    //! \brief Retorna el tamaño de la población
    int get_PobSize(){
        return sizeof(ArrayGladidadores)/sizeof(ArrayGladidadores[0]);
    }

    //! \brief Retorna el promedio de Resistencia de la Población
    float get_Prom(){
        calc_prom();
        return res_prom;
    }

};
#endif // POBLACION_HPP
