#ifndef NODO_DEF_H
#define NODO_DEF_H

template <class T>
Nodo<T>::Nodo()
{
    this->_next = nullptr;
}

template <class T>
void Nodo<T>::set_Nodo(T dato){
    this->_dato = dato;
}

template <class T>
void Nodo<T>::_print_Nodo(){
    cout<<"{ Dato: "+ to_string(this->_dato)+"}"<<endl;
}

#endif // NODO_DEF_H
