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
    Edad=rand()%40+20;
    InteligenciaEmocional=rand()%100; //coeficiente
    CondicionFisica=rand()%15; //Test de Ruffier
    FuerzaTroncoSuperior=rand()%100; //Newtons
    FuerzaTroncoInferior=rand()%100; //Newtons

    Resistencia=Edad/10
    +FuerzaTroncoSuperior/10
    +FuerzaTroncoInferior/10
    +InteligenciaEmocional/10
    +15-CondicionFisica;
}

Gladiador::Gladiador(unsigned short Edad, unsigned short InteligenciaEmocional, unsigned short CondicionFisica, unsigned short FuerzaTroncoSuperior, unsigned short FuerzaTroncoInferior)
{
    id=++idGlobal;
    this->Edad=Edad;
    this->InteligenciaEmocional=InteligenciaEmocional;
    this->CondicionFisica=CondicionFisica;
    this->FuerzaTroncoInferior=FuerzaTroncoInferior;
    this->FuerzaTroncoSuperior=FuerzaTroncoSuperior;

    this->Resistencia=Edad/10
    +FuerzaTroncoSuperior/10
    +FuerzaTroncoInferior/10
    +InteligenciaEmocional/10
    +15-CondicionFisica;
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
    int unsigned short Edad=(this->Edad+P.getEdad())/2;
    int unsigned short InteligenciaEmocional=(this->InteligenciaEmocional+P.getInteligenciaEmocional())/2;
    int unsigned short CondicionFisica=(this->CondicionFisica+P.getCondicionFisica())/2;
    int unsigned short FuerzaTroncoSuperior=(this->FuerzaTroncoSuperior+P.getFuerzaTroncoSuperior())/2;
    int unsigned short FuerzaTroncoInferior=(this->FuerzaTroncoInferior+P.getFuerzaTroncoInferior())/2;

    return new Gladiador(Edad,InteligenciaEmocional,CondicionFisica,FuerzaTroncoSuperior,FuerzaTroncoInferior);
}


