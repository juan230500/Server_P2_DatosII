#ifndef POBLACION_HPP
#define POBLACION_HPP

// Bibliotecas
#include <iostream>

#include "../../Game_Logic/gladiador.h"
#include "../../Data_Structures/lista.hpp"

class Poblacion
{
private:

    Gladiador* ArrayGladidadores[90]; //!<
    int tam;//!<

public:

    //! \brief Constructor
    //! \param tam
    Poblacion(int tam);

    //! \brief Ordenar
    void Ordenar();
    void print_Gladiadores();
    void print_Estadistica();
    Lista<Gladiador*> get_Mejores();

    Gladiador** get_poblacion(){
        return ArrayGladidadores;
    }

    int get_PobSize(){
        return sizeof(ArrayGladidadores)/sizeof(ArrayGladidadores[0]);
    }

};
#endif // POBLACION_HPP
