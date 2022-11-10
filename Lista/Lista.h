#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_

#include "Nodo.h"
#include <iostream>

/**
 * Clase que implementa una Lista Enlazada generica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T> class Lista
{
private:
    Nodo<T> *inicio;

public:
  Lista();

  Lista(const Lista<T> &li);

  ~Lista();

  bool esVacia();

  int getTamanio();

  void insertar(int pos, T dato);

  void insertarPrimero(T dato);

  void insertarUltimo(T dato);

  void remover(int pos);

  T getDato(int pos);

  void reemplazar(int pos, T dato);

  void vaciar();

  void mostrar();

  void insertAfterN (double oldValue , double newValue , int n);

  bool buscar(T dato);

  Nodo<T>* getInicio();

  void setInicio (Nodo<T> *newInicio);
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T> Lista<T>::Lista()
{
    inicio = nullptr;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T> Lista<T>::Lista(const Lista<T> &li)
{
    this->inicio = li.inicio;
}

/**
 * Destructor de la clase Lista, se encarga de liberar la memoria de todos los
 * nodos utilizados en la lista
 * @tparam T
 */
template <class T> Lista<T>::~Lista()
{
    vaciar();
    delete inicio;
}

/**
 * Metodo para saber si la lista esta vacia
 * @tparam T
 * @return true si la lista esta vacia, sino false
 */
template <class T> bool Lista<T>::esVacia()
{
    return inicio == nullptr;
}

/**
 * Metodo para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T> int Lista<T>::getTamanio()
{
    Nodo<T> *nodo = inicio;
    int sumatoria = 0;
    if (esVacia())
    {
        return sumatoria;
    } else
    {
        while (nodo != nullptr)
        {
            sumatoria++;
            nodo = nodo->getSiguiente();
        }
    }
    return sumatoria;
}

/**
 * Inserta un nodo con el dato en la posicion pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato  dato a insertar
 */
template <class T> void Lista<T>::insertar(int pos, T dato)
{
    int posActual = 0;
    Nodo<T> *auxNodo = inicio;

    Nodo<T> *nuevo = new Nodo<T>;
    nuevo->setDato(dato);

    if (pos < 0)
    {
        throw std::invalid_argument("La posicion no existe\n");
    }
    else if (pos == 0) //insertar nodo en la primera posicion
    {
        insertarPrimero(dato);
        return;
    }

    while (posActual < (pos - 1))
    {
        auxNodo = auxNodo->getSiguiente();
        posActual++;

        if (auxNodo == nullptr) //error de programa
        {
            throw std::invalid_argument("Posicion fuera de rango\n");
        }
    }

    nuevo -> setSiguiente(auxNodo->getSiguiente());
    auxNodo->setSiguiente(nuevo);
}

/**
 * Inserta un nodo con el dato en la primera posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarPrimero(T dato)
{
    Nodo<T> *nuevo = new Nodo<T>;
    nuevo->setDato(dato);

    nuevo->setSiguiente(inicio);
    inicio = nuevo;
}

/**
 * Inserta un nodo con el dato en la ultima posicion
 * @tparam T
 * @param dato dato a insertar
 */
template <class T> void Lista<T>::insertarUltimo(T dato)
{
    Nodo<T> *auxNodo = inicio;

    Nodo<T> *nuevo = new Nodo<T>;
    nuevo->setDato(dato);

    if (esVacia())
    {
        inicio = nuevo;
        nuevo->setSiguiente(nullptr);
        return;
    }

    while (auxNodo->getSiguiente() != nullptr)
    {
        auxNodo = auxNodo->getSiguiente();
    }
    auxNodo->setSiguiente(nuevo);
    nuevo->setSiguiente(nullptr);
}

/**
 * Elimina el nodo en la posicion 'pos' de la lista enlazada
 * @tparam T
 * @param pos posicion del nodo a eliminar
 */
