#include "Backtracking.hpp"

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/
Backtracking::Backtracking(){

}

/* -------------------------------
 *          METODOS UTIL
 * -------------------------------*/

// Metodo inicial de la funcion
string Backtracking::Backtracking_Search(int (*maze)[10],int x, int y){

    // Se realiza una marca al inicio del algoritmo
    time_point<Clock> start = Clock::now();
    Lista<string> *path = new Lista<string>();
    this->_path = "";
    if(!Backtracking_Solver(maze,x,y,path)){
        return this->_path;
    }
    // Se realiza una marca al final del algoritmo
    time_point<Clock> end = Clock::now();

    microseconds time = duration_cast<microseconds>(end - start);
    this->_time = time.count(); // Dado en us
    return this->_path;
}


// Metodo recursivo de Backtracking
bool Backtracking::Backtracking_Solver(int (*maze)[10], int x, int y, Lista<string> *path){



    // Si (x,y) es la salida return true
        if(x == 9 && y == 9 && is_safe_Bt(maze,x,y))
        {
            // Se agrega (x,y) al path
            path->push_back(to_string(x) + to_string(y) + "-");
            //maze[x][y] = 5;

            // Se convierte la lista al string
            trace_path(path);
            return true;
        }

        // Verifica si maze[x][y] es una posicion valida
        if(is_safe_Bt(maze,x,y))
        {
            cout<<""; // Time
            cout<<""; // Time

            // Marcar x,y como parte del path
            path->push_back(to_string(x)+to_string(y)+"-" );
            //maze[x][y] = 5;

            // Moverse hacia adelante
            if (Backtracking_Solver(maze, x, y+1, path) == true)
                return true;

            /* Si moverse hacia el frente no es una solucion
               entonces intenta moverse hacia abajo  */
            if (Backtracking_Solver(maze, x+1, y, path) == true)
                return true;

            /* Si moverse abajo el frente no es una solucion
               entonces intenta moverse hacia arriba  */
            if (Backtracking_Solver(maze, x-1, y, path) == true)
                return true;


            /* Si ninguna de estas lleva a una solucion entonces
               intenta moverse en diagonal hacia abajo */
            if(Backtracking_Solver(maze,x+1,y+1,path)){
                return true;
            }

            /* Si ninguna de estas lleva a una solucion entonces
               intenta moverse en diagonal hacia arriba */
            if(Backtracking_Solver(maze,x-1,y+1,path)){
                return true;
            }

            /* Si ninguna de estas lleva a una solucion entonces
               intenta moverse en hacia atras */
            if(Backtracking_Solver(maze,x,y-1,path)){
                return true;
            }

            /* Si ninguno de estos movimientos, lleva a una solucion, realizar BACKTRACK:
                desmarcar x,y como parte de la solucion */
            path->pop_back();
            //maze[x][y] = 0;
            return false;
        }

        return false;
}

/* -------------------------------
 *          METODOS EXTRA
 * -------------------------------*/

// Metodo que valida si la posicion es valida
bool Backtracking::is_safe_Bt(int (*maze)[10],int x, int y){
    // Si (x,y) se encuentra fuera del laberinto return False
    if(x >= 0 && x < 10 && y >= 0 && y < 10 && maze[x][y] == 0){
        return true;
    }
    return false;
}

// Metodo que muestra el path en consola
void Backtracking::trace_path(Lista<string> *path){
    while(!path->empty()){
        _path += path->pop_front();
    }
    //cout<<_path<<endl;
}
