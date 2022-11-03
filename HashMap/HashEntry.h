#ifndef U05_HASH_HASHMAP_HASHENTRY_H_
#define U05_HASH_HASHMAP_HASHENTRY_H_

template <class K, class T> class HashEntry {
private:
    K clave;
    T valor;
    int ocurrencias;
public:
    HashEntry(){}

    HashEntry(K clave , T valor)
    {
        this->clave = clave;
        this->valor = valor;
        ocurrencias = 1;
    }

    K getClave()
    {
        return this->clave;
    }

    void setClave(K clave)
    {
        this->clave = clave;
    }

    T getValor()
    {
        return this->valor;
    }

    void setValor(T valor)
    {
        this->valor = valor;
    }

    int getOcurrencias()
    {
        return ocurrencias;
    }

    void setOcurrencias(int ocurrencias)
    {
        this->ocurrencias = ocurrencias;
    }
};

#endif // U05_HASH_HASHMAP_HASHENTRY_H_
