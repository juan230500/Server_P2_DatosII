
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

using namespace std;

/*-------------------- NOTA ----------------------------
  Como convencion usamos las casillas disponibles como 0
  y las casillas con obtaculo como 1
  -----------------------------------------------------*/

//!
//! \brief The Pathfinding class
//!
class Backtracking{

    string _path;//!< Ruta que encuentra el algoritmo

    int _time; //!< Tiempo que tarda el algoritmo en encontrar la ruta

    //!
    //! \brief is_safe
    //! \param x
    //! \param y
    //! \return
    //!
    bool is_safe_Bt(int (*maze)[10],int x, int y);

    //!
    //! \brief print_solution
    //! \param path
    //!
    void trace_path(Lista<string> *path);

public:

    //! @brief Constructor
    Backtracking();

    //! @brief Implementacion del algoritmo de busqueda Backtracking.
    //! @param[in] maze: Laberinto sobre el que se realiza la busqueda.
    //! @return[out] Ruta encontrada para salir del laberinto.
   string Backtracking_Search(int (*maze)[10]);

    //!
    //! \brief solve_Bt
    //! \param x
    //! \param y
    //! \param path
    //! \return
    //!
    bool Backtracking_Solver(int (*maze)[10], int x, int y, Lista<string> *path);

    //!
    //! \brief get_Time
    //! \return
    //!
    int get_Time(){
        return this->_time;
    }

};
