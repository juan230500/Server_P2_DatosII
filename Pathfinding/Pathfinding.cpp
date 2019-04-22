#include "Pathfinding.hpp"

// Metodo inicial de la funcion
string Pathfinding::Backtracking(int (*maze)[10]){

    Lista<string> *path = new Lista<string>();
    if(!solve_Bt(maze,0,0,path)){
    return "False";
  }

  return "True";
}

// Metodo que valida si la posicion es valida
bool Pathfinding::is_safe_Bt(int (*maze)[10],int x, int y){
    // Si (x,y) se encuentra fuera del laberinto return False
    if(x >= 0 && x < 10 && y >= 0 && y < 10 && maze[x][y] == 0){
        return true;
    }
    return false;
}


// Metodo recursivo de Backtracking
bool Pathfinding::solve_Bt(int (*maze)[10], int x, int y, Lista<string> *path){

    cout<<"Recorriendo: "<<x<<","<<y<<endl;

    // Si (x,y) es la salida return true
        if(x == 9 && y == 9)
        {
            // Se agrega (x,y) al path
            path->push_back(to_string(x) + to_string(y) + "->");
            maze[x][y] = 5;
            print_solution(path);
            return true;
        }

        // Verifica si maze[x][y] es una posicion valida
        if(is_safe_Bt(maze,x,y))
        {
            // Marcar x,y como parte del path
            path->push_back(to_string(x) + to_string(y) + "->");
            maze[x][y] = 5;

            // Moverse hacia adelante
            if (solve_Bt(maze, x, y+1, path) == true)
                return true;

            /* Si moverse hacia el frente no es una solucion
               entonces intenta moverse hacia abajo  */
            if (solve_Bt(maze, x+1, y, path) == true)
                return true;

            /* Si ninguna de estas lleva a una solucion entonces
               intenta moverse en diagonal */
            if(solve_Bt(maze,x+1,y+1,path)){
                return true;
            }

            /* Si ninguno de estos movimientos, lleva a una solucion, realizar BACKTRACK:
                desmarcar x,y como parte de la solucion */
            path->pop_back();
            maze[x][y] = 0;
            return false;
        }

        return false;
}

// Metodo que muestra el path en consola
void Pathfinding::print_solution(Lista<string> *path){
    for(int i = 0; i < path->size();i++){
        cout<<path->get_index(i);
    }
    cout<<endl;
}
