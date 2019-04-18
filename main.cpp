// Bibliotecas
#include "mainwindow.h"
#include "Pathfinding/Backtracking.hpp"
#include "Data_Structures/nodo.hpp"

#include <QApplication>
#include <iostream>
#include <algorithm>


using namespace std;

// Declaracion de funciones
void print_maze(int(*maze)[10]);
int Backtracking_test();


int main()
{

   Nodo<int> *nodo;
   nodo = new Nodo<int>(2);
   nodo->_print_Nodo();
   //Backtracking_test();
   return 0;
}

/*
 * Funcion que se encarga de  realizar una prueba al algoritmo Backtracking
 */
int Backtracking_test(){
    // Declarar la matriz que se usara como laberinto
    int (*maze)[10];
    maze = (int(*)[10]) calloc(10,sizeof(*maze));

    // Colocar 3 obstaculos aleatorios
    srand(time(NULL));
    int cnt = 0;
    vector<string> obstaculos;
    while(cnt < 30){

        int x = rand() %10;
        int y = rand() %10;
        if(x!=0 && y!=0){
            maze[x][y]=1;
            cnt++;
        }
    }

    // Mostrar la matriz
    print_maze(maze);

    Backtracking::solve_Backtracking(maze);

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
