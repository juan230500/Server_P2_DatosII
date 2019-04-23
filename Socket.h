#ifndef SOCKET_H
#define SOCKET_H
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

class Socket
{
private:
     Socket();
public:
     static Socket & getInstance(){
         static Socket instance;
         return instance;
     }

    void escuchar_sala2(int puerto);

    void enviar2(string mnsaje,int puerto,string ip);
};

#endif // SOCKET_H
