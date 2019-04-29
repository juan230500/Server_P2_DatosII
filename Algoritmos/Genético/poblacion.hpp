#ifndef POBLACION_HPP
#define POBLACION_HPP

// Bibliotecas
#include <iostream>
#include "../../Objetos/gladiador.h"

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
    Gladiador* get_mejor_Gladiador();

    Gladiador** get_poblacion(){
        return ArrayGladidadores;
    }

    int get_PobSize(){
        return sizeof(ArrayGladidadores)/sizeof(ArrayGladidadores[0]);
    }

};
#endif // POBLACION_HPP
