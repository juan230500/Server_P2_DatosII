#ifndef NODO_H
#define NODO_H

// Bibliotecas
#include <iostream>

using namespace std;

//! @abstract Nodo de tipo generico para una Lista enlazada
template <class T>
class Nodo
{
    T _dato; //!< Dato T que almacena el nodo
    Nodo* _next; //!< Puntero al sgte nodo de la lista

public:

    //! @brief Constructor
    //! @param [in]dato: Dato que almacena el nodo
    Nodo();

    //! @brief
    //! @param
    void set_Nodo(T dato);

    //! @brief Imprime la informacion del nodo en consola
    void _print_Nodo();
};

#include "nodo_def.h"

#endif // NODO_H
