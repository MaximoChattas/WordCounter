#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Arbol/ArbolBinario.h"
#include "HashMap/HashMapList.h"

using namespace std;

//Para Excluir palabras intentar tree.remove()

void deletePunctuation(string &a);

void counter(char* file);

void alphabeticalOrder(char* file);

void alphabeticalOrderLimit(char* file , int cantidad);

void occurrenceOrder(char* file);

void occurrenceOrderLimit(char* file , int cantidad);

unsigned int hashfunc (string word);

int main(int argc , char* argv[]) {
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

    if (argc == 3)
    {
        if(strcmp(argv[2] , "-palabras") == 0) alphabeticalOrder(argv[1]);

        if(strcmp(argv[2] , "-ocurrencias") == 0) occurrenceOrder(argv[1]);
    }

    if (argc == 4)
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

        if(strcmp(argv[2] , "-ocurrencias") == 0)
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

    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}

void counter(char* file)
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
        //Se realiza el conteo total de palabras, palabras diferentes y caracteresyEspacios sin espacios y sin puntuación
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
        //Se realiza el conteo de lineas y caracteresyEspacios totales
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

void alphabeticalOrder (char* file)
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
        alphOrder.inorder();
    }
    else
    {
        throw std::invalid_argument("ERROR: El archivo no fue encontrado\n");
    }

}

void alphabeticalOrderLimit (char* file , int cantidad)
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

}

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
}

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

unsigned int hashfunc (string word)
{
    unsigned int key = 1;

    for (int i = 0 ; i < word.size() ; i++)
    {
        key *= word[i];
    }
    return key % 100;
}
