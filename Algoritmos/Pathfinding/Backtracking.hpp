#ifndef BACKTRACKING_H
#define BACKTRACKING_H
// Bibliotecas
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "../../Data_Structures/lista.hpp"

// Esto se realiza para conocer cuánto tiempo le toma al algoritmo encontrar la ruta
using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::microseconds;

#define ROW 10
#define COL 10

using namespace std;

/*-------------------- NOTA ----------------------------
  Como convencion usamos las casillas disponibles como 0
  y las casillas con obtaculo como 1
  -----------------------------------------------------*/

//!
//! \brief Algoritmo de PathFinding Backtracking
//!
class Backtracking{

    string _path;//!< Ruta que encuentra el algoritmo

    int _time; //!< Tiempo que tarda el algoritmo en encontrar la ruta


    //! \brief Función que determina si la posición en el tablero es permitida
    //! \param [in] x : Posición x de la casilla
    //! \param [in] y : Posición y de la casilla
    //! \return
    bool is_safe_Bt(int (*maze)[COL],int x, int y);

    //! \brief Convierte el path de lista a string para su uso en JSON y Recorridos
    //! \param path: Lista con las posiciones que componen la ruta a la salida
    void trace_path(Lista<string> *path);

public:

    //! @brief Constructor
    Backtracking();

    //! @brief Implementacion del algoritmo de busqueda Backtracking.
    //! @param[in] maze: Laberinto sobre el que se realiza la busqueda.
    //! @return[out] Ruta encontrada para salir del laberinto.
    string Backtracking_Search(int (*maze)[COL],int x, int y);


    //! \brief Función recursiva que ejecuta el Backtracking
    //! \param [in] x : Posición x de la casilla
    //! \param [in] y : Posición y de la casilla
    //! \param [in] path : Lista con las posiciones que componen la ruta a la salida
    bool Backtracking_Solver(int (*maze)[COL], int x, int y, Lista<string> *path);

    //! \brief Retorna el tiempo que se tardó en encontrar la ruta de salida
    int get_Time(){
        return this->_time;
    }

    //! \brief Limpia el path para volver a utilizarlo nuevamente
    void clean_Path(){
        _path = "";
    }

};

#endif
