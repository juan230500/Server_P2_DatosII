#include "gladiador.h"

unsigned short int Gladiador::idGlobal=0;

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/

// Genera el Gladiador de manera aleatoria
Gladiador::Gladiador()
{
    id=++idGlobal;
    Edad=rand()%20+21;
    InteligenciaEmocional=rand()%20; //coeficiente
    CondicionFisica=rand()%12; //Test de Ruffier
    FuerzaTroncoSuperior=rand()%10; //Newtons
    FuerzaTroncoInferior=rand()%10; //Newtons

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
    +CondicionFisica/3; //0-5

}

// Realiza el cálculo de probabilidades por sobrevivir que tiene el gladiador
int Gladiador::calc_ProbSupervivencia(int pos){
    ProbabilidadSupervivencia = (100*(90-pos)/(90));
    return this->ProbabilidadSupervivencia;
}

// Realiza el cálculo de la cantidad de generaciones que se espera que el gladiador continúe en la población
int Gladiador::calc_GenSupervivencia(int pos){

    // Son 90 gladiadores y c/iteración se agregan 6
    // Según su posición en la lista se puede conocer cuántas generaciones
    // le quedan.
    this->GeneracionesSupervivencia = (90-pos)/6 +1;
    return GeneracionesSupervivencia;
}

// Imprime las stats del gladiador en consola
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

//-------------------------------------------------------------------

int manipular_ADN(int p1_ADN,int p2_ADN){

    // #1. Pasar los enteros a binario, para tratarlos como material genético básico.
    string p1_BIN = bitset<8>(p1_ADN).to_string();
    string p2_BIN = bitset<8>(p2_ADN).to_string();

    // #2. Tomar el punto de cruce como el 4 (3).
    p1_BIN = p1_BIN.substr(0,4);
    p2_BIN = p2_BIN.substr(4,4);

    // #3. Cruzar los genes de los padres.
    string h_BIN = p1_BIN+p2_BIN;
    int h_ADN = boost::numeric_cast<int>(bitset<8>(h_BIN).to_ulong());

    return h_ADN;
}

//-------------------------------------------------------------------

// Esta una sobre carga al operador + ,es la funcion que me permite
// cruzar dos gladiadores de manera que se sumen sus atributos.
Gladiador* Gladiador::operator+(const Gladiador &P){

    unsigned short int Edad = manipular_ADN(this->getEdad(),P.getEdad());
    unsigned short int InteligenciaEmocional = manipular_ADN(this->getInteligenciaEmocional(),P.getInteligenciaEmocional());
    unsigned short int CondicionFisica = manipular_ADN(this->getCondicionFisica(),P.getCondicionFisica());
    unsigned short int FuerzaTroncoSuperior = manipular_ADN(this->getFuerzaTroncoSuperior(),P.getFuerzaTroncoSuperior());
    unsigned short int FuerzaTroncoInferior = manipular_ADN(this->getFuerzaTroncoInferior(),P.getFuerzaTroncoInferior());

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




