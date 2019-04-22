// Bibliotecas
#include "mainwindow.h"
#include "Pathfinding/Pathfinding.hpp"
#include "Pathfinding/a_star.hpp"
#include "Data_Structures/nodo.hpp"
#include "Data_Structures/lista.hpp"

#include <QApplication>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

// Declaracion de funciones
void print_maze(int(*maze)[10]);
int Backtracking_test();
void lista_test();

typedef pair<int,int> Pair;
int main()
{
   //lista_test();
   //Backtracking_test();
   return 0;
}

/*
 * Funcion que se encarga de  realizar una prueba al algoritmo Backtracking
 */
int Backtracking_test(){
    // Declarar la matriz que se usara como laberinto
    int maze[][10] = { {0,0,1,0,0,0,0,0,0,0},
                       {0,0,1,0,0,0,0,0,0,0},
                       {0,0,1,0,0,0,0,0,0,0},
                       {0,1,0,0,0,1,1,0,0,0},
                       {0,0,1,0,0,0,1,0,0,0},
                       {0,0,0,0,0,0,0,0,0,1},
                       {0,0,0,1,0,0,0,0,0,1},
                       {0,0,0,1,0,0,0,0,0,1},
                       {0,0,0,1,0,0,1,1,0,0},
                       {0,0,0,1,0,0,0,1,0,0}};

    // Mostrar la matriz
    print_maze(maze);

    Pathfinding::Backtracking(maze);

    print_maze(maze);
    return 0;
}

// Imprime el laberinto en la consola
void print_maze(int(*maze)[10]){
    for(int row=0;row<10;row++){
      cout<<"{ ";
      for(int col=0;col<10;col++){
        cout<<maze[row][col]<<" ";
      }
      cout<<" }"<<endl;
    }
}


