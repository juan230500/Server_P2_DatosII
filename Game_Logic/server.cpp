#include "server.hpp"
#define CANTNUEVOSOBSTACULOS 3

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

void Server::obstaculosAleatorios(Tablero* maze, int maxTipo){
    Backtracking *_Backtracking = new Backtracking();
    string Backtracking_Path = "0";
    int tipo, fila, col;
    random_device rd;
    mt19937 gen(rd());
    for(int cont = 0; cont < CANTNUEVOSOBSTACULOS; cont++){
        uniform_int_distribution<> dis1(1,maxTipo);
        tipo = dis1(gen);
        uniform_int_distribution<> dis2(0,9);
        fila = dis2(gen);
        col = dis2(gen);
        if((fila == 0 && col == 0) || (fila == 9 && col == 9)) cont--;
        else{
            maze->Maze[fila][col] = tipo;
            Backtracking_Path = _Backtracking->Backtracking_Search(maze->Maze,0,0);
            maze->Maze[fila][col] = 0;
            if(Backtracking_Path != "") maze->ColocarObstaculo(tipo, fila, col);
            else cont--;
        }
    }
}

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

void Server::Play(){

    // #1. Generar las dos poblaciones iniciales

    Poblacion *Pob_1 = new Poblacion(90);
    Poblacion *Pob_2 = new Poblacion(90);
    Gladiador *G1, *G2;
    int G1_info[10], G2_info[10];
    // HASTA ESTE PUNTO NO SE HA PUESTO EL TIEMPO -> Gn_info[9]
    // #4. Generar un tablero
    Tablero *Maze = new Tablero();
    // #5. Calcular la primer ruta de c/ Gladiador
    string A_star_Path, Backtracking_Path, obstaculos;
    A_star *_AStar = new A_star();
    Backtracking *_Backtracking = new Backtracking();
    string pos1 = "0", pos2 = "0";
    // #8. Se instancia el Socket
    int fila,col,fila2,col2;
    Socket *canal = &Socket::getInstance();
    int turno=1;
    int maxTipoObstaculos = 3;
    while(pos1 != "" && pos2 != ""){
        if(turno == 3) maxTipoObstaculos = 2;
        if (turno%3 == 0){
            //canal->escuchar(8082);
            // #9. Crear un objeto traductor
            traductorServidor *traductor = new traductorServidor();
           // canal->escuchar(8082);
            bool terminoJ1 = false;
            bool terminoJ2 = false;
            string muerte1 = "";
            string muerte2 = "";
            resistenciaGladiador1Global=G1->getResistencia();
            resistenciaGladiador2Global=G2->getResistencia();
            while(!terminoJ1 || !terminoJ2){
                qDebug()<<"Escuchando ciclo parcial";
                canal->escuchar(8082);
                // #6. Tomar el tiempo que duró c/ Gladiador encontrando su ruta
                int t_G1 = _AStar->get_Time();
                int t_G2 = _Backtracking->get_Time();
                G1_info[9] = t_G1;
                G2_info[9] = t_G2;
                // Se agregan nuevos obstáculos
                obstaculos = Maze->get_obstaculos();
                qDebug()<<"OBSTACULOS PARCIAL";
                qDebug()<<QString::fromStdString(obstaculos);
                // Se recorre la ruta de nuevo
                qDebug()<<"recorre ruta 1";
                muerte1 = recorrerRutaIteracion3(A_star_Path,0,Maze->ArrayDatos);
                qDebug()<<"recorre ruta 2";
                muerte2 = recorrerRutaIteracion3(Backtracking_Path,1,Maze->ArrayDatos);
                qDebug()<<"termina de recorrer rutas";
                if(muerte1 != "") terminoJ1 = true;
                if(muerte2 != "") terminoJ2 = true;
                string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                               A_star_Path,Backtracking_Path,false,
                                                               Pob_1->get_Prom(),Pob_2->get_Prom(),muerte1,muerte2);
                canal->enviar(json,8081,"192.168.42.25");
                qDebug()<< "ENTRA1" << endl;
                moverObstaculos(Maze, fila, col, fila2, col2);
                qDebug()<< "ENTRA2" << endl;

                vector<string> vectorRuta;
                boost::split(vectorRuta, A_star_Path, boost::is_any_of("-"));
                if(vectorRuta.size() > 2){
                    string posiciones = vectorRuta[1];
                    fila = stoi(posiciones.substr(0,1));
                    col = stoi(posiciones.substr(1,1));
                    qDebug()<<"G1"<<to_string(fila).c_str()<<to_string(col).c_str();
                    qDebug()<<"Llama A_star_Search() CicloParcial";
                    _AStar->A_star_Search(Maze->Maze,fila,col);
                    qDebug()<<"Llama _AStar->get_Path() CicloParcial";
                    A_star_Path = _AStar->get_Path();
                }

                vector<string> vectorRuta2;
                boost::split(vectorRuta2, Backtracking_Path, boost::is_any_of("-"));
                qDebug()<<"TAMANIO BT: " << to_string(vectorRuta2.size()).c_str();
                if(vectorRuta2.size() > 2){
                    string posiciones2 = vectorRuta2[1];
                    fila2 = stoi(posiciones2.substr(0,1));
                    col2 = stoi(posiciones2.substr(1,1));
                    qDebug()<<"G2"<<to_string(fila2).c_str()<<to_string(col2).c_str();
                    qDebug()<<"Llama Bactracking_Search() CicloParcial";
                    Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,fila2,col2);
                    qDebug()<<"Sale Backtracking_Search() CicloParcial";
                }
                qDebug()<<"SALE CICLO PARCIAL";
            }turno++;
        }
        else{
            qDebug()<<"Escuchando ciclo completo";
            canal->escuchar(8082);

            // Se agregan nuevos obstáculos
            obstaculosAleatorios(Maze, maxTipoObstaculos);
            obstaculos = Maze->get_obstaculos();
            qDebug()<<">> Lista de obstaculos: "<<obstaculos.c_str();

            qDebug()<<"Llama A_star_Search()";
            _AStar->A_star_Search(Maze->Maze,0,0);
            qDebug()<<"Llama _AStar->get_Path()";
            A_star_Path = _AStar->get_Path();
            qDebug()<<"Llama Bactracking_Search()";
            Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,0,0);
            qDebug()<<"Sale Backtracking_Search()";

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
            qDebug()<<">> Llega hasta la posición: "<<pos1.c_str();

            pos2 = recorrerRuta(Backtracking_Path,G2->getResistencia(),Maze->ArrayDatos);
            qDebug()<<">> Llega hasta la posición: "<<pos2.c_str();
            // #9. Crear un objeto traductor
            traductorServidor *traductor = new traductorServidor();
            string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                           A_star_Path,Backtracking_Path,false,
                                                           Pob_1->get_Prom(),Pob_2->get_Prom(),pos1,pos2);

            // #10. Enviar la información
            canal->enviar(json,8081,"192.168.42.25");
            // Si retorna string vacío es porque ya terminó
            if(pos1 == "" ){
                qDebug()<<" G1 ha llegado!";
                break;
            } else if(pos2 == ""){
                qDebug()<<" G2 ha llegado!";
                break;
            }

            /*-----------------------------------*/
            // Se aplica el genético
            Gen_Engine::Evolve(Pob_1);
            Gen_Engine::Evolve(Pob_2);
            Pob_1->Ordenar();
            Pob_2->Ordenar();

            /*-----------------------------------*/

        /*-----------------------------------*/
            /*Esto es para aumentar el turno 3 */
             turno++;
             qDebug()<<"SALE CICLO COMPLETO";
        }
    }
}
// -----------------------------------------------------------------------------------
string Server::recorrerRuta(string ruta, int resistencia, int (*matrizObstaculos)[10]){
    ruta = ruta.substr(0, ruta.size()-1);
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
string Server::recorrerRutaIteracion3(string ruta, int id, int (*matrizObstaculos)[10]){
    qDebug()<<QString::fromStdString("RUTA: " + ruta);
    ruta = ruta.substr(0, ruta.size()-1);
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    string posiciones = vectorRuta[0];
    int fila = stoi(posiciones.substr(0,1));
    int col = stoi(posiciones.substr(1,1));
    int resistencia = (id == 0) ? resistenciaGladiador1Global:resistenciaGladiador2Global;
    resistencia += matrizObstaculos[fila][col];
    (id == 0) ? resistenciaGladiador1Global = resistencia : resistenciaGladiador2Global = resistencia;
    if(resistencia <= 0){
        return posiciones;
    }
    return "";
}
