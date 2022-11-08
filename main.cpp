#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Arbol/ArbolBinario.h"
#include "HashMap/HashMapList.h"

using namespace std;

//Para Excluir palabras intentar tree.remove()

void counter(char *file);

void alphabeticalOrder(char *file);

void alphabeticalOrderLimit(char *file , int cantidad);

void alphabeticalOrderIgnore(char *file , char *toignore);

void occurrenceOrder(char *file);

void occurrenceOrderLimit(char *file , int cantidad);

void occurrenceOrderIgnore(char *file , char *toignore);

void mostrar(char *file , char *words);

void deletePunctuation(string &a);

unsigned int hashfunc (string word);


int main(int argc , char *argv[]) {
    clock_t begin;

    cout << "Comenzando a medir Tiempo\n" << endl;

    begin = clock();

    /*
     * Insertar código a medir tiempo aquí
     */
    if (argc == 2)
    {
        counter(argv[1]);
    }

    else if (argc == 3)
    {
        if(strcmp(argv[2] , "-palabras") == 0) alphabeticalOrder(argv[1]);

        else if(strcmp(argv[2] , "-ocurrencias") == 0) occurrenceOrder(argv[1]);

        else cout << "Ingrese un Argumento Valido (ver instrucciones)\n";
    }

    else if (argc == 4)
    {
        if(strcmp(argv[2] , "-palabras") == 0)
        {
            if(strcmp(argv[3] , "0") == 0) alphabeticalOrder(argv[1]); //Mostrar Todas las palabras

            else
            {
                std::istringstream iss( argv[3] ); //Convertir de String a Int para poder utilizarlo
                int val;

                if (iss >> val)
                {
                    alphabeticalOrderLimit(argv[1] , val);
                }
                else
                {
                    cout << "Ingrese un Argumento Valido (ver instrucciones)\n";
                }
            }
        }

        else if(strcmp(argv[2] , "-ocurrencias") == 0)
        {
            if(strcmp(argv[3] , "0") == 0) occurrenceOrder(argv[1]); //Mostrar Todas las palabras

            else
            {
                std::istringstream iss( argv[3] ); //Convertir de String a Int para poder utilizarlo
                int val;

                if (iss >> val)
                {
                    occurrenceOrderLimit(argv[1] , val);
                }
                else
                {
                    cout << "Ingrese un Argumento Valido (ver instrucciones)\n";
                }
            }
        }

        else if (strcmp(argv[2] , "-mostrar") == 0)
        {
            mostrar(argv[1] , argv[3]);
        }

        else cout << "Ingrese un Argumento Valido (ver instrucciones)\n";

    }

    else if (argc == 5)
    {
        if(strcmp(argv[2] , "-palabras") == 0)
        {
            if(strcmp(argv[3] , "-excluir") == 0) alphabeticalOrderIgnore(argv[1] , argv[4]); //Mostrar Todas las palabras

        }

        else if(strcmp(argv[2] , "-ocurrencias") == 0)
        {
            if(strcmp(argv[3] , "-excluir") == 0) occurrenceOrderIgnore(argv[1] , argv[4]);
        }

        else cout << "Ingrese un Argumento Valido (ver instrucciones)\n";

    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}

/**
 * Contador de Letras, Caracteres, Lineas, Palabras y Palabras Diferentes
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 */
void counter(char *file)
{
    HashMapList<string , string> hash(10000, hashfunc);
    //Implementar Funcion Hash para determinar cantidad de palabras diferentes.

    std::ifstream archivo; //Archivo de Texto a Leer

    std::string auxLinea , auxWord; //Linea de texto a analizar

    int lineas = 0 , caracteresyEspacios = 0 , caracteres = 0 , palabras = 0 , palabrasDiferentes = 0; //Counters

    archivo.open(file);

    if(archivo.is_open())
    {
        //Recorrido palabra a palabra
        //Se realiza el conteo total de palabras, palabras diferentes y caracteres sin espacios y sin puntuación
        while (archivo >> auxWord)
        {
            palabras++;
            deletePunctuation(auxWord);
            caracteres+= auxWord.size();
            try
            {
                hash.put(auxWord , auxWord);
            }
            catch (std::invalid_argument &Error)
            {
                palabrasDiferentes--;
            }
        }

        palabrasDiferentes += palabras;

        archivo.clear();
        archivo.seekg(0 , ios::beg);

        //Recorrido linea por linea
        //Se realiza el conteo de lineas y caracteres totales
        while (archivo.peek() != EOF)
        {
            std::getline(archivo , auxLinea); //Se obtiene la linea
            lineas++;
            caracteresyEspacios += auxLinea.size();
        }

        std::cout << "Lineas: " << lineas << '\n';
        std::cout << "Palabras: " << palabras << '\n';
        std::cout << "Palabras Diferentes: " << palabrasDiferentes << '\n';
        std::cout << "Caracteres con Espacios: " << caracteresyEspacios << '\n';
        std::cout << "Caracteres sin Espacios: " << caracteres << '\n';

    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }

}

/**
 * Muestra todas las palabras del texto en orden alfabético
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 */
void alphabeticalOrder (char *file)
{
    ArbolBinario<string> alphOrder;
    std::ifstream textFile;
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            alphOrder.put(auxString);

        }
        alphOrder.inorder();
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }

}

