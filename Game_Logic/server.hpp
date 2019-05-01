#ifndef SERVER_HPP
#define SERVER_HPP

// Bibliotecas
#include "../Net/Socket.h"
#include "../Net/traductorservidor.h"
#include "../Algoritmos/Genético/gen_Engine.hpp"
#include "../Algoritmos/Genético/poblacion.hpp"
#include "../Algoritmos/Pathfinding/a_star.hpp"
#include "../Algoritmos/Pathfinding/Backtracking.hpp"
#include "tablero.hpp"

#include <iostream>
#include "qdebug.h"

using namespace std;

class Server
{
public:
    Server();

    void Play();
};

#endif // SERVER_HPP
