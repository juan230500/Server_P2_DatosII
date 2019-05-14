#ifndef TABLERO_H
#define TABLERO_H

// Bibliotecas
#include <QString>
#include <iostream>
#include "qdebug.h"

using namespace std;

//! \brief Implementacion de la Zona de Intimidacion mediante un tablero
class Tablero
{
private:

    //!< String que muestra los obstaculos que existen en la Zona.
    string obstaculos;
public:

    int (*Maze)[10];//!< Zona con unicamente las posiciones de los obstaculos
    int (*ArrayDatos)[10]; //!< Zona con los valores y rango de ataque de la Zona.

    //! \brief Constructor
    Tablero();

    //! \brief Coloca un nuevo obstaculo de tipo N, en la fila x, columna y
    //! \param id
    //! \param fila
    //! \param columna
    void ColocarObstaculo(int id, int fila, int columna);

    //! \brief Limpia la Zona colocando todas las casillas a 0
    void Limpiar();

    //! \brief Retorna el String con los obtaculos de la Zona
    string get_obstaculos(){
        return this->obstaculos;
    }

    void Print();

};

#endif // TABLERO_H
