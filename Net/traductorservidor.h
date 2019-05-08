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
    string SerializarInformacion(string obstaculos1 ,int atributosGladiador1[10],int atributosGladiador2[10],string rutaA,string rutaB,bool finalizacion,float AvanceGenetico1, float AvanceGenetico2,string muerte1,string muerte2);
    void DeserializarInfoDeSimulacion(string json ,string *obstaculos,int atributosGladiador1[10],int atributosGladiador2[10],bool *finalizacion,float *AvanceGenetico1,float *AvanceGenetico2,string *rutaA,string *rutaB,string *muerte1,string *muerte2);

};

#endif // TRADUCTORSERVIDOR_H
