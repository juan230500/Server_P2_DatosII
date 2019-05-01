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

    Maze->ColocarObstaculo(2,2,2);
    Maze->ColocarObstaculo(1,0,4);
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
    int t_G2 = _Backtracking->get_Time();

    G1_info[9] = t_G1;
    G2_info[9] = t_G2;

    // #7. Recorrer la Zona de Intimidación
    string pos1 = recorrerRuta(A_star_Path,G1->getResistencia(),Maze->ArrayDatos);
    qDebug()<<">> Llega hasta la posición: "<<pos1.c_str();

    string pos2 = recorrerRuta(Backtracking_Path,G2->getResistencia(),Maze->ArrayDatos);
    qDebug()<<">> Llega hasta la posición: "<<pos2.c_str();


    // #8. Se instancia el Socket
    Socket *canal = &Socket::getInstance();
    int turno=1;
    int cnt = 3;
    while(cnt < 10){
        if (turno==3){
            //canal->escuchar(8082);
            // #9. Crear un objeto traductor
            traductorServidor *traductor = new traductorServidor();
           // canal->escuchar(8082);
            string muerte1="";
            string muerte2="";
            // Se calculan las nuevas rutas
            _AStar->A_star_Search(Maze->Maze,0,0);
            A_star_Path = _AStar->get_Path();
            Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,0,0);
            while(muerte1==""&&muerte2==""){
                 canal->escuchar(8082);
                resistenciaGladiador1Global=G1->getResistencia();
                resistenciaGladiador2Global=G2->getResistencia();
                // #6. Tomar el tiempo que duró c/ Gladiador encontrando su ruta
                int t_G1 = _AStar->get_Time();
                int t_G2 = _Backtracking->get_Time();
                G1_info[9] = t_G1;
                G2_info[9] = t_G2;
                // Se agregan nuevos obstáculos
                Maze->ColocarObstaculo(2,cnt,cnt);
                cnt++;
                obstaculos = Maze->get_obstaculos();
                // Se recorre la ruta de nuevo
                pos1 = recorrerRutaIteracion3(A_star_Path,resistenciaGladiador1Global,Maze->ArrayDatos);
                pos2 = recorrerRutaIteracion3(Backtracking_Path,resistenciaGladiador2Global,Maze->ArrayDatos);
                string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                               A_star_Path,Backtracking_Path,false,20,pos1,pos2);
                canal->enviar(json,8081,"192.168.100.9");

                //########## Aqui lo que hago es serializar la ruta para moverme en el primer paso de la ruta###############
                //A_star_Path = A_star_Path.substr(0, A_star_Path.size()-1);
                vector<string> vectorRuta;
                boost::split(vectorRuta, A_star_Path, boost::is_any_of("-"));
                string posiciones = vectorRuta[1];
                int fila = stoi(posiciones.substr(0,1));
                int col = stoi(posiciones.substr(1,1));
                // ahora con el backtracking
                //Backtracking_Path = Backtracking_Path.substr(0, Backtracking_Path.size()-1);
                vector<string> vectorRuta2;
                boost::split(vectorRuta2, Backtracking_Path, boost::is_any_of("-"));
                string posiciones2 = vectorRuta2[1];
                int fila2 = stoi(posiciones2.substr(0,1));
                int col2 = stoi(posiciones2.substr(1,1));
                _AStar->A_star_Search(Maze->Maze,fila,col);
                A_star_Path = _AStar->get_Path();
                Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,fila2,col2);


        }

    }
        else{
            canal->escuchar(8082);

            // #9. Crear un objeto traductor
            traductorServidor *traductor = new traductorServidor();
            string json = traductor->SerializarInformacion(obstaculos,G1_info,G2_info,
                                                           A_star_Path,Backtracking_Path,false,20,pos1,pos2);

            // #10. Enviar la información
            canal->enviar(json,8081,"192.168.100.9");

            // Si retorna string vacío es porque ya terminó
            if(pos1 == "" ){
                qDebug()<<" G1 ha llegado!";
                break;
            } else if(pos2 == ""){
                qDebug()<<" G2 ha llegado!";
                break;
            }

            // Se agregan nuevos obstáculos
            Maze->ColocarObstaculo(2,cnt,cnt);
            cnt++;
            obstaculos = Maze->get_obstaculos();

            // Se calculan las nuevas rutas
            _AStar->A_star_Search(Maze->Maze,0,0);
            A_star_Path = _AStar->get_Path();
            Backtracking_Path = _Backtracking->Backtracking_Search(Maze->Maze,0,0);

            /*-----------------------------------*/
            // Se aplica el genético
            Gen_Engine::Evolve(Pob_1);
            Gen_Engine::Evolve(Pob_2);

            Pob_1->Ordenar();
            Pob_2->Ordenar();

            // Escoger nuevos representantes
            G1 = Pob_1->get_Mejor();
            G2 = Pob_2->get_Mejor();

            /*-----------------------------------*/

            // Se recorre la ruta de nuevo
            pos1 = recorrerRuta(A_star_Path,G1->getResistencia(),Maze->ArrayDatos);
            pos2 = recorrerRuta(Backtracking_Path,G2->getResistencia(),Maze->ArrayDatos);

        /*-----------------------------------*/
            /*Esto es para aumentar el turno 3 */
             turno++;

        }
        //esto es para la iteracion 3

  }
}
// -----------------------------------------------------------------------------------
string Server::recorrerRuta(string ruta, int resistencia, int (*matrizObstaculos)[10]){
    qDebug()<<">> Resistencia del MOP:"<<resistencia;
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
string Server::recorrerRutaIteracion3(string ruta, int resistencia, int (*matrizObstaculos)[10]){
    qDebug()<<">> Resistencia del MOP:"<<resistencia;
    ruta = ruta.substr(0, ruta.size()-1);
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    string posiciones = vectorRuta[0];
    int fila = stoi(posiciones.substr(0,1));
    int col = stoi(posiciones.substr(1,1));
    resistencia += matrizObstaculos[fila][col];
    if(resistencia <= 0) return posiciones;
    else{
    return "";
    }

}