/**
 * Muestra las primeras n palabras en orden alfabético
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 * @param cantidad cantidad de palabras a mostrar en orden alfabético
 */
void alphabeticalOrderLimit (char *file , int cantidad)
{
    ArbolBinario<string> alphOrder;
    std::ifstream textFile; //Text File to Read
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            alphOrder.put(auxString);
        }

        try
        {
            alphOrder.inOrderLimit(cantidad);
            std::cout << "No hay la cantidad suficiente de palabras para mostrar\n";
        }
        catch (std::invalid_argument &Error){}

    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }

}

/**
 * Muestra todas las palabras del texto en orden alfabético excepto las palabras indicadas que deben ser excluidas
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 */
void alphabeticalOrderIgnore (char *file , char* toignore)
{
    ArbolBinario<string> alphOrder;
    std::ifstream textFile;
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            alphOrder.put(auxString);

        }

        int size = strlen(toignore);
        for (int i = 0 ; i < size ; i++)
        {
            string word;
            while(toignore[i] != ' ' && toignore[i] != '\0')
            {
                word+= toignore[i]; //Se obtiene cada una de las palabras
                i++;
            }
            deletePunctuation(word);

            try
            {
                //Se elimina la palabra del arbol
                alphOrder.remove(word);
            }
            catch (std::invalid_argument &ERROR){}
        }

        alphOrder.inorder();
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }

}

/**
 * Muestra todas las palabras del texto ordenadas descendientemente según la cantidad de veces que aparece
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 */
void occurrenceOrder(char *file)
{
    ArbolBinario<string> occurenceOrder;
    HashMapList<string , string> hash(10000, hashfunc);
    std::ifstream textFile; //Text File to Read
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        //Se recorre el texto, se ingresan las palabras en una tabla Hash para obtener las ocurrencias de cada una
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            hash.putOcurrencias(auxString , auxString);
        }

        textFile.clear();
        textFile.seekg(0 , ios::beg);

        //CAMBIAR POR FUNC. DENTRO DE HASH
        //Se recorre nuevamente el texto, se ingresan las palabras en un árbol ordenadas por ocurrencias
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);
            HashEntry<string , string> auxEntry = hash.get(auxString);

            string data = auxEntry.getValor();
            int ocurrencia = auxEntry.getOcurrencias();

            occurenceOrder.putOcurrencias(data , ocurrencia);
        }

        occurenceOrder.inorder();
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }
}

/**
 * Muestra las primeras n palabras en orden de ocurrencias
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 * @param cantidad cantidad de palabras a mostrar en orden de ocurrencias
 */
void occurrenceOrderLimit(char *file, int cantidad)
{
    ArbolBinario<string> occurenceOrder;
    HashMapList<string , string> hash(10000, hashfunc);
    std::ifstream textFile; //Text File to Read
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        //Se recorre el texto, se ingresan las palabras en una tabla Hash para obtener las ocurrencias de cada una
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            hash.putOcurrencias(auxString , auxString);
        }

        textFile.clear();
        textFile.seekg(0 , ios::beg);

        //Se recorre nuevamente el texto, se ingresan las palabras en un árbol ordenadas por ocurrencias
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);
            HashEntry<string , string> auxEntry = hash.get(auxString);

            string data = auxEntry.getValor();
            int ocurrencia = auxEntry.getOcurrencias();

            occurenceOrder.putOcurrencias(data , ocurrencia);
        }

        try
        {
            occurenceOrder.inOrderLimit(cantidad);
            std::cout << "No hay la cantidad suficiente de palabras para mostrar\n";
        }
        catch (std::invalid_argument &Error){}
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }
}