template <class T> void Lista<T>::remover(int pos)
{
    int posActual = 0;
    Nodo<T> *auxNodo = inicio;

    if (esVacia())
    {
        throw std::invalid_argument("La lista esta vacia\n");
    }

    else if (pos < 0)
    {
        throw std::invalid_argument("La posicion no existe\n");
    }

    else if(pos == 0)
    {
        inicio = auxNodo->getSiguiente();
        delete auxNodo;
        return;
    }

    while (pos - 1 > posActual)
    {
        auxNodo = auxNodo->getSiguiente();
        posActual++;

        if(auxNodo->getSiguiente() == nullptr)
        {
            throw std::invalid_argument ("La posicion no existe\n");
        }
    }
    Nodo<T> *toDestroy = auxNodo->getSiguiente();
    auxNodo->setSiguiente(auxNodo->getSiguiente()->getSiguiente());
    delete toDestroy;
}

/**
 * Obtener el dato del nodo en la posicion pos
 * @tparam T
 * @param pos posicion del dato
 * @return dato almacenado en el nodo
 */
template <class T> T Lista<T>::getDato(int pos)
{
    int posActual = 0;
    Nodo<T> *auxNodo = inicio;

    if(esVacia())
    {
        throw std::invalid_argument("La lista esta vacia\n");
    }

    else if (pos < 0)
    {
        throw std::invalid_argument("La posicion no existe\n");
    }

    while (posActual < pos)
    {
        auxNodo = auxNodo->getSiguiente();
        posActual++;

        if (auxNodo == nullptr)
        {
            throw std::invalid_argument("La posicion no existe\n");
        }
    }
    return auxNodo->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posicion donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T> void Lista<T>::reemplazar(int pos, T dato)
{
    int posActual = 0;
    Nodo<T> *auxNodo = inicio;

    if (esVacia())
    {
        throw std::invalid_argument("La lista esta vacia\n");
    }

    else if (pos < 0)
    {
        throw std::invalid_argument("La posicion no existe\n");
    }

    while (posActual < pos)
    {
        auxNodo = auxNodo->getSiguiente();
        posActual++;

        if (auxNodo == nullptr)
        {
            throw std::invalid_argument("La posicion no existe\n");
        }
    }
    auxNodo->setDato(dato);
}

/**
 * Función que vacia la lista enlazada
 * @tparam T
 */
template <class T> void Lista<T>::vaciar()
{
    int size = getTamanio();

    for (int i = 0 ; i < size ; i++)
    {
        remover(0);
    }
}

template<class T>
void Lista<T>::mostrar()
{
    if (esVacia())
    {
        throw std::invalid_argument("La lista esta vacia\n");
    }
    int size = getTamanio();

    for (int i = 0 ; i < size ; i++)
    {
        std::cout << getDato(i) << '\n';
    }
}

template<class T>
void Lista<T>::insertAfterN(double oldValue, double newValue, int n)
{
    Nodo<T> *auxNodo = inicio;
    int posActual = 0;
    int sumador = 0;

    if (esVacia())
    {
        throw std::invalid_argument("La lista esta vacia\n");
    }

    if (n <= 0)
    {
        throw std::invalid_argument("Ingrese una cantidad valida\n");
    }

    while (auxNodo != nullptr)
    {
        if (getDato(posActual) == oldValue) sumador++;
        if (sumador == n)
        {
            insertar(posActual+1 , newValue);
            break;
        }
        auxNodo = auxNodo->getSiguiente();
        posActual++;

        if (auxNodo == nullptr)
        {
            throw std::invalid_argument("No hay suficientes repeticiones en la lista\n");
        }
    }

}

template<class T>
Nodo<T> *Lista<T>::getInicio() {
    return inicio;
}

template<class T>
bool Lista<T>::buscar(T dato)
{
    Nodo<T> *auxNodo = inicio;

    if (esVacia())
    {
        return false;
    }

    while(auxNodo != nullptr)
    {
        if(auxNodo->getDato() == dato) return true;
        auxNodo = auxNodo->getSiguiente();
    }
    return false;
}

template<class T>
void Lista<T>::setInicio(Nodo<T> *newInicio)
{
    inicio = newInicio;
}

#endif // U02_LISTAS_LISTA_LISTA_H_