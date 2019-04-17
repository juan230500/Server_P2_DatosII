
// Bibliotecas
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*-------------------- NOTA ----------------------------
  Como convencion usamos las casillas disponibles como 0
  y las casillas con obtaculo como 1
  -----------------------------------------------------*/

class Backtracking{
   static bool is_safe(int (*maze)[10],int x, int y);

   static void print_solution(vector<string> path);
public:

  //! @brief Constructor
  Backtracking();

  //! @brief Implementacion del algoritmo de busqueda Backtracking.
  //! @param[in] maze: Laberinto sobre el que se realiza la busqueda.
  //! @return[out] Ruta encontrada para salir del laberinto.
  static string solve_Backtracking(int (*maze)[10]);

  static bool solve_Bt_aux(int (*maze)[10], int x, int y, vector<string> path);

};
