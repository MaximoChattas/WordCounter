#ifndef U05_ARBOL_ARBOL_ARBOLBINARIO_H_
#define U05_ARBOL_ARBOL_ARBOLBINARIO_H_

#include <iostream>
#include "NodoArbol.h"
#include "../Lista/Lista.h"

template<class T>
class ArbolBinario {
private:
    NodoArbol<T> *root;

    T search(T dato , NodoArbol<T> *r);

    NodoArbol<T> * put(T dato , NodoArbol<T> *r);

    NodoArbol<T> * remove(T dato , NodoArbol<T> *r);

    NodoArbol<T> * findMaxAndRemove(NodoArbol<T> *r , bool *found);

    void preOrder(NodoArbol<T> *r);

    void inOrder(NodoArbol<T> *r);

    void inOrderLimit(NodoArbol<T> *r , int &cantidad);

    void postOrder(NodoArbol<T> *r);

    void contarPorNivel(NodoArbol<T> *r, int nivel, Lista<int> &list);

public:
    ArbolBinario();

    void put(T dato);

    T search(T dato);

    void remove(T dato);

    void preorder();

    void inorder();

    void inOrderLimit(int &cantidad);

    void postorder();

    ~ArbolBinario();

    bool esVacio();

    void print();

    void contarPorNivel();
};

/**
 * Constructor del Arbol
 * @tparam K Clave por la cual va a ordenar el árbol
 * @tparam T Valor guardado por el árbol
 */
template<class T>
ArbolBinario<T>::ArbolBinario()
{
    root = nullptr;
}

/**
 * Destructor del Arbol
 */
template<class T>
ArbolBinario<T>::~ArbolBinario() {}

/**
 * Busca un dato en el árbol. Si no esta el dato en el árbol
 * tira una excepción
 * @param clave Valor a buscar
 * @return el valor buscado
 */
template<class T>
T ArbolBinario<T>::search(T dato)
{
    return search(dato , root);
}

template<class T>
T ArbolBinario<T>::search(T dato , NodoArbol<T> *r)
{
    if(r == nullptr) //No encontro el dato
    {
        throw std::invalid_argument(dato << " no se encuentra en el texto\n");
    }

    if (r->getData() == dato)  //Encontro el dato
    {
        return r->getData();
    }

    //Recursividad
    if (r->getData() < dato)
    {
        return search(dato , r->getRight());
    }

    else
    {
        return search(dato , r->getLeft());
    }
}

/**
 * Agrega un dato al árbol
 * @param clave Clave para agregar el dato
 * @param dato Dato a agregar
 */
template<class T>
void ArbolBinario<T>::put(T dato)
{
    root = put(dato , root);
}

template<class T>
NodoArbol<T> * ArbolBinario<T>::put(T dato, NodoArbol<T> *r)
{
    if (r == nullptr)
    {
        return new NodoArbol<T>(dato);
    }

    if (r->getData() == dato)
    {
        r->aumentarOcurrencia();
    }

    if (dato > r->getData())
    {
        r->setRight(put(dato , r->getRight()));
    }

    else if (dato < r->getData())
    {
        r->setLeft(put(dato , r->getLeft()));
    }

    return r;
}

/**
 * Elimina un dato del árbol
 * @param clave Clave para identificar el nodo a borrar
 */
template<class T>
void ArbolBinario<T>::remove(T dato)
{
    root = remove(dato , root);
}

template<class T>
NodoArbol<T> * ArbolBinario<T>::remove(T dato , NodoArbol<T> *r)
{
    NodoArbol<T> *auxNodo;

    if(r == nullptr)
    {
        throw std::invalid_argument("El dato no existe\n");
    }

    if(r->getData() == dato)
    {
        if(r->getLeft() == nullptr && r->getRight() == nullptr) //Nodo Hoja (sin hijos)
        {
            delete r;
            return nullptr;
        }

        if(r->getLeft() == nullptr && r->getRight() != nullptr) //Nodo tiene un hijo a la derecha
        {
            auxNodo = r->getRight();
            delete r;
            return auxNodo;
        }

        if(r->getLeft() != nullptr && r->getRight() == nullptr) //Nodo tiene un hijo a la izquierda
        {
            auxNodo = r->getLeft();
            delete r;
            return auxNodo;
        }

        if(r->getLeft() != nullptr && r->getRight() != nullptr) //Nodo tiene hijos a ambos lados
        {
            if(r->getLeft()->getRight() != nullptr) //Hay algo a la derecha del nodo izquierdo (mínimo del máximo)
            {
                bool found;
                auxNodo = findMaxAndRemove(r->getLeft() , &found);
                auxNodo->setRight(r->getRight());
                auxNodo->setLeft(r->getLeft());
            }
            else
            {
                auxNodo = r->getLeft();
                auxNodo->setRight(r->getRight());
            }
            delete r;
            return auxNodo;
        }
    }
    else
    {
        if(r->getData() > dato)
        {
            r->setLeft(remove(dato , r->getLeft()));
        }
        else
        {
            r->setRight(remove(dato , r->getRight()));
        }
    }

    return r;
}

