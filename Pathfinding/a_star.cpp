#include "a_star.hpp"

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/
A_star::A_star()
{

}

/* -------------------------------
 *          METODOS UTIL
 * -------------------------------*/
bool A_star::pos_valida(int row, int col){

}

bool A_star::pos_bloqueada(int value){

}

bool A_star::es_destino(int row, int col){

}

int A_star::calc_H(int row, int col){

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


void A_star::A_star_Search(int maze[][10], pos src){

}

void A_star::A_star_Solver(int maze[][10], pos src){

}