/**
 * Muestra todas las palabras del texto ordenadas descendientemente según la cantidad de veces que aparece excepto
 * las palabras indicadas que deben ser excluidas
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 */
void occurrenceOrderIgnore(char *file , char *toignore)
{
    ArbolBinario<string> occurenceOrder;
    HashMapList<string , string> hash(10000, hashfunc);
    std::ifstream textFile; //Text File to Read
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        //Se recorre el texto, se ingresan las palabras en una tabla Hash para obtener las ocurrencias de cada una
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            hash.putOcurrencias(auxString , auxString);
        }

        textFile.clear();
        textFile.seekg(0 , ios::beg);

        //CAMBIAR POR FUNC. DENTRO DE HASH
        //Se recorre nuevamente el texto, se ingresan las palabras en un árbol ordenadas por ocurrencias
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);
            HashEntry<string , string> auxEntry = hash.get(auxString);

            string data = auxEntry.getValor();
            int ocurrencia = auxEntry.getOcurrencias();

            occurenceOrder.putOcurrencias(data , ocurrencia);
        }

        int size = strlen(toignore);
        for (int i = 0 ; i < size ; i++)
        {
            string word;
            while(toignore[i] != ' ' && toignore[i] != '\0')
            {
                word+= toignore[i]; //Se obtiene cada una de las palabras
                i++;
            }
            deletePunctuation(word);

            try
            {
                //Se elimina la palabra del arbol
                occurenceOrder.remove(word);
            }
            catch (std::invalid_argument &ERROR){}
        }

        occurenceOrder.inorder();
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }
}

/**
 * Muestra las palabras indicadas ordenadas por ocurrencia
 * @param file cadena de caracteres que contiene el nombre del archivo a leer
 * @param words cadena de caracteres con las palabras a mostrar
 */
void mostrar(char *file, char *words)
{
    ArbolBinario<string> occurenceOrder;
    HashMapList<string , string> hash(10000, hashfunc);
    std::ifstream textFile; //Text File to Read
    std::string auxString;

    textFile.open(file);

    if(textFile.is_open())
    {
        //Se recorre el texto, se ingresan las palabras en una tabla Hash para obtener las ocurrencias de cada una
        while (textFile >> auxString)
        {
            deletePunctuation(auxString);

            hash.putOcurrencias(auxString, auxString);
        }

        int size = strlen(words);
        for (int i = 0 ; i < size ; i++)
        {
            string word;
            while(words[i] != ' ' && words[i] != '\0')
            {
                word+= words[i]; //Se obtiene cada una de las palabras
                i++;
            }
            deletePunctuation(word);

            try
            {
                //Se obtiene la cantidad de ocurrencias de esa palabra y se ingresa en un arbol
                HashEntry<string , string> toTree = hash.get(word);
                int ocurrencias = toTree.getOcurrencias();
                occurenceOrder.putOcurrencias(word , ocurrencias);
            }
            catch (std::invalid_argument &ERROR)
            {
                std::cout << word << " no se encuentra en el texto\n";
            }
        }

        occurenceOrder.inorder();

    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }
}

/**
 * Elimina los signos de puntuación y mayúsculas de una cadena de caracteres pasada por referencia
 * @param a string con caracteres a eliminar
 */
void deletePunctuation(string &a)
{
    unsigned int len = a.size();

    for (unsigned int i = 0 ; i < len; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z') a[i]+=32; //Minuscula

        else if (ispunct(a[i])) //Puntuacion
        {
            a.erase(i--, 1);
            len = a.size();
        }
    }

}

/**
 * Función de Hash que determina la posición dentro de la tabla de un string
 * @param word dato que determina la posición dentro del hash
 */
unsigned int hashfunc (string word)
{
    unsigned int key = 1;

    for (int i = 0 ; i < word.size() ; i++)
    {
        key *= word[i];
    }
    return key % 10000;
}
