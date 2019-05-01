#include "mainwindow.h"
#include <QApplication>
#include "traductorservidor.h"
#include "Socket.h"
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
    traductorServidor*test1=new traductorServidor();
    int b[9]={11,12,13,14,15,16,17,18,19};
    int c[9]={11,12,13,14,15,16,17,18,19};
    //char ruta[] = "hola sahid guapo ";
    string rutaA="11-22-33-44-55-66-77-88-99";
    string rutaB="12-42-43-64-75-86-77-08-59";
    string obstaculos="132-251-473";
    string json1=test1->SerializarInformacion(obstaculos,b,c,rutaA,rutaB,false,50);
    int z[10][10];
    int x[9];
    int y[9];
    int AvanceGenetico;
    bool finalizacion;
    string rutaJSON;
    string rutaJSON2;
    string obstaculosJSON;
    test1->DeserializarInfoDeSimulacion(json1,&obstaculosJSON,x,y,&finalizacion,&AvanceGenetico,&rutaJSON,&rutaJSON2);
    cout<<rutaJSON2<<"hola loco"<<endl;
//    Socket  *canal= &Socket::getInstance();
//    canal->enviar(json1,8081,"192.168.100.15");
    //string respuesta=canal->escuchar(8080);
   return 0;
}
