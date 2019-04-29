#include "gladiador.h"

unsigned short int Gladiador::idGlobal=0;

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/

// Genera el Gladiador de manera aleatoria
Gladiador::Gladiador()
{
    id=++idGlobal;
    Edad=rand()%40+21;
    InteligenciaEmocional=rand()%101; //coeficiente
    CondicionFisica=rand()%16; //Test de Ruffier
    FuerzaTroncoSuperior=rand()%101; //Newtons
    FuerzaTroncoInferior=rand()%101; //Newtons

    calc_Resistencia();
}

// Permite crear un Gladiador con parámetros establecidos
Gladiador::Gladiador(unsigned short Edad, unsigned short InteligenciaEmocional, unsigned short CondicionFisica,
                     unsigned short FuerzaTroncoSuperior, unsigned short FuerzaTroncoInferior)
{
    id=++idGlobal;
    this->Edad=Edad;
    this->InteligenciaEmocional=InteligenciaEmocional;
    this->CondicionFisica=CondicionFisica;
    this->FuerzaTroncoInferior=FuerzaTroncoInferior;
    this->FuerzaTroncoSuperior=FuerzaTroncoSuperior;

    calc_Resistencia();
}

/* -------------------------------
 *          METODOS UTIL
 * -------------------------------*/

// Realiza un cálculo de la resistencia del gladiador
void Gladiador::calc_Resistencia(){
    //Total 4-26
    this->Resistencia=Edad/10 //4-6
    +FuerzaTroncoSuperior/20 //0-5
    +FuerzaTroncoInferior/20 //0-5
    +InteligenciaEmocional/20 //0-5
    +5-CondicionFisica/3; //0-5
}

void Gladiador::print(){
    qDebug()<<"ID: "<<id;
    qDebug()<<"=====================";
    qDebug()<<"Edad: "<<Edad;
    qDebug()<<"InteligenciaEmocional: "<<InteligenciaEmocional;
    qDebug()<<"CondicionFisica: "<<CondicionFisica;
    qDebug()<<"FuerzaTroncoSuperior: "<<FuerzaTroncoSuperior;
    qDebug()<<"FuerzaTroncoInferior: "<<FuerzaTroncoInferior;
    qDebug()<<"_____________________";
    qDebug()<<"Resistencia: "<<Resistencia;
}

// Esta una sobre carga al operador + ,es la funcion que me permite
// cruzar dos gladiadores de manera que se sumen sus atributos.
Gladiador* Gladiador::operator+(const Gladiador &P){

    /*unsigned short int Edad=(this->Edad+P.getEdad())/2;
    unsigned short int InteligenciaEmocional=(this->InteligenciaEmocional+P.getInteligenciaEmocional())/2;
    unsigned short int CondicionFisica=(this->CondicionFisica+P.getCondicionFisica())/2;
    unsigned short int FuerzaTroncoSuperior=(this->FuerzaTroncoSuperior+P.getFuerzaTroncoSuperior())/2;
    unsigned short int FuerzaTroncoInferior=(this->FuerzaTroncoInferior+P.getFuerzaTroncoInferior())/2;*/

    // Se escoge un tipo de cruce
    int punto_cruce = rand()%4+1;
    //qDebug()<<punto_cruce;

    unsigned short int Edad;
    unsigned short int InteligenciaEmocional;
    unsigned short int CondicionFisica;
    unsigned short int FuerzaTroncoSuperior;
    unsigned short int FuerzaTroncoInferior;

    switch (punto_cruce) {
    // Punto cruce {0,0,0,1,1}
    case 1:{

        Edad = this->getEdad();
        InteligenciaEmocional = this->getInteligenciaEmocional();
        CondicionFisica = this->getCondicionFisica();
        FuerzaTroncoSuperior = P.getFuerzaTroncoSuperior();
        FuerzaTroncoInferior = P.getFuerzaTroncoInferior();
        break;
    }
    // Punto cruce {1,1,1,0,0}
    case 2:{

        Edad = P.getEdad();
        InteligenciaEmocional = P.getInteligenciaEmocional();
        CondicionFisica = P.getCondicionFisica();
        FuerzaTroncoSuperior = this->getFuerzaTroncoSuperior();
        FuerzaTroncoInferior = this->getFuerzaTroncoInferior();
        break;
    }
    // Intercalado A {1,0,1,0,1}
    case 3:{
        Edad = this->getEdad();
        InteligenciaEmocional = P.getInteligenciaEmocional();
        CondicionFisica = this->getCondicionFisica();
        FuerzaTroncoSuperior = P.getFuerzaTroncoSuperior();
        FuerzaTroncoInferior = this->getFuerzaTroncoInferior();
        break;
    }
    // Intercalado B {0,1,0,1,0}
    case 4:{
        Edad = P.getEdad();
        InteligenciaEmocional = this->getInteligenciaEmocional();
        CondicionFisica = P.getCondicionFisica();
        FuerzaTroncoSuperior = this->getFuerzaTroncoSuperior();
        FuerzaTroncoInferior = P.getFuerzaTroncoInferior();

        break;
    }
    default:
        break;
    }

    return new Gladiador(Edad,InteligenciaEmocional,CondicionFisica,FuerzaTroncoSuperior,FuerzaTroncoInferior);
}

/* -------------------------------
 *         GETTERS Y SETTERS
 * -------------------------------*/
unsigned short Gladiador::getEdad() const
{
    return Edad;
}

void Gladiador::setEdad(unsigned short value)
{
    Edad = value;
}

unsigned short Gladiador::getInteligenciaEmocional() const
{
    return InteligenciaEmocional;
}

void Gladiador::setInteligenciaEmocional(unsigned short value)
{
    InteligenciaEmocional = value;
}

unsigned short Gladiador::getCondicionFisica() const
{
    return CondicionFisica;
}

void Gladiador::setCondicionFisica(unsigned short value)
{
    CondicionFisica = value;
}

unsigned short Gladiador::getFuerzaTroncoSuperior() const
{
    return FuerzaTroncoSuperior;
}

void Gladiador::setFuerzaTroncoSuperior(unsigned short value)
{
    FuerzaTroncoSuperior = value;
}

unsigned short Gladiador::getFuerzaTroncoInferior() const
{
    return FuerzaTroncoInferior;
}

void Gladiador::setFuerzaTroncoInferior(unsigned short value)
{
    FuerzaTroncoInferior = value;
}

unsigned short Gladiador::getResistencia() const
{
    return Resistencia;
}

void Gladiador::setResistencia(unsigned short value)
{
    Resistencia = value;
}




