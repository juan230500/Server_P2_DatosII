#ifndef ALG_GENETICO_HPP
#define ALG_GENETICO_HPP

// Bibbliotecas
#include <iostream>
#include "qdebug.h"

#include "poblacion.hpp"
#include "../../Objetos/gladiador.h"
#include "../../Data_Structures/lista.hpp"

using namespace std;
//! \brief Implementación del Algoritmo genético
class Gen_Engine
{
    //! \brief Método que ingresa a los nuevos individuos a la población, y elimina a los débiles.
    //! \param Poblacion: Población original.
    //! \param Next_Gen: Población de nuevos individuos.
    static void seleccion_Natural(Poblacion *Poblacion, Lista<Gladiador*> *Next_Gen);

public:

    //! @brief Constructor
    Gen_Engine();

    //! \brief Se encarga de cruzar a los dos mejores gladiadores de la población
    //! agregando 10 individuos nuevos.
    //! \param Poblacion: Población sobre la cual se aplica el cruce en algoritmo genético.
    static void Crossover(Poblacion *Poblacion);

    //! \brief Lleva a cab una mutación/inversión sobre los individuos hijos.
    //! \param Poblacion: Población sobre la cual se aplica la mutación/inversión en algoritmo genético.
    static void Mutation(Poblacion *Poblacion);


};

#endif // ALG_GENETICO_HPP
