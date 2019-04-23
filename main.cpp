// Bibliotecas
#include "mainwindow.h"
#include "Pathfinding/Backtracking.hpp"
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
int A_star_test();
void lista_test();

typedef pair<int,int> Pair;
int main()
{
   //lista_test();
   cout<<"Backtracking:";
   Backtracking_test();

   cout<<"A*:";
   A_star_test();
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

    Backtracking* solver = new Backtracking();
    string my_path = solver->Backtracking_Search(maze);
    //print_maze(maze);
    delete(solver);
    cout<<my_path<<endl;
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

// Función que ejecuta el algoritmo A*
int A_star_test(){

    // Declarar un laberinto
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

    // Ejecutar el algoritmo A*
    A_star* solver = new A_star();
    solver->A_star_Search(maze,make_pair(0,0));

    // Obtener la ruta como String
    string my_Path = solver->get_Path();
    delete(solver);

    // Muestra en consola la ruta encontrada
    cout<<my_Path<<endl;
    return 0;
}
