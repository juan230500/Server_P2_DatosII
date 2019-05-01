#include "tablero.hpp"

void Tablero::ColocarObstaculo(int id, int fila, int columna)
{
    this->ArrayDatos[fila][columna]=id;
    this->Maze[fila][columna]=id;
    obstaculos += to_string(fila) +to_string(columna)+to_string(id) +"-";
    if (id==1){
        int filaMenor=fila-1;
        int filaMayor=fila+1;
        int columnaMenor=columna-1;
        int columnaMayor=columna+1;

        if (filaMenor<0) filaMenor=0;
        if (columnaMenor<0) columnaMenor=0;
        if (filaMayor>9) filaMayor=9;
        if (columnaMayor>9) columnaMayor=9;

        for (int i=filaMenor;i<=filaMayor;i++){
            for (int j=columnaMenor;j<=columnaMayor;j++){
                if (i!=fila || j!=columna){
                    this->ArrayDatos[i][j]-=1;
                }
            }
        }

    }
    else{
        int filaMenor=fila-2;
        int filaMayor=fila+2;
        int columnaMenor=columna-2;
        int columnaMayor=columna+2;

        if (filaMenor<0) filaMenor=0;
        if (columnaMenor<0) columnaMenor=0;
        if (filaMayor>9) filaMayor=9;
        if (columnaMayor>9) columnaMayor=9;

        for (int i=filaMenor;i<=filaMayor;i++){
            for (int j=columnaMenor;j<=columnaMayor;j++){
                if (i!=fila || j!=columna){
                    if (id==2){
                        this->ArrayDatos[i][j]-=2;
                    }
                    else{
                        this->ArrayDatos[i][j]-=4;
                    }
                }
            }
        }
    }

}

void Tablero::Limpiar()
{
    for (int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            this->ArrayDatos[i][j]=0;
        }
    }
}

void Tablero::Print()
{
    QString S="";
    QString tmp="";
    int dato;
    for (int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            //qDebug().noquote()<<QString::number(this->ArrayDatos[i][j]);
            dato=this->ArrayDatos[i][j];
            if (dato>=0) {
                tmp+=" "+QString::number(dato)+" ";
            }
            else {
                tmp+=QString::number(dato)+" ";
            }
        }
        S+=(tmp+"\n");
        tmp="";
    }
    qDebug().noquote()<<S;
}

Tablero::Tablero(){
    ArrayDatos = (int(*)[10]) calloc(10,sizeof(*ArrayDatos));
    Maze = (int(*)[10]) calloc(10,sizeof(*ArrayDatos));
}
