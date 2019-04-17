#include "mainwindow.h"
#include "Pathfinding/Backtracking.hpp"
#include <QApplication>
#include <iostream>
#include <algorithm>


using namespace std;

void print_maze(int(*maze)[10]);

int main()
{
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
        if(x!=0 && y!=0)
            maze[x][y]=1;
            cnt++;
    }

    // Mostrar la matriz
    print_maze(maze);

    Backtracking::solve_Backtracking(maze);

    print_maze(maze);
    return 0;
}

void print_maze(int(*maze)[10]){
    for(int row=0;row<10;row++){
      cout<<"{ ";
      for(int col=0;col<10;col++){
        cout<<maze[row][col]<<" ";
      }
      cout<<" }"<<endl;
    }
}
