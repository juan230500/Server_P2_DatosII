#include "mainwindow.h"
#include <QApplication>
#include "gladiador.h"

int main(int argc, char *argv[])
{
    srand((unsigned)time(nullptr));

    QApplication a(argc, argv);

    Gladiador* G=new Gladiador();
    G->print();
    Gladiador* G1=new Gladiador();
    G1->print();

    Gladiador* G2=(*G)+(*G1);
    G2->print();

    MainWindow w;
    w.show();

    return a.exec();
}
