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

// Ver información aquí: http://www.sc.ehu.es/ccwbayes/docencia/mmcc/docs/temageneticos.pdf
// La mutación se realiza sobre cada Hijo
void Gen_Engine::Mutation(Lista<Gladiador*> *Next_Gen){

    // La mutación se realiza sobre cada hijo
    for(int i = 0; i < Next_Gen->size();i++){

        Gladiador *G = Next_Gen->get_index(i);

        // #3. Se calcula la probabilidad de mutación

        // #4. Se realiza una mutación sobre una característica del Gladiador al azar

        // Se selecciona un gen al azar
        int gen_mutado = rand()%3+1;

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

        // Se genera el valor de mutación
        int random = rand()%30+4;

        switch (gen_mutado) {
        case 1:{
            unsigned short int Edad = G->getEdad()+random;
            G->setEdad(Edad);
            G->calc_Resistencia();
            break;
        }
        case 2:{
            unsigned short int IE = G->getInteligenciaEmocional()+random;
            G->setInteligenciaEmocional(IE);
            G->calc_Resistencia();
            break;
        }
        case 3:{
            unsigned short int CF = G->getCondicionFisica()+random;
            G->setCondicionFisica(CF);
            G->calc_Resistencia();
            break;
        }
        case 4:{
            unsigned short int FTS = G->getFuerzaTroncoSuperior()+random;
            G->setFuerzaTroncoSuperior(FTS);
            G->calc_Resistencia();
            break;
        }
        case 5:{
            unsigned short int FTI = G->getFuerzaTroncoInferior()+random;
            G->setFuerzaTroncoInferior(FTI);
            G->calc_Resistencia();
            break;
        }
        default:
            break;
        }
    }

}

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

    // #3. Inserción y Reducción
    seleccion_Natural(Poblacion,Next_Gen);
}
