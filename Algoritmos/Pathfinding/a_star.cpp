#include "a_star.hpp"

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/
A_star::A_star(){

}

/* -------------------------------
 *          METODOS UTIL
 * -------------------------------*/
// Revisa si la posición está en el rango
bool A_star::pos_valida(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Revisa la posición es un obstáculo
bool A_star::pos_desbloqueada(int value){
    /*
     * COMO ACUERDO, LA POSICION DISPONIBLE ES UN 0
     */
    return value == 0;
}

// Indica si la posición es el destino
bool A_star::es_destino(int row, int col){
    return (row == 9) && (col==9);
}

// Calcula el valor de H para el A* con el método Mahattan
int A_star::calc_H(int row, int col){
    return abs(9-row)+abs(9-col);
}

/* -------------------------------
 *          METODOS BUSQUEDA
 * -------------------------------*/
/*
        Generating all the 8 successor of this cell

            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E

        Cell-->Popped Cell (i, j)
        N -->  North       (i-1, j)
        S -->  South       (i+1, j)
        E -->  East        (i, j+1)
        W -->  West           (i, j-1)
        N.E--> North-East  (i-1, j+1)
        N.W--> North-West  (i-1, j-1)
        S.E--> South-East  (i+1, j+1)
        S.W--> South-West  (i+1, j-1)

 source: https://www.geeksforgeeks.org/a-search-algorithm/*/

// Método encargado de inicializar la matriz de celdas a partir de una numérica.
// Además inicializa la lista de celdas visitadas.
void A_star::A_star_Search(int maze[][COL], int x, int y){

    pos src = make_pair(x,y);
    if(!pos_valida(src.first,src.second)){
        cout<<"Posición inicial no válida!"<<endl;
        return;
    }

    // Se implementa la lista de celdas no visitadas
    bool lista_cerrada[ROW][COL];
    memset(lista_cerrada,false,sizeof(lista_cerrada));

    // Se implementa la matriz de celdas
    Celda cell_maze[ROW][COL];

    // Setear los valores iniciales a la matriz
    for(int i = 0; i < ROW;i++){
        for(int j = 0; j < COL; j++){
            cell_maze[i][j].F = INT_MAX;
            cell_maze[i][j].G = INT_MAX;
            cell_maze[i][j].H = INT_MAX;

            cell_maze[i][j].padre_i = -1;
            cell_maze[i][j].padre_j = -1;
        }
    }

    // Se inicializan los parámetros del nodo inicial
    int i = src.first,j = src.second;

    cell_maze[i][j].F = 0;
    cell_maze[i][j].G = 0;
    cell_maze[i][j].H = 0;

    cell_maze[i][j].padre_i = i;
    cell_maze[i][j].padre_j = j;

    // Se ejecuta la función de búsqueda
    A_star_Solver(maze,cell_maze,src,lista_cerrada);
}

void A_star::A_star_Solver(int int_maze[][COL],Celda cell_maze[][COL], pos src,bool lista_cerrada[ROW][COL]){

    time_point<Clock> start = Clock::now();

    // Se crea una lista que almacenará las tuplas <f,<i,j>>, con F = G+H
    Lista<pos_info> *lista_abierta = new Lista<pos_info>();

    lista_abierta->push_back(make_pair(0,make_pair(src.first,src.second)));

    bool foundDest = false;

    while (!(lista_abierta->empty())) {


        // Se encuentra el index del nodo con menor F de la lista
        int f_menor= lista_abierta->get_index(0).first, index = 0;

        for(int i = 0; i < lista_abierta->size();i++){

            int f_actual= lista_abierta->get_index(i).first;

            // Si el valor de F es menor que el que se tiene, realiza el cambio
            if(f_menor > f_actual){
                index = i;
            }
        }

        // Se extrae el nodo con el menor F
        pos_info p = lista_abierta->remove_at(index);

        // Se añade este vértice a la lista cerrada
        int i = p.second.first,j = p.second.second;
        lista_cerrada[i][j] = true;

        // Para almacenar los valores temporales de F,G y H
        int tmp_F,tmp_G,tmp_H;

        /*Se realizarán las búsquedas de los 8 posibles sucesores*/

        /* -------------------------------
         *        MOVIMIENTOS H V
         * -------------------------------*/

        // -------------------------- NORTE ------------------------------
        if(pos_valida(i-1,j)){

            if(es_destino(i-1,j)){
                // Set el padre de la celda de destino
                cell_maze[i-1][j].padre_i = i;
                cell_maze[i-1][j].padre_j = j;
                foundDest = true;
                trace_path(cell_maze);
                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us
                return;

            }else if(!lista_cerrada[i-1][j] &&
                     pos_desbloqueada(int_maze[i-1][j])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + HOR;
                tmp_H = calc_H(i-1,j);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i-1][j].F == INT_MAX || cell_maze[i-1][j].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i-1,j));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i-1][j].F = tmp_F;
                    cell_maze[i-1][j].G = tmp_G;
                    cell_maze[i-1][j].H = tmp_H;
                    cell_maze[i-1][j].padre_i = i;
                    cell_maze[i-1][j].padre_j = j;
                }
            }
        }

        // -------------------------- SUR ------------------------------
        if(pos_valida(i+1,j)){

            if(es_destino(i+1,j)){
                // Set el padre de la celda de destino
                cell_maze[i+1][j].padre_i = i;
                cell_maze[i+1][j].padre_j = j;
                trace_path(cell_maze);
                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us
                foundDest = true;
                return;

            }else if(!lista_cerrada[i+1][j] &&
                     pos_desbloqueada(int_maze[i+1][j])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + HOR;
                tmp_H = calc_H(i+1,j);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i+1][j].F == INT_MAX || cell_maze[i+1][j].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i+1,j));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i+1][j].F = tmp_F;
                    cell_maze[i+1][j].G = tmp_G;
                    cell_maze[i+1][j].H = tmp_H;
                    cell_maze[i+1][j].padre_i = i;
                    cell_maze[i+1][j].padre_j = j;
                }

            }
        }

        // -------------------------- ESTE ------------------------------
        if(pos_valida(i,j+1)){

            if(es_destino(i,j+1)){
                // Set el padre de la celda de destino
                cell_maze[i][j+1].padre_i = i;
                cell_maze[i][j+1].padre_j = j;
                trace_path(cell_maze);
                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;

            }else if(!lista_cerrada[i][j+1] &&
                     pos_desbloqueada(int_maze[i][j+1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + VERT;
                tmp_H = calc_H(i,j+1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i][j+1].F == INT_MAX || cell_maze[i][j+1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i,j+1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i][j+1].F = tmp_F;
                    cell_maze[i][j+1].G = tmp_G;
                    cell_maze[i][j+1].H = tmp_H;
                    cell_maze[i][j+1].padre_i = i;
                    cell_maze[i][j+1].padre_j = j;
                }
            }
        }

        // ------------------------- OESTE ------------------------------
        if(pos_valida(i,j-1)){

            if(es_destino(i,j-1)){
                // Set el padre de la celda de destino
                cell_maze[i][j-1].padre_i = i;
                cell_maze[i][j-1].padre_j = j;
                trace_path(cell_maze);

                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;
            }else if(!lista_cerrada[i][j-1] &&
                     pos_desbloqueada(int_maze[i][j-1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + VERT;
                tmp_H = calc_H(i,j-1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i][j-1].F == INT_MAX || cell_maze[i][j-1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i,j-1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i][j-1].F = tmp_F;
                    cell_maze[i][j-1].G = tmp_G;
                    cell_maze[i][j-1].H = tmp_H;
                    cell_maze[i][j-1].padre_i = i;
                    cell_maze[i][j-1].padre_j = j;
                }
            }
        }

        /* -------------------------------
         *        MOVIMIENTOS DIAG
         * -------------------------------*/

        // ------------------------ NOR-ESTE ----------------------------
        if(pos_valida(i-1,j+1)){

            if(es_destino(i-1,j+1)){
                // Set el padre de la celda de destino
                cell_maze[i-1][j+1].padre_i = i;
                cell_maze[i-1][j+1].padre_j = j;
                trace_path(cell_maze);

                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;

            }else if(!lista_cerrada[i-1][j+1] &&
                     pos_desbloqueada(int_maze[i-1][j+1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + DIAG;
                tmp_H = calc_H(i-1,j+1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i-1][j+1].F == INT_MAX || cell_maze[i-1][j+1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i-1,j+1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i-1][j+1].F = tmp_F;
                    cell_maze[i-1][j+1].G = tmp_G;
                    cell_maze[i-1][j+1].H = tmp_H;
                    cell_maze[i-1][j+1].padre_i = i;
                    cell_maze[i-1][j+1].padre_j = j;
                }
            }
        }

        // ------------------------ NOR_OESTE ---------------------------
        if(pos_valida(i-1,j-1)){

            if(es_destino(i-1,j-1)){
                // Set el padre de la celda de destino
                cell_maze[i-1][j-1].padre_i = i;
                cell_maze[i-1][j-1].padre_j = j;
                trace_path(cell_maze);
                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;

            }else if(!lista_cerrada[i-1][j-1] &&
                     pos_desbloqueada(int_maze[i-1][j-1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + DIAG;
                tmp_H = calc_H(i-1,j-1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i-1][j-1].F == INT_MAX || cell_maze[i-1][j-1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i-1,j-1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i-1][j-1].F = tmp_F;
                    cell_maze[i-1][j-1].G = tmp_G;
                    cell_maze[i-1][j-1].H = tmp_H;
                    cell_maze[i-1][j-1].padre_i = i;
                    cell_maze[i-1][j-1].padre_j = j;
                }
            }
        }

        // ----------------------- SUR- ESTE-----------------------------
        if(pos_valida(i+1,j+1)){

            if(es_destino(i+1,j+1)){
                // Set el padre de la celda de destino
                cell_maze[i+1][j+1].padre_i = i;
                cell_maze[i+1][j+1].padre_j = j;
                trace_path(cell_maze);

                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;

            }else if(!lista_cerrada[i+1][j+1] &&
                     pos_desbloqueada(int_maze[i+1][j+1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + DIAG;
                tmp_H = calc_H(i+1,j+1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i+1][j+1].F == INT_MAX || cell_maze[i+1][j+1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i+1,j+1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i+1][j+1].F = tmp_F;
                    cell_maze[i+1][j+1].G = tmp_G;
                    cell_maze[i+1][j+1].H = tmp_H;
                    cell_maze[i+1][j+1].padre_i = i;
                    cell_maze[i+1][j+1].padre_j = j;
                }
            }
        }

        // ----------------------- SUR- OESTE ---------------------------
        if(pos_valida(i+1,j-1)){

            if(es_destino(i+1,j-1)){
                // Set el padre de la celda de destino
                cell_maze[i+1][j-1].padre_i = i;
                cell_maze[i+1][j-1].padre_j = j;
                trace_path(cell_maze);

                // Se realiza una marca al final del algoritmo
                time_point<Clock> end = Clock::now();

                microseconds time = duration_cast<microseconds>(end - start);
                this->_time = time.count(); // Dado en us

                foundDest = true;
                return;

            }else if(!lista_cerrada[i+1][j-1] &&
                     pos_desbloqueada(int_maze[i+1][j-1])){

                // Calcula los "nuevos" valores F,G y H
                tmp_G = cell_maze[i][j].G + DIAG;
                tmp_H = calc_H(i+1,j-1);
                tmp_F = tmp_G + tmp_H;

                /* -----------------------------------------------------------
                 * Si no está en la lista abierta, lo añade a la lista abierta,
                 * hace a la celda actual el padre de esa celda y almacena los
                 * nuevos datos F,G y H de la celda. [f = INT_MAX]
                 *
                 * Si ya está en la lista abierta; pero el tmp_f es mejor, entonces
                 * busca encontrar un path más barato, con el F como parámetro.
                 * [F> tmp_F]
                 * -----------------------------------------------------------*/
                if(cell_maze[i+1][j-1].F == INT_MAX || cell_maze[i+1][j-1].F > tmp_F){

                    // #1. Añade el nodo a la lista abierta (si no está)
                    pos_info p = make_pair(tmp_F,make_pair(i+1,j-1));
                    if(lista_abierta->contains(p) == false){
                        lista_abierta->push_back(p);
                    }

                    // #2. Actualiza los valores de F,G y H de la celda
                    cell_maze[i+1][j-1].F = tmp_F;
                    cell_maze[i+1][j-1].G = tmp_G;
                    cell_maze[i+1][j-1].H = tmp_H;
                    cell_maze[i+1][j-1].padre_i = i;
                    cell_maze[i+1][j-1].padre_j = j;
                }
            }
        }
    }

    if(!foundDest)
        cout<<"Error al encontrar la ruta a la salida"<<endl;

    return;
}

// Método encargado de trazar la ruta una vez conocidos todos los padres de las celdas
void A_star::trace_path(Celda cell_maze[][10]){

    Lista<pos> *path = new Lista<pos>();

    int row = 9,col = 9; // La posición final es (9,9)

    // Añade las celdas que pertenecen a la ruta al "stack" (Lista LIFO)
    while (!(cell_maze[row][col].padre_i == row
             && cell_maze[row][col].padre_j == col)) {

        // Añade la celda a lista con comportamiento LIFO y hace cambios.
        path->push_front(make_pair(row,col));
        int tmp_row = cell_maze[row][col].padre_i;
        int tmp_col = cell_maze[row][col].padre_j;
        row = tmp_row;
        col = tmp_col;
    }

    path->push_front(make_pair(row,col));

    // Acomoda e inserta los elementos en la lista de salida y en el orden que se debe
    while (!path->empty()) {
        pos p = path->pop_front();
        this->_path += to_string(p.first)+ to_string(p.second) + "-" ;
    }

    //cout<<this->_path<<endl;

}

// Retorna la ruta en formato string
string A_star::get_Path(){
    return this->_path;
}
