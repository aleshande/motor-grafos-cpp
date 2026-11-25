# Motor de Parseo y Grafos No Dirigidos en C++

Implementación modular en C++ de un sistema de lectura, validación y construcción de **Grafos No Dirigidos** a partir de archivos de texto plano, desarrollado bajo el paradigma de Tipos Abstractos de Datos (TADs) con gestión manual de memoria dinámica.

## Arquitectura del Proyecto

El sistema está desacoplado en módulos independientes con ocultamiento de información (punteros opacos) e iteradores propios:

* **`UndavArchivoTexto` (`ArchivoTexto.h/.cpp`):** Lectura binaria de archivos `.txt`, sanitización de espacios/caracteres inválidos y validación de formato `<entero>-<entero>`.
* **`UndavParserConexiones` (`ParserConexiones.h/.cpp`):** Transformación del contenido limpio en estructuras de conexión en memoria.
* **`UndavConexion` (`Conexion.h/.cpp`):** Representación de una arista entre dos vértices enteros (`p-q`).
* **`UndavConjuntoConexion` (`ConjuntoConexiones.h/.cpp`):** Colección dinámica redimensionable sin duplicados (considerando bidireccionalidad) con su propio `IteradorConjunto`.
* **`UndavDiccionario` (`Diccionario.h/.cpp`):** Estructura asociativa clave-valor para indexar vértices y listas de adyacencia.
* **`UndavGrafo` (`Grafo.h/.cpp`):** Implementación del TAD Grafo con inserción de vértices, adyacencias e iteradores.
* **`UndavFactoryGrafos` (`FactoryGrafos.h/.cpp`):** Fábrica encargada de instanciar grafos dirigidos o no dirigidos a partir de un conjunto de conexiones.

## Compilación y Ejecución

Desde la carpeta raíz del proyecto, ejecutá:

    g++ -std=c++14 *.cpp -o grafos
    ./grafos

*(En Windows, ejecutá `grafos.exe` en lugar de `./grafos`)*

## Ejemplo de Entrada y Salida

Dado un archivo `conexiones1.txt` con formato libre (tolerante a espacios y líneas vacías):

    61-25
    26-3
    45- 65
    16-26

El programa construye el grafo no dirigido registrando ambos sentidos de cada arista:

    Grafo [0]:

    3-26 16-26 25-61 26-3 26-16 45-65 61-25 65-45

## Próximos Pasos

* Implementar detección de componentes conexas / bosques mediante algoritmos de recorrido (BFS/DFS) o estructuras *Union-Find*.