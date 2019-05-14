#ifndef TRADUCTORSERVIDOR_H
#define TRADUCTORSERVIDOR_H

// Bibliotecas
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>

using namespace std;
using namespace rapidjson;

//! @brief Traductor de JSON a objetos y viceversa
class traductorServidor
{
public:

    //! @brief Constructor
    traductorServidor();

    //! @brief Serializa información a JSON
    string SerializarInformacionIteracion3(string obstaculos1 ,string rutaA,string rutaB,bool finalizacion);

    //! @brief Deserializa de JSON a Información
    void  DeserializarInformacionIteracion3(string json,string *obstaculos1 ,string *rutaA,string *rutaB,bool *finalizacion);

    //! @brief Serializa información a JSON
    string SerializarInformacion(string obstaculos1 ,int atributosGladiador1[10],int atributosGladiador2[10],string rutaA,string rutaB,bool finalizacion,float AvanceGenetico1, float AvanceGenetico2,string muerte1,string muerte2, int ganador);

    //! @brief Deserializa de JSON a Información
    void DeserializarInfoDeSimulacion(string json ,string *obstaculos,int atributosGladiador1[10],int atributosGladiador2[10],bool *finalizacion,float *AvanceGenetico1,float *AvanceGenetico2,string *rutaA,string *rutaB,string *muerte1,string *muerte2);

};

#endif // TRADUCTORSERVIDOR_H
