#ifndef U05_HASH_HASHMAP_HASHMAP_H_
#define U05_HASH_HASHMAP_HASHMAP_H_

#include <cstddef>
#include <stdexcept>
#include "HashEntry.h"
#include "../Lista/Lista.h"

template <class K, class T> class HashMapList {
private:
    Lista<HashEntry<K , T> > **tabla;

    unsigned int tamanio;

  unsigned int hashFunc(K clave);

  unsigned int (*hashFuncP)(K clave); //Puntero a función

public:
  explicit HashMapList(unsigned int tamanio);

  explicit HashMapList(unsigned int tamanio, unsigned int (*fp)(K clave));

  T get(K clave);

  void put(K clave, T valor);

  void remove(K clave);

  ~HashMapList();

  bool esVacio();
};

template <class K, class T> HashMapList<K, T>::HashMapList(unsigned int tamanio)
{
    this->tamanio = tamanio;
    tabla = new Lista<HashEntry<K , T> > *[tamanio];

    for(int i = 0 ; i < tamanio ; i++)
    {
        tabla[i] = NULL;
    }

    hashFuncP = &hashFunc;
}

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int tamanio, unsigned int (*fp)(K clave))
{
    this->tamanio = tamanio;
    tabla = new Lista<HashEntry<K , T> > *[tamanio];

    for(int i = 0 ; i < tamanio ; i++)
    {
        tabla[i] = NULL;
    }

    hashFuncP = fp;
}

template <class K, class T> HashMapList<K, T>::~HashMapList()
{
    for(int i = 0 ; i < tamanio ; i++)
    {
        if(tabla[i] != NULL)
        {
            delete tabla[i];
        }
    }
}

template <class K, class T> T HashMapList<K, T>::get(K clave)
{
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL)
    {
        throw std::invalid_argument("El Dato no se encuentra en la tabla de hash\n");
    }

    Nodo<HashEntry<K , T> > *auxNodo = tabla[pos]->getInicio();

    while (auxNodo != nullptr)
    {
        if (auxNodo->getDato().getClave() == clave)
        {
            return auxNodo->getDato().getValor();
        }
        auxNodo = auxNodo->getSiguiente();
    }

    throw std::invalid_argument("El Dato no se encuentra en la tabla de hash\n");
}

template <class K, class T> void HashMapList<K, T>::put(K clave, T valor)
{
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL)
    {
        tabla[pos] = new Lista<HashEntry<K , T> >;
    }

    else
    {
        Nodo<HashEntry<K , T> > *auxNodo = tabla[pos]->getInicio();

        while (auxNodo != nullptr)
        {
            if (auxNodo->getDato().getValor() == valor)
            {
                throw std::invalid_argument("El dato ya se encuentra en la funcion de Hash\n");
            }
            auxNodo = auxNodo->getSiguiente();
        }
    }

    tabla[pos]->insertarUltimo(HashEntry<K , T>(clave , valor));

}

template <class K, class T> void HashMapList<K, T>::remove(K clave)
{}

template <class K, class T> bool HashMapList<K, T>::esVacio()
{
    for (int i = 0 ; i < tamanio ; i++)
    {
        if(tabla[i] != NULL) return false;
    }
    return true;
}

template <class K, class T> unsigned int HashMapList<K, T>::hashFunc(K clave)
{
    throw std::invalid_argument("ERROR: Función Hash por Defecto\n");
}


#endif // U05_HASH_HASHMAP_HASHMAP_H_
