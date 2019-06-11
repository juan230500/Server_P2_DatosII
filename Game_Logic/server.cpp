#include "server.hpp"
#define CANTNUEVOSOBSTACULOS 3

Server::Server(){

}

//-----------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------

void Server::obstaculosAleatorios(Tablero* maze, int maxTipo){
    Backtracking *_Backtracking = new Backtracking();
    string Backtracking_Path = "0";
    int tipo, fila, col;
    random_device rd;
    mt19937 gen(rd());
    string obstaculosActuales = maze->get_obstaculos();
    obstaculosActuales = obstaculosActuales.substr(0, obstaculosActuales.size()-1);
    vector<string> vectorObstaculos;
    boost::split(vectorObstaculos, obstaculosActuales, boost::is_any_of("-"));
    for(int cont = 0; cont < CANTNUEVOSOBSTACULOS; cont++){
        uniform_int_distribution<> dis1(1,maxTipo);
        tipo = dis1(gen);
        uniform_int_distribution<> dis2(0,9);
        fila = dis2(gen);
        col = dis2(gen);
        bool obstaculoExiste = verificarObstaculo(fila, col, vectorObstaculos);
        if((fila == 0 && col == 0) || (fila == 9 && col == 9) || obstaculoExiste) cont--;
        else{
            maze->Maze[fila][col] = tipo;
            Backtracking_Path = _Backtracking->Backtracking_Search(maze->Maze,0,0);
            maze->Maze[fila][col] = 0;
            if(Backtracking_Path != "") maze->ColocarObstaculo(tipo, fila, col);
            else cont--;
        }
    }
}

bool Server::verificarObstaculo(int fila, int col, vector<string> obstaculosActuales){
    int cantObstaculos = obstaculosActuales.size();
    string posicion, filaObs, colObs;
    for(int indice = 0; indice < cantObstaculos; indice++){
        posicion = obstaculosActuales[indice];
        qDebug() << posicion.c_str();
        if(posicion != ""){
            filaObs = posicion.substr(0,1);
            colObs = posicion.substr(1,1);
            if(fila == stoi(filaObs) && col == stoi(colObs)) return true;
        }
    }return false;
}

//-----------------------------------------------------------------------------------

void Server::moverObstaculos(Tablero* maze, int G1fila, int G1col, int G2fila, int G2col){
    Backtracking *_Backtracking = new Backtracking();
    string obstaculosAnteriores = maze->get_obstaculos();
    vector<string> vectorObstaculos;
    boost::split(vectorObstaculos, obstaculosAnteriores, boost::is_any_of("-"));
    string posActual, Backtracking_Path;
    int movFila, movCol, fila, col, tipo;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis1(-1,1);
    maze->Limpiar();
    for(int cont = 0; cont < vectorObstaculos.size()-1; cont++){
        movFila = dis1(gen);
        movCol = dis1(gen);
        posActual = vectorObstaculos[cont];
        fila = stoi(posActual.substr(0,1));
        col = stoi(posActual.substr(1,1));
        tipo = stoi(posActual.substr(2,1));
        fila = fila + movFila;
        col = col + movCol;
        if(fila > 9) fila = 0;
        if(fila < 0) fila = 9;
        if(col > 9) col = 0;
        if(col < 0) col = 9;
        if((fila == 0 && col == 0) || (fila == 9 && col == 9)) cont--;
        else if((fila==G1fila && col==G1col) || (fila==G2fila && col==G2col)) cont--;
        else{
            maze->Maze[fila][col] = tipo;
            Backtracking_Path = _Backtracking->Backtracking_Search(maze->Maze,0,0);
            maze->Maze[fila][col] = 0;
            if(Backtracking_Path != "") maze->ColocarObstaculo(tipo, fila, col);
            else cont--;
        }
    }

}

//-----------------------------------------------------------------------------------

