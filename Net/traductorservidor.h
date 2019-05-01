#ifndef TRADUCTORSERVIDOR_H
#define TRADUCTORSERVIDOR_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <string>
using namespace std;
using namespace rapidjson;


class traductorServidor
{
public:
    traductorServidor();
    string SerializarInformacionIteracion3(string obstaculos1 ,string rutaA,string rutaB,bool finalizacion);
    void  DeserializarInformacionIteracion3(string json,string *obstaculos1 ,string *rutaA,string *rutaB,bool *finalizacion);
    string SerializarInformacion(string obstaculos1 ,int atributosGladiador1[9],int atributosGladiador2[9],string rutaA,string rutaB,bool finalizacion,int AvanceGenetico);
    void DeserializarInfoDeSimulacion(string json ,string *obstaculos,int atributosGladiador1[9],int atributosGladiador2[9],bool *finalizacion,int *AvanceGenetico,string *rutaA,string *rutaB);

};

#endif // TRADUCTORSERVIDOR_H
