#include "gen_Engine.hpp"

Gen_Engine::Gen_Engine(){

}

void Gen_Engine::Crossover(Poblacion *Poblacion){

    // 1. Se escogen los dos mejores Gladiadores
    Gladiador *Padre1,*Padre2;
    Poblacion->get_poblacion()[0] = new Gladiador();
}

void Gen_Engine::Mutation(Poblacion *Poblacion){

}

void Gen_Engine::seleccion_Natural(Poblacion *_Poblacion, Lista<Gladiador*> *Next_Gen){

    int largo_poblacion = _Poblacion->get_PobSize(); // Este valor debe ser dinámico
    int largo_nextG = Next_Gen->size();

    qDebug()<<">> LARGO POBLACION: "<<largo_poblacion;
    qDebug()<<">> LARGO NEXT GEN: "<<largo_nextG;

    for(int i = largo_poblacion-1;i >= largo_poblacion-largo_nextG;i--){
        _Poblacion->get_poblacion()[i] = Next_Gen->pop_back();
    }
}
