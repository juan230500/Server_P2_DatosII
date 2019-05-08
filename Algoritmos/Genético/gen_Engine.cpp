#include "gen_Engine.hpp"

Gen_Engine::Gen_Engine(){

}

void Gen_Engine::Crossover(Poblacion *Poblacion,Lista<Gladiador*> *Next_Gen){

    // #1. Se escogen los dos mejores Gladiadores
    Lista<Gladiador*> Padres = Poblacion->get_Mejores();

    // #2. Se CRUZAN los Padres para generar una poblacion de 10 individuos
    for(int hijo = 0; hijo < 6; hijo++){


        /*********************************************************
         ¿ Cuantas distintas combinaciones se pueden
           hacer con 4 padres?
           C<n,m> = (n m)= n!/(m!*(n-m)!)
           n = cantidad de elementos del grupo tomado
           m = grupos que se desean hacer

           C<4,2> = 6 -> Se pueden hacer 6 combinaciones distintas!
         **********************************************************/

        switch (hijo) {
        // Cruza P1+P2
        case 0:
            Next_Gen->push_back(*(Padres.get_index(0))+*(Padres.get_index(1)));
            break;
        // Cruza P1+P3
        case 1:
            Next_Gen->push_back(*(Padres.get_index(0))+*(Padres.get_index(2)));
            break;
        // Cruza P1+P4
        case 2:
            Next_Gen->push_back(*(Padres.get_index(0))+*(Padres.get_index(3)));
            break;
        // Cruza P2+P3
        case 3:
            Next_Gen->push_back(*(Padres.get_index(1))+*(Padres.get_index(2)));
            break;
        // Cruza P2+P4
        case 4:
            Next_Gen->push_back(*(Padres.get_index(1))+*(Padres.get_index(3)));
            break;
        // Cruza P3+P4
        case 5:
            Next_Gen->push_back(*(Padres.get_index(2))+*(Padres.get_index(3)));
            break;
        default:
            break;
        }
   }
}

//----------------------------------------------------------------------
int mutate(int value, int gen){

    string val_BIN = bitset<8>(value).to_string();

    string gen_val = val_BIN.substr(gen,1);

    val_BIN = (gen_val.compare("0") == 0) ? val_BIN.replace(gen,1,"1"):val_BIN.replace(gen,1,"0");
    value = boost::numeric_cast<int>(bitset<8>(val_BIN).to_ulong());

    return value;
}
//----------------------------------------------------------------------

