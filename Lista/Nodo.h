//
// Created by Maximo Chattas on 18/08/2022.
//

#ifndef INC_2021A2_U02_LISTAS_MAXIMOCHATTAS_NODO_H
#define INC_2021A2_U02_LISTAS_MAXIMOCHATTAS_NODO_H

template<class T>
class Nodo
{
private:
    T dato;
    Nodo<T> *siguiente;

public:
    Nodo(){
    }
    Nodo(T dato);

    T getDato();

    void setDato(T);

    Nodo<T> *getSiguiente();

    void setSiguiente(Nodo<T>*);

};


template<class T>
T Nodo<T>::getDato() {
    return dato;
}

template<class T>
void Nodo<T>::setDato(T dato) {
    this->dato = dato;
}

template<class T>
Nodo<T> *Nodo<T>::getSiguiente() {
    return siguiente;
}

template<class T>
void Nodo<T>::setSiguiente(Nodo<T> *siguiente) {
    this->siguiente = siguiente;
}

template<class T>
Nodo<T>::Nodo(T dato)
{
    this->dato = dato;
    this->siguiente = nullptr;
}

#endif //INC_2021A2_U02_LISTAS_MAXIMOCHATTAS_NODO_H
