#include "server.hpp"

Server::Server(){

}


void generate_Info(Gladiador *G1, int info[]){

    info[0] = G1->getId();
    info[1] = G1->getEdad();
    info[2] = 10; //G1->getSurvival();
    info[3] = 5;  //G1->getExpectedGen();
    info[4] = G1->getInteligenciaEmocional();
    info[5] = G1->getCondicionFisica();
    info[6] = G1->getFuerzaTroncoSuperior();
    info[7] = G1->getFuerzaTroncoInferior();
    info[8] = G1->getResistencia();
    info[9] = 0; // Este comienza en 0 por default

}

void Server::Play(){

    // #1. Generar las dos poblaciones iniciales

    Poblacion *Pob_1 = new Poblacion(90);
    Poblacion *Pob_2 = new Poblacion(90);

    // #2. Devolver el promedio de resistencia de las poblaciones
    int prom_P1 = Pob_1->get_Prom();
    int prom_P2 = Pob_2->get_Prom();

    // #3. Seleccionar los gladiadores que atravesarán el laberinto
    Gladiador *G1 = Pob_1->get_Mejor();
    Gladiador *G2 = Pob_2->get_Mejor();

    // #4. Generar arrays de inf@ de c/Gladiador
    int G1_info[10];
    int G2_info[10];
    generate_Info(G1,G1_info);
    generate_Info(G2,G2_info);

    // HASTA ESTE PUNTO NO SE HA PUESTO EL TIEMPO -> Gn_info[9]
    // #4. Generar un tablero

    Tablero *Maze = new Tablero();

    Maze->ColocarObstaculo(2,2,1);
    Maze->ColocarObstaculo(1,3,4);
    Maze->ColocarObstaculo(3,4,1);

    string obstaculos = Maze->get_obstaculos();
    qDebug()<<">> Lista de obstaculos: "<<obstaculos.c_str();

    // #5. Calcular la primer ruta de c/ Gladiador
    string A_star_Path, Backtracking_Path;

    A_star *_AStar = new A_star();
    Backtracking *_Backtracking = new Backtracking();

    _AStar->A_star_Search(Maze->Maze,0,0);
    A_star_Path = _AStar->get_Path();
    Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,0,0);

    qDebug()<<">> Ruta A*: "<<A_star_Path.c_str();
    qDebug()<<">> Ruta BT: "<<Backtracking_Path.c_str();

    // #6. Tomar el tiempo que duró c/ Gladiador encontrando su ruta
    int t_G1 = _AStar->get_Time();
    int t_G2 = Backtracking_Path();

    G1_info[9] = t_G1;
    G2_info[9] = t_G2;

}

string Server::recorrerRuta(string ruta, int resistencia, int matrizObstaculos[][10]){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    for(int indice = 0, size = vectorRuta.size(); indice < size; indice++){
        string posiciones = vectorRuta[indice];
        int fila = stoi(posiciones.substr(0,1));
        int col = stoi(posiciones.substr(1,1));
        resistencia += matrizObstaculos[fila][col];
        if(resistencia <= 0) return posiciones;
    }return "";
}
