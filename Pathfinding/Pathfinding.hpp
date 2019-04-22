
// Bibliotecas
#include <iostream>
#include <vector>
#include <string>
#include "../Data_Structures/lista.hpp"

using namespace std;

/*-------------------- NOTA ----------------------------
  Como convencion usamos las casillas disponibles como 0
  y las casillas con obtaculo como 1
  -----------------------------------------------------*/

//!
//! \brief The Pathfinding class
//!
class Pathfinding{

    //!
    //! \brief is_safe
    //! \param x
    //! \param y
    //! \return
    //!
    static bool is_safe_Bt(int (*maze)[10],int x, int y);

    //!
    //! \brief print_solution
    //! \param path
    //!
    static void print_solution(Lista<string> *path);

public:

    //! @brief Constructor
    Pathfinding();

    //! @brief Implementacion del algoritmo de busqueda Backtracking.
    //! @param[in] maze: Laberinto sobre el que se realiza la busqueda.
    //! @return[out] Ruta encontrada para salir del laberinto.
    static string Backtracking(int (*maze)[10]);

    //!
    //! \brief solve_Bt
    //! \param x
    //! \param y
    //! \param path
    //! \return
    //!
    static bool solve_Bt(int (*maze)[10], int x, int y, Lista<string> *path);

    static void A_star();


};
