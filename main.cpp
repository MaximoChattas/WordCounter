#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include "Arbol/ArbolBinario.h"
#include "HashMap/HashMapList.h"

using namespace std;

void deletePunctuation(string &a);
void counter(char* file);
void alphabeticalOrder(char* file);
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
        alphabeticalOrder(argv[1]);
    }

    clock_t end = clock();

    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    cout << "Tardo elapsed_secs" << elapsed_secs << "\n" << std::endl;
    return 0;
}

void counter(char* file)
{
    HashMapList<string , unsigned int> hash(100, hashfunc);
    //Implementar Funcion Hash para determinar cantidad de palabras diferentes.

    std::ifstream archivo; //Archivo de Texto a Leer

    std::string auxLinea; //Linea de texto a analizar

    unsigned int lineas = 0 , caracteres = 0 , palabras = 0; //Counters

    archivo.open(file);

    if(archivo.is_open())
    {
        while (archivo.peek() != EOF)
        {
            std::getline(archivo , auxLinea); //Se obtiene la linea
            lineas++;

            unsigned int len = auxLinea.length();
            int prevSpace = 0;

            for (int i = 0 ; i < len ; i++) //Se recorre la linea
            {
                caracteres++;

                if (auxLinea[i] == ' ')
                {
                    palabras++; //OPTIMIZAR
//                    std::cout << auxLinea.substr(prevSpace , i-prevSpace);
                    prevSpace = i+1;
                }
            }

            if(auxLinea[len - 1] != ' ')
            {
                palabras++;
//                std::cout << auxLinea.substr(prevSpace , len-prevSpace);
            }
        }

        std::cout << "Lineas: " << lineas << '\n';
        std::cout << "Palabras: " << palabras << '\n';
        std::cout << "Caracteres: " << caracteres << '\n';
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