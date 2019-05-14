#ifndef SOCKET_H
#define SOCKET_H

// Bibliotecas
#include <map>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "qdebug.h"
#include <QFile>

#define PORT 8080

using namespace std;

//! \brief Socket
class Socket
{
private:

    //! Constructor
    Socket();
public:

    //! Singleton : Permite obtener la instancia ya creada del Socket
    static Socket & getInstance(){
        static Socket instance;
        return instance;
    }

    //! @brief Escucha el puerto
    string escuchar(int puerto);

    //! @brief Envia un mensaje al cliente/servidor
    void enviar(string mnsaje,int puerto,string ip);
};

#endif // SOCKET_H
