#ifndef A_STAR_H
#define A_STAR_H

// Bibliotecas
#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <chrono>

#include "../../Data_Structures/lista.hpp"

// Esto se realiza para conocer cuánto tiempo le toma al algoritmo encontrar la ruta
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::microseconds;

using namespace std;

#define ROW 10
#define COL 10
#define HOR 10
#define VERT 10
#define DIAG 14

// Crear una tupla int,int
typedef pair<int,int> pos; //!< Guarda la posición <i,j>

// Crear una tupla int,pair<int,int>
typedef pair<int,pair<int,int>> pos_info; //!< Guarda el valor f <f,<i,j>>

// Se crea un struct para almacenar los parametros necesarios (casilla)
//!
//! \brief Celda struct. Implementación de una celda del laberinto.
//! Contiene la fila y columna de su padre y su valor de f,g y h.
//!
struct Celda{
    int padre_i,padre_j;
    int F,G,H;
};

using namespace std;

//!
//! \brief A_star. Implementación del algoritmo de búsqueda A*
//!
class A_star
{

    string _path;//!< Ruta encontrada en formato string

    int _time; //!< Tiempo que tarda el algoritmo en encontrar la ruta

    //!
    //! \brief pos_valida. Recibe la fila y col de una celda para indicar si es un posición permitida.
    //! \param row: fila de la celda.
    //! \param col: columna de la celda.
    //! \return true si la celda es válida, false si no lo es.
    //!
    bool pos_valida(int row,int col);

    //!
    //! \brief pos_bloqueada. Recibe un valor para saber si es un obstáculo.
    //! \param value: Valor que indica si es un obstáculo.
    //! \return true si está bloqueada y false si no lo está.
    //!
    bool pos_desbloqueada(int value);

    //!
    //! \brief es_destino. Indica si una celda dada es el final del laberinto.
    //! \param row: fila de la celda.
    //! \param col: columna de la celda.
    //! \return true si la celda es el final, false si no lo es.
    //!
    bool es_destino(int row,int col);

    //!
    //! \brief calc_H. Función que calcula el parametro H de una celd con el método Mahattan
    //! \param row: fila de la celda.
    //! \param col: columna de la celda.
    //! \return El valor H de la celda.
    //!
    int calc_H(int row, int col);

    //!
    //! \brief trace_path. Método encargado de mostrar la ruta encontrada
    //! \param cell_maze: Matriz que implementa el laberinto de celdas
    //!
    void trace_path(Celda cell_maze[][10]);

public:

    //! \brief A_star constructor
    //!
    A_star();

    //!
    //! \brief A_star_Search. Metodo inicial que se encarga de llamar al método de búqueda recursivo.
    //!
    void A_star_Search(int maze[][COL],pos src);

    //!
    //! \brief A_star_Solver. Método auxiliar para resolver el laberinto.
    //!
    void A_star_Solver(int int_maze[][COL],Celda maze[][COL],pos src,bool lista_cerrada[ROW][COL]);

    //!
    //! \brief get_Path. Función que retorna el path en formato "ij-i1j1-i2j2-..."
    //! \return Path en formato string
    //!
    string get_Path();

    int get_Time(){
        return this->_time;
    }
};

#endif // A_STAR_H
