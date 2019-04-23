#include "gladiador.h"

unsigned short int Gladiador::idGlobal=0;

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

Gladiador::Gladiador()
{
    id=++idGlobal;
    Edad=rand()%40+21;
    InteligenciaEmocional=rand()%101; //coeficiente
    CondicionFisica=rand()%16; //Test de Ruffier
    FuerzaTroncoSuperior=rand()%101; //Newtons
    FuerzaTroncoInferior=rand()%101; //Newtons

    //Total 4-26
    this->Resistencia=Edad/10 //4-6
    +FuerzaTroncoSuperior/20 //0-5
    +FuerzaTroncoInferior/20 //0-5
    +InteligenciaEmocional/20 //0-5
    +5-CondicionFisica/3; //0-5
}

Gladiador::Gladiador(unsigned short Edad, unsigned short InteligenciaEmocional, unsigned short CondicionFisica, unsigned short FuerzaTroncoSuperior, unsigned short FuerzaTroncoInferior)
{
    id=++idGlobal;
    this->Edad=Edad;
    this->InteligenciaEmocional=InteligenciaEmocional;
    this->CondicionFisica=CondicionFisica;
    this->FuerzaTroncoInferior=FuerzaTroncoInferior;
    this->FuerzaTroncoSuperior=FuerzaTroncoSuperior;

    //Total 4-26
    this->Resistencia=Edad/10 //4-6
    +FuerzaTroncoSuperior/20 //0-5
    +FuerzaTroncoInferior/20 //0-5
    +InteligenciaEmocional/20 //0-5
    +5-CondicionFisica/3; //0-5
}


void Gladiador::print()
{
    qDebug()<<"ID: "<<id<<"=====================";
    qDebug()<<"Edad: "<<Edad;
    qDebug()<<"InteligenciaEmocional: "<<InteligenciaEmocional;
    qDebug()<<"CondicionFisica: "<<CondicionFisica;
    qDebug()<<"FuerzaTroncoSuperior: "<<FuerzaTroncoSuperior;
    qDebug()<<"FuerzaTroncoInferior: "<<FuerzaTroncoInferior;
    qDebug()<<"Resistencia: "<<Resistencia;
}

Gladiador* Gladiador::operator+(const Gladiador &P)
{
    unsigned short int Edad=(this->Edad+P.getEdad())/2;
    unsigned short int InteligenciaEmocional=(this->InteligenciaEmocional+P.getInteligenciaEmocional())/2;
    unsigned short int CondicionFisica=(this->CondicionFisica+P.getCondicionFisica())/2;
    unsigned short int FuerzaTroncoSuperior=(this->FuerzaTroncoSuperior+P.getFuerzaTroncoSuperior())/2;
    unsigned short int FuerzaTroncoInferior=(this->FuerzaTroncoInferior+P.getFuerzaTroncoInferior())/2;

    return new Gladiador(Edad,InteligenciaEmocional,CondicionFisica,FuerzaTroncoSuperior,FuerzaTroncoInferior);
}