// Ver información aquí: http://www.sc.ehu.es/ccwbayes/docencia/mmcc/docs/temageneticos.pdf
// La mutación se realiza sobre cada Hijo
void Gen_Engine::Mutation(Lista<Gladiador*> *Next_Gen){

    // La mutación se realiza sobre cada hijo
    for(int i = 0; i < Next_Gen->size();i++){

        Gladiador *G = Next_Gen->get_index(i);

        // #3. Se calcula la probabilidad de mutación:: P = 1/7 = 0,14 % de Posibilidades de entrar
        int _probabilidad = rand()%4;

        // #4. Se realiza una mutación sobre una característica del Gladiador al azar
        if(_probabilidad == 0){

            qDebug()<<">> Habrá una mutación!";

            /*************************************************
             *                  JUSTIFICACIÓN
             * ----------------------------------------------
             * La mutación es un proceso mucho más importante
             * que el cruce, pues es la que genera cambios en
             * la nueva población y aumenta la probabilidad de
             * mejora.
             * Para esta mutación, el gen a mutar se escoge de
             * forma aletoria al igual que el valor de muta-
             * ción.
             * La teoría lo explica como la alteración de un
             * {bit} pero un bit en las representaciones bina-
             * rias,  en este caso, cumplímos la teoría ya que
             * estamos alterando un "bit" del gladiador.
             *************************************************/

            // Se selecciona un gen al azar
            int gen_mutado = rand()%5+1;

            // Se genera el valor de mutación
            int random_gen = rand()%4;

            switch (gen_mutado) {
            case 1:{
                unsigned short int Edad = mutate(G->getEdad(),random_gen);
                G->setEdad(Edad);
                G->calc_Resistencia();
                break;
            }
            case 2:{
                unsigned short int IE = mutate(G->getInteligenciaEmocional(),random_gen);
                G->setInteligenciaEmocional(IE);
                G->calc_Resistencia();
                break;
            }
            case 3:{
                unsigned short int CF = mutate(G->getCondicionFisica(),random_gen);
                G->setCondicionFisica(CF);
                G->calc_Resistencia();
                break;
            }
            case 4:{
                unsigned short int FTS = mutate(G->getFuerzaTroncoSuperior(),random_gen);
                G->setFuerzaTroncoSuperior(FTS);
                G->calc_Resistencia();
                break;
            }
            case 5:{
                unsigned short int FTI = mutate(G->getFuerzaTroncoInferior(),random_gen);
                G->setFuerzaTroncoInferior(FTI);
                G->calc_Resistencia();
                break;
            }
            default:
                break;
            }
        }
    }
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int invert(int value){

    string val_BIN = bitset<8>(value).to_string();
    int gen = rand()%4+2;

    string gen_invert = val_BIN.substr(gen,3);

    for(int i = 0; i < 3; i++){
        string gen_val = gen_invert.substr(i,1);
        gen_invert = (gen_val.compare("0") == 0) ? gen_invert.replace(i,1,"1"):gen_invert.replace(i,1,"0");
    }

    val_BIN = val_BIN.replace(gen,3,gen_invert);
    value = boost::numeric_cast<int>(bitset<8>(val_BIN).to_ulong());

    return value;
}
//----------------------------------------------------------------------

// Ver información aquí: http://www.sc.ehu.es/ccwbayes/docencia/mmcc/docs/temageneticos.pdf
// La mutación se realiza sobre cada Hijo
void Gen_Engine::Invertion(Lista<Gladiador*> *Next_Gen){

    // La mutación se realiza sobre cada hijo
    for(int i = 0; i < Next_Gen->size();i++){

        Gladiador *G = Next_Gen->get_index(i);

        // #3. Se calcula la probabilidad de inversión P = 1/5 = 0,2 % de posibilidades
        int _probabilidad = rand()%2;

        // #4. Se realiza una inversión sobre una característica del Gladiador al azar
        if(_probabilidad == 0){

            qDebug()<<">> Habrá una inversión!";

            /*************************************************
             *                  JUSTIFICACIÓN
             * ----------------------------------------------
             * La mutación es un proceso mucho más importante
             * que el cruce, pues es la que genera cambios en
             * la nueva población y aumenta la probabilidad de
             * mejora.
             * Para esta mutación, el gen a mutar se escoge de
             * forma aletoria al igual que el valor de muta-
             * ción.
             * La teoría lo explica como la alteración de un
             * {bit} pero un bit en las representaciones bina-
             * rias,  en este caso, cumplímos la teoría ya que
             * estamos alterando un "bit" del gladiador.
             *************************************************/

            // Se selecciona un gen al azar
            int gen_mutado = rand()%5+1;

            switch (gen_mutado) {
            case 1:{
                unsigned short int Edad = invert(G->getEdad());
                G->setEdad(Edad);
                G->calc_Resistencia();
                break;
            }
            case 2:{
                unsigned short int IE = invert(G->getInteligenciaEmocional());
                G->setInteligenciaEmocional(IE);
                G->calc_Resistencia();
                break;
            }
            case 3:{
                unsigned short int CF = invert(G->getCondicionFisica());
                G->setCondicionFisica(CF);
                G->calc_Resistencia();
                break;
            }
            case 4:{
                unsigned short int FTS = invert(G->getFuerzaTroncoSuperior());
                G->setFuerzaTroncoSuperior(FTS);
                G->calc_Resistencia();
                break;
            }
            case 5:{
                unsigned short int FTI = invert(G->getFuerzaTroncoInferior());
                G->setFuerzaTroncoInferior(FTI);
                G->calc_Resistencia();
                break;
            }
            default:
                break;
            }
        }
    }
}

//----------------------------------------------------------------------

// Inserta la nueva pobalción, eliminando a los más débiles
void Gen_Engine::seleccion_Natural(Poblacion *_Poblacion, Lista<Gladiador*> *Next_Gen){

    int largo_poblacion = _Poblacion->get_PobSize(); // Este valor debe ser dinámico
    int largo_nextG = Next_Gen->size();

    for(int i = largo_poblacion-1;i >= largo_poblacion-largo_nextG;i--){
        _Poblacion->get_poblacion()[i] = Next_Gen->pop_back();
    }
}

// Maneja el Proceso Evolutivo de una población
void Gen_Engine::Evolve(Poblacion *Poblacion){

    Lista<Gladiador*> *Next_Gen = new Lista<Gladiador*>();
    // #1. Seleccionar y Cruzar
    Crossover(Poblacion,Next_Gen);

    // #2. Mutación de los hijos
    Mutation(Next_Gen);
    Invertion(Next_Gen);

    // #3. Inserción y Reducción
    seleccion_Natural(Poblacion,Next_Gen);

}
