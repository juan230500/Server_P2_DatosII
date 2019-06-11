// Bibliotecas
#include "Algoritmos/Pathfinding/Backtracking.hpp"
#include "Algoritmos/Pathfinding/a_star.hpp"
#include "Data_Structures/nodo.hpp"
#include "Data_Structures/lista.hpp"
#include "Algoritmos/Genético/gen_Engine.hpp"
#include "Algoritmos/Genético/poblacion.hpp"
#include "Game_Logic/tablero.hpp"
#include "Game_Logic/server.hpp"

#include "qdebug.h"
#include <QApplication>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <bitset>

using namespace std;

// Declaracion de funciones
void print_maze(int(*maze)[10]);
int Backtracking_test();
int A_star_test();
void lista_test();
void algoritmo_Genetico();

int main(){
    srand (time(NULL));

    Server *server = new Server();
    Socket* socket = &Socket::getInstance();
    string ip = "192.168.43.144";
    while (true) {
        server->Play(ip);
        delete server;
        server = new Server();
        socket->escuchar(8082);
    }

    /* PRUEBAS GENETICOS */
    //algoritmo_Genetico();

    /* PRUEBAS PATHFINDING */
    //cout<<"Backtracking:"<<endl;
    //Backtracking_test();

    //cout<<"A*:"<<endl;
    //A_star_test();

    return 0;
}

//Funcion que se encarga de  realizar una prueba al algoritmo Backtracking
int Backtracking_test(){

    // 1. Declarar la matriz que se usara como laberinto
    Tablero* tablero = new Tablero();

    // 2. Insertar obstáculos en el tablero
    tablero->ColocarObstaculo(1,0,2);
    tablero->ColocarObstaculo(2,1,2);
    tablero->ColocarObstaculo(3,1,1);
    tablero->ColocarObstaculo(3,2,2);

    print_maze(tablero->Maze);
    cout<<endl;

    // Ya hay un método que limpia el laberinto para volver a ser utilizado
    Backtracking* solver = new Backtracking();
    string my_path = solver->Backtracking_Search(tablero->Maze,0,0);
    int time = solver->get_Time();


    print_maze(tablero->Maze);
    cout<<endl;

    cout<<my_path<<endl;
    cout<<"Encuentra la ruta en: "<< time<<" us"<<endl;

    tablero->ColocarObstaculo(1,9,2);
    tablero->ColocarObstaculo(2,1,5);
    tablero->ColocarObstaculo(3,4,2);
    tablero->ColocarObstaculo(3,3,8);

    my_path = solver->Backtracking_Search(tablero->Maze,0,0);
    time = solver->get_Time();

    print_maze(tablero->Maze);
    cout<<endl;

    cout<<my_path<<endl;
    cout<<"Encuentra la ruta en: "<< time<<" us"<<endl;

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
    int maze[][10] = { {0,0,1,0,0,0,0,0,1,0},
                       {0,0,1,0,1,1,1,0,1,0},
                       {0,1,1,0,0,0,0,0,1,0},
                       {0,1,0,0,1,1,1,0,0,0},
                       {0,0,1,0,1,0,1,0,0,0},
                       {0,0,0,0,1,0,0,0,1,1},
                       {1,1,0,1,1,0,1,1,1,1},
                       {0,0,0,1,0,0,1,0,0,1},
                       {0,0,0,1,0,0,1,0,1,0},
                       {0,0,0,1,0,0,0,0,1,0}};

    // Ejecutar el algoritmo A*
    A_star* solver = new A_star();
    solver->A_star_Search(maze,5,1);

    // Obtener la ruta como String
    string my_Path = solver->get_Path();
    int time = solver->get_Time();
    delete(solver);

    // Muestra en consola la ruta encontrada
    cout<<my_Path<<endl;
    cout<<"Encuentra la ruta en: "<<time<<" us"<<endl;
    return 0;
}

// Función de prueba del Algoritmo genético
void algoritmo_Genetico(){
    int gen = 1, obst = 3;
    Poblacion* P = new Poblacion(90);
    P->Ordenar();
    P->print_Estadistica(1,3);

    while(gen <= 10){
        gen++;
        obst+=3; // Cada iteración se agregan 3 obstáculos nuevos
        qDebug()<<"-------------------------------";
        qDebug()<<"Generación: "<<gen;
        Gen_Engine::Evolve(P);
        P->Ordenar();
        P->print_Estadistica(gen,obst);
    }
}
