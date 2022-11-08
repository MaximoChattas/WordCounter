# Word Counter

---

## Resumen:

La aplicación tiene varias funcionalidades que permiten obtener información
de interés sobre un archivo de texto (tipo .txt). Además, esta puede ser utilizada para el ordenamiento y
búsqueda de información según varios criterios, permitiendo además utilizar
ciertos filtros para eliminar resultados no deseados o irrelevantes de la búsqueda. A continuación 
se detallarán todas sus funcionalidades, junto con un instructivo sobre cómo utilizar
cada una de ellas.

## Funcionalidades:

- Conteo:
  - Caracteres
  - Letras
  - Palabras
  - Palabras Diferentes
  - Lineas


- Ordenamiento:
  - Alfabético
  - Cantidad de Ocurrencias


- Búsqueda:
  - Palabras específicas (ordenadas por ocurrencias)


- Filtros:
  - Exclusión de Palabras específicas
  - Exclusión todas las palabras de un archivo .txt

## Manual de Usuario

En primer lugar, para poder aprovechar las funcionalidades ofrecidas
por la aplicación, debe asegurarse de que tiene un archivo de tipo .txt
en la misma carpeta en la que tiene instalada la app. Este archivo será
el punto de partida para el análisis de datos.

Antes de comenzar a usar la aplicación, se recomienda compilar 
nuevamente el código, para garantizar que está utilizando la última
versión disponible. Esto evitará problemas de funcionalidad y compatibilidad.

Para compilar el código, en su terminal de Mac corra el siguiente comando:

`g++ main.cpp -o main`

### Conteo

Esta función le informará la cantidad de caracteres, letras, palabras,
palabras diferentes y líneas que tiene en su archivo de texto. Para utilizar esta función, en la terminal, 
corra el siguiente comando:

`./main [nombre_archivo.txt]`

### Ordenamiento Alfabético

Esta función ordenará alfabéticamente [A-Z] todas las palabras en su archivo, mostrando además, la cantidad
de veces que aparece cada una de ellas. Para utilizar esta función, en la terminal, corra el
siguiente comando:

`./main [nombre_archivo.txt] -palabras`

Además, puede agregar un número al final si quiere limitar la cantidad de palabras a mostrar.
Si elige un número mayor a la cantidad de palabras diferentes, se mostrarán todas las palabras
disponibles y el sistema le informará que no hay la suficiente cantidad de palabras. Si ingresa 0
se mostraran todas las palabras del texto.

`./main [nombre_archivo.txt] -palabras n`

siendo n el número de palabras que se mostrarán

### Ordenamiento por Ocurrencias

Esta función ordenará descendientemente todas las palabras en su archivo según la cantidad de veces que aparezca
en el mismo. Para utilizar esta función, en la terminal, corra el siguiente comando:

`./main [nombre_archivo.txt] -ocurrencias`

Además, puede agregar un número al final si quiere limitar la cantidad de palabras a mostrar.
Si elige un número mayor a la cantidad de palabras diferentes, se mostrarán todas las palabras
disponibles y el sistema le informará que no hay la suficiente cantidad de palabras. Si ingresa 0
se mostraran todas las palabras del texto.

`./main [nombre_archivo.txt] -ocurrencias n`

siendo n el número de palabras que se mostrarán


### Búsqueda de Palabras

Esta función permite buscar ciertas palabras dentro del texto y las mostrará ordenadas según la cantidad de veces 
que aparezca en el mismo. Si intenta buscar una palabra que no se encuentra en el archivo, el sistema se lo notificará.
Para utilizar esta función, en la terminal, corra el siguiente comando:

`./main [nombre_archivo.txt] -mostrar "palabras a mostrar"`

donde las palabras que desea buscar deben estar encerradas por comillas dobles y separadas entre ellas por un espacio.

### Filtro de Palabras Específicas

Esta función modifica a las funciones de ordenamiento, de modo que ciertas palabras especificadas por el usuario no son
mostradas. Para utilizar esta función, en la terminal, corra alguno de los siguientes comandos, dependiendo de cuál es
la función a la cual le quiere modificar su comportamiento:

`./main [nombre_archivo.txt] -palabras -excluir "palabras a excluir"`

`./main [nombre_archivo.txt] -ocurrencias -excluir "palabras a excluir"`

donde las palabras que desea excluir deben estar encerradas por comillas dobles y separadas entre ellas por un espacio.

### Filtro de Palabras en un Archivo .txt

Esta función modifica a las funciones de ordenamiento, de modo todas las palabras que se encuentren en un segundo
archivo .txt especificado por el usuario, no son mostradas. Para utilizar esta función, en la terminal, corra alguno de 
los siguientes comandos, dependiendo de cuál es la función a la cual le quiere modificar su comportamiento:

`./main [nombre_archivo.txt] -palabras -excluirf [nombre_archivo_a_excluir.txt]`

`./main [nombre_archivo.txt] -ocurrencias -excluirf [nombre_archivo_a_excluir.txt]`