void Server::Play(string ip){

    Gladiador::resetIdGlobal();

    // #1. Generar las dos poblaciones iniciales
    Poblacion *Pob_1 = new Poblacion(90);
    Poblacion *Pob_2 = new Poblacion(90);
    Gladiador *G1, *G2;
    int G1_info[10], G2_info[10];

    // #4. Generar un tablero
    Tablero *Maze = new Tablero();
    string A_star_Path, Backtracking_Path, obstaculos;
    A_star *_AStar = new A_star();
    Backtracking *_Backtracking = new Backtracking();
    string pos1 = "0", pos2 = "0";

    // #8. Se instancia el Socket
    Socket *canal = &Socket::getInstance();
    traductorServidor *traductor = new traductorServidor();
    int turno=1;
    int maxTipoObstaculos = 3;
    int ganador=-1;

    while(pos1 != "" && pos2 != "" && turno <= 15){

        if(turno == 3) maxTipoObstaculos = 2;

        if (turno%3 == 0){
            // #9. Crear un objeto traductor
            bool terminoJ1 = false, terminoJ2 = false;
            string muerte1 = "", muerte2 = "";
            resistenciaGladiador1Global=G1->getResistencia();
            resistenciaGladiador2Global=G2->getResistencia();
            vector<string> vectorRuta;
            boost::split(vectorRuta, A_star_Path, boost::is_any_of("-"));
            vector<string> vectorRuta2;
            boost::split(vectorRuta2, Backtracking_Path, boost::is_any_of("-"));
            int fila = 0,col = 0,fila2 = 0,col2 = 0;
            ganador = -1;
            while(!terminoJ1 || !terminoJ2){
                canal->escuchar(8082);
                if(vectorRuta.size() > 2){
                    _AStar->A_star_Search(Maze->Maze,fila,col);
                    A_star_Path = _AStar->get_Path();
                    A_star_Path = A_star_Path.substr(0, A_star_Path.size()-1);
                    vectorRuta.clear();
                    boost::split(vectorRuta, A_star_Path, boost::is_any_of("-"));
                    string posiciones = vectorRuta[1];
                    fila = stoi(posiciones.substr(0,1));
                    col = stoi(posiciones.substr(1,1));
                }else{
                    A_star_Path="99";
                    if(ganador == -1 && !terminoJ1) ganador = 0;
                    terminoJ1 = true;
                }

                if(vectorRuta2.size() > 2){
                    Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,fila2,col2);
                    Backtracking_Path = Backtracking_Path.substr(0, Backtracking_Path.size()-1);
                    vectorRuta2.clear();
                    boost::split(vectorRuta2, Backtracking_Path, boost::is_any_of("-"));
                    string posiciones2 = vectorRuta2[1];
                    fila2 = stoi(posiciones2.substr(0,1));
                    col2 = stoi(posiciones2.substr(1,1));
                }else{
                    Backtracking_Path="99";
                    if(ganador == -1 && !terminoJ2) ganador = 1;
                    terminoJ2 = true;
                }

                // #6. Tomar el tiempo que duró c/ Gladiador encontrando su ruta
                int t_G1 = _AStar->get_Time();
                int t_G2 = _Backtracking->get_Time();
                G1_info[9] = t_G1;
                G2_info[9] = t_G2;

                obstaculos = Maze->get_obstaculos();

                // Se recorre la ruta de nuevo
                muerte1 = recorrerRutaIteracion3(A_star_Path,0,Maze->ArrayDatos);
                muerte2 = recorrerRutaIteracion3(Backtracking_Path,1,Maze->ArrayDatos);
                if(muerte1 != "") terminoJ1 = true;
                if(muerte2 != "") terminoJ2 = true;
                string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                               A_star_Path,Backtracking_Path,false,
                                                               Pob_1->get_Prom(),Pob_2->get_Prom(),muerte1,muerte2,ganador);
                canal->enviar(json,8081,ip);

                qDebug()<< "ENTRA1" << endl;
                moverObstaculos(Maze, fila, col, fila2, col2);
                qDebug()<< "ENTRA2" << endl;

            } turno++;
            if(ganador>=0) break;
        }else{
            ganador = -1;
            canal->escuchar(8082);

            // Se agregan nuevos obstáculos
            obstaculosAleatorios(Maze, maxTipoObstaculos);
            obstaculos = Maze->get_obstaculos();

            _AStar->A_star_Search(Maze->Maze,0,0);
            A_star_Path = _AStar->get_Path();
            A_star_Path = A_star_Path.substr(0, A_star_Path.size()-1);
            Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,0,0);
            Backtracking_Path = Backtracking_Path.substr(0, Backtracking_Path.size()-1);

            // #3. Seleccionar los gladiadores que atravesarán el laberinto
            G1 = Pob_1->get_Mejor();
            G2 = Pob_2->get_Mejor();

            // #4. Generar arrays de inf@ de c/Gladiador
            generate_Info(G1,G1_info);
            generate_Info(G2,G2_info);

            // #6. Tomar el tiempo que duró c/ Gladiador encontrando su ruta
            int t_G1 = _AStar->get_Time();
            int t_G2 = _Backtracking->get_Time();

            G1_info[9] = t_G1;
            G2_info[9] = t_G2;

            // #7. Recorrer la Zona de Intimidación
            pos1 = recorrerRuta(A_star_Path,G1->getResistencia(),Maze->ArrayDatos);
            pos2 = recorrerRuta(Backtracking_Path,G2->getResistencia(),Maze->ArrayDatos);

            if(pos1 == "" && pos2 == "")
                A_star_Path.size() < Backtracking_Path.size() ? ganador = 0: ganador = 1;
            else if(pos1=="") ganador = 0;
            else if(pos2 == "") ganador = 1;

            // #9. Crear un objeto traductor
            string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                           A_star_Path,Backtracking_Path,false,
                                                           Pob_1->get_Prom(),Pob_2->get_Prom(),pos1,pos2,ganador);
            // #10. Enviar la información
            canal->enviar(json,8081,ip);
            // Si retorna string vacío es porque ya terminó
            if(ganador >= 0) break;

            // Se aplica el genético
            Gen_Engine::Evolve(Pob_1);
            Gen_Engine::Evolve(Pob_2);
            Pob_1->Ordenar();
            Pob_2->Ordenar();

            turno++;
        }
    }
    if(turno > 15){
        string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                       A_star_Path,Backtracking_Path,false,
                                                       Pob_1->get_Prom(),Pob_2->get_Prom(),pos1,pos2,2);
        canal->enviar(json,8081,ip);
    }
}

// -----------------------------------------------------------------------------------

string Server::recorrerRuta(string ruta, int resistencia, int (*matrizObstaculos)[10]){
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

//------------------------------------------------------------------------------------

string Server::recorrerRutaIteracion3(string ruta, int id, int (*matrizObstaculos)[10]){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    string posiciones = vectorRuta[0];
    int fila = stoi(posiciones.substr(0,1));
    int col = stoi(posiciones.substr(1,1));
    int resistencia = (id == 0) ? resistenciaGladiador1Global:resistenciaGladiador2Global;
    resistencia += matrizObstaculos[fila][col];
    (id == 0) ? resistenciaGladiador1Global = resistencia : resistenciaGladiador2Global = resistencia;
    if(resistencia <= 0) return posiciones;
    return "";
}
