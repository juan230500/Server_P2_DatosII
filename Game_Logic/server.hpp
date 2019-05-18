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
#include <boost/algorithm/string.hpp>
#include <vector>
#include "qdebug.h"

using namespace std;

//! \brief Servidor que lleva la logica del Juego
class Server
{
private:

    int resistenciaGladiador1Global=0;
    int resistenciaGladiador2Global=0;

public:

    //! \brief Constructor
    Server();

    //! \brief Funcion principal de simulacion
    //! \param ip: IP Address
    void Play(string ip);

    //! \brief Metodo que recorre la ruta que sigue un gladiador
    //! \param ruta: Ruta de Salida
    //! \param resistencia: Resistencia del Gladiador que recorre la Zona
    //! \param matrizObstaculos: Matriz que debe recorrerse
    string recorrerRuta(string ruta, int resistencia, int matrizObstaculos[][10]);

    //! \brief Recorre la Ruta en la 3er iteracion
    //! \param ruta
    //! \param id
    string recorrerRutaIteracion3(string ruta, int id, int (*matrizObstaculos)[10]);

    //! \brief Metodo encargado de colocar tres obstaculos aleatorios
    //! \param maze
    //! \param maxTipo
    void obstaculosAleatorios(Tablero* maze, int maxTipo);

    bool verificarObstaculo(int fila, int col, vector<string> obstaculosActuales);

    //! \brief Metodo ESPECIAL que mueve los obstaculos una posicion en la tercer iteracion`w
    void moverObstaculos(Tablero* maze, int G1fila, int G1col, int G2fila, int G2col);
};

#endif // SERVER_HPP
