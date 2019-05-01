#include "traductorservidor.h"
#include <iostream>
using namespace std;
traductorServidor::traductorServidor()
{

}

string traductorServidor::SerializarInformacionIteracion3(string obstaculos1, string rutaA, string rutaB, bool finalizacion)
{
    const char* json = "{\"AvanceGenetico\":0,"
                       "\"finalizacion\":true,"
                       "\"rutaA\":\"abcdefghaaa\","
                       "\"rutaB\":\"abcdefghaaa\","
                       "\"obstaculos\":\"abcdefghaaa\","
                       "\"atributosGladiador1\":[0,2,0,0,0,0,0,0,0,0],"
                       "\"atributosGladiador2\":[0,2,0,0,0,0,0,0,0,0],"
                       "\"ganador\":\"\"}";
    Document d;
    d.Parse(json);
    d["finalizacion"].SetBool(finalizacion);
    if (!finalizacion) {
        string stmp;
        const char * cstr = rutaA.c_str();
        const char * cstr1 = rutaB.c_str();
        const char * obstaculos = obstaculos1.c_str();
        d["obstaculos"].SetString((StringRef(obstaculos)));
        d["rutaA"].SetString((StringRef(cstr)));
        d["rutaB"].SetString((StringRef(cstr1)));
    }
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    return buffer.GetString();
}

void traductorServidor::DeserializarInformacionIteracion3(string json,string *obstaculos1, string *rutaA, string *rutaB, bool *finalizacion)
{
    Document d;
    d.Parse(json.c_str());
     const char * cstr=d["rutaA"].GetString();
     const char * obstac=d["obstaculos"].GetString();
    *rutaA=d["rutaA"].GetString();
    *rutaB=d["rutaB"].GetString();
    *obstaculos1=d["obstaculos"].GetString();
    *finalizacion=d["finalizacion"].GetBool();
}
void traductorServidor::DeserializarInfoDeSimulacion(string json,string *obstaculos,int atributosGladiador1[9],int atributosGladiador2[9],bool *finalizacion,int *AvanceGenetico,string *rutaA,string *rutaB)
{
    Document d;
    d.Parse(json.c_str());
   // cout << "ya parsee"<<endl;
    for (int i=0;i<10;i++){
        atributosGladiador1[i]= d["atributosGladiador1"].GetArray()[i].GetInt();
         atributosGladiador2[i]=d["atributosGladiador2"].GetArray()[i].GetInt();
    }
     const char * cstr=d["rutaA"].GetString();
     const char * obstac=d["obstaculos"].GetString();
    *rutaA=d["rutaA"].GetString();
    *rutaB=d["rutaB"].GetString();
    *obstaculos=d["obstaculos"].GetString();
    *finalizacion=d["finalizacion"].GetBool();
    *AvanceGenetico=d["AvanceGenetico"].GetInt();
}
string traductorServidor::SerializarInformacion(string obstaculos1 , int atributosGladiador1[9] , int atributosGladiador2[9], string rutaA,string rutaB, bool finalizacion, int AvanceGenetico)
{

    const char* json = "{\"AvanceGenetico\":0,"
                       "\"finalizacion\":true,"
                       "\"rutaA\":\"abcdefghaaa\","
                       "\"rutaB\":\"abcdefghaaa\","
                       "\"obstaculos\":\"abcdefghaaa\","
                       "\"atributosGladiador1\":[0,2,0,0,0,0,0,0,0,0],"
                       "\"atributosGladiador2\":[0,2,0,0,0,0,0,0,0,0],"
                       "\"ganador\":\"\"}";
    Document d;
    d.Parse(json);
    d["AvanceGenetico"].SetInt(AvanceGenetico);
    d["finalizacion"].SetBool(finalizacion);
    if (!finalizacion) {
        string stmp;
        for(int i=0;i<10;i++){
            d["atributosGladiador1"].GetArray()[i]=atributosGladiador1[i];
            d["atributosGladiador2"].GetArray()[i]=atributosGladiador2[i];
        }
        const char * cstr = rutaA.c_str();
        const char * cstr1 = rutaB.c_str();
        const char * obstaculos = obstaculos1.c_str();
        d["obstaculos"].SetString((StringRef(obstaculos)));
        d["rutaA"].SetString((StringRef(cstr)));
        d["rutaB"].SetString((StringRef(cstr1)));
    }
    // cout<<"termine de serializar"<<endl;
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
   // cout<<"est es el JSON"<<buffer.GetString()<<endl;
    return buffer.GetString();
}
