#ifndef LISTA_HPP
#define LISTA_HPP

//Bibliotecas
#include <iostream>
#include "nodo.hpp"

template <class T>
class Lista
{
    Nodo<T> *_head;
    int _largo;

public:

    Lista();

    void push_back(T dato);

    void push_front(T dato);

    T pop_back();

    T get(T dato);

    T get_index(int index);

    int get_largo();

    void set(int index, T dato);

    void print_lista();
};

#include "lista_def.h"
#endif // LISTA_HPP
