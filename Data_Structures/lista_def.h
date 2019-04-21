#ifndef LISTA_DEF_H
#define LISTA_DEF_H

/* -------------------------------
 *          CONSTRUCTOR
 * -------------------------------*/

template <class T>
Lista<T>::Lista(){
    this->_head = nullptr;
    this->_largo = 0;
}

/* -------------------------------
 *          METODOS LISTA
 * -------------------------------*/

template <class T>
void Lista<T>::push_back(T dato){
    if(!_head){
        this->_head = new Nodo<T>(dato);
        this->_largo++;
    } else {

        Nodo<T> *aux = _head;
        while(aux->get_Next()!= nullptr){
            aux = aux->get_Next();
        }

        aux->set_Next(new Nodo<T>(dato));
        this->_largo++;

    }
}

template <class T>
void Lista<T>::push_front(T dato){

    Nodo<T> *new_Node = new Nodo<T>(dato);
    if(!_head){
        this->_head = new_Node;
        this->_largo++;
    } else {
        new_Node->set_Next(_head);
        this->_head = new_Node;
        this->_largo++;
    }
}

template <class T>
T Lista<T>::pop_back(){
    Nodo<T> *aux = _head;
    while(aux->get_Next()!= nullptr){
        aux = aux->get_Next();
    }
    return aux->get_Dato();
}

/* -------------------------------
 *        SETTERS & GETTERS
 * -------------------------------*/
template <class T>
T Lista<T>::get_index(int index){
    Nodo<T> *aux = _head;
    for(int i = 0;i!= index;i++){
        aux = aux->get_Next();
    }
    return aux->get_Dato();
}

template <class T>
T Lista<T>::get(T dato){
    Nodo<T> *aux = _head;
    for(int i = 0;i < _largo;i++){
        if(aux->get_Dato() == dato)
            break;
        aux = aux->get_Next();
    }

    return aux->get_Dato();
}

template <class T>
int Lista<T>::get_largo(){
    return this->_largo;
}

template <class T>
void Lista<T>::set(int index,T dato){
    Nodo<T> *aux = _head;
    for(int i = 0;i!= index;i++){
        aux = aux->get_Next();
    }

    aux->set_Dato(dato);
}

/* -------------------------------
 *              UTIL
 * -------------------------------*/
template <class T>
void Lista<T>::print_lista(){
    for(Nodo<T> *nodo = _head; nodo!= nullptr; nodo = nodo->get_Next()){
        cout<<"[ "<<nodo->get_Dato()<<" ]->";
    }
    cout<<"NULL"<<endl;
}

#endif // LISTA_DEF_H