template<class T>
NodoArbol<T> *ArbolBinario<T>::findMaxAndRemove(NodoArbol<T> *r, bool *found)
{
    NodoArbol<T> *maxNodo;
    *found = false;

    if (r->getRight() == nullptr)
    {
        *found = true;
        return r;
    }

    maxNodo = findMaxAndRemove(r->getRight() , found);
    if (*found)
    {
        r->setRight(maxNodo->getLeft());
        *found = false;
    }
    return maxNodo;
}

/**
 * Informa si un árbol esta vacío
 * @return
 */
template<class T>
bool ArbolBinario<T>::esVacio()
{
    return root == nullptr;
}

/**
 * Recorre un árbol en preorden
 */
template<class T>
void ArbolBinario<T>::preorder()
{
    preOrder(root);

}

template<class T>
void ArbolBinario<T>::preOrder(NodoArbol<T> *r)
{
    if(r == nullptr) return;

    std::cout << r->getOcurrencia() << ' ' << r->getData() << '\n';
    preOrder(r->getLeft());
    preOrder(r->setRight());
}

/**
 * Recorre un árbol en orden
 */
template<class T>
void ArbolBinario<T>::inorder()
{
    inOrder(root);
}

template<class T>
void ArbolBinario<T>::inOrder(NodoArbol<T> *r)
{
    if(r == nullptr) return;

    inOrder(r->getLeft());
    std::cout << r->getOcurrencia() << ' ' << r->getData() << '\n';
    inOrder(r->getRight());
}

template<class T>
void ArbolBinario<T>::inOrderLimit(int &cantidad)
{
    inOrderLimit(root , cantidad);
}

template<class T>
void ArbolBinario<T>::inOrderLimit(NodoArbol<T> *r , int &cantidad)
{
    if(r == nullptr) return;

    inOrderLimit(r->getLeft() , cantidad);
    std::cout << r->getOcurrencia() << ' ' << r->getData() << '\n';
    cantidad--;

    if(cantidad == 0)
    {
        throw std::invalid_argument("Ejecucion Finalizada\n");
    }

    inOrderLimit(r->getRight() , cantidad);
}

/**
 * Recorre un árbol en postorden
 */
template<class T>
void ArbolBinario<T>::postorder()
{
    postOrder(root);
}

template<class T>
void ArbolBinario<T>::postOrder(NodoArbol<T> *r)
{
    if(r == nullptr) return;

    postOrder(r->getLeft());
    postOrder(r->getRight());
    std::cout << r->getOcurrencia() << ' ' << r->getData() << '\n';
}

/**
 * Muestra un árbol por consola
 */
template <class T>
void ArbolBinario<T>::print()
{
    if (root != NULL)
        root->print(false, "");
}

template<class T>
void ArbolBinario<T>::contarPorNivel()
{
    Lista<int> list;
    contarPorNivel(root, 0, list);

    for (int i = 0 ; i < list.getTamanio() ; i++)
    {
        std::cout << "Nivel " << i << ": " << list.getDato(i) << '\n';
    }
}

template<class T>
void ArbolBinario<T>::contarPorNivel(NodoArbol<T> *r, int nivel, Lista<int> &list)
{
    if(r == nullptr) return;

    try
    {
        list.reemplazar(nivel , list.getDato(nivel)+1);
    }
    catch (invalid_argument &Error)
    {
        list.insertarUltimo(1);
    }

    contarPorNivel(r->getLeft() , nivel+1 , list);
    contarPorNivel(r->getRight() , nivel+1 , list);
}


#endif // U05_ARBOL_ARBOL_ARBOLBINARIO_H_
