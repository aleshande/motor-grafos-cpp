#include <iostream>
#include <string>
#include "ParserConexiones.h"
#include "ConjuntoConexiones.h"
#include "FactoryGrafos.h"
#include "Grafo.h"
#include "Diccionario.h"

using std::string;
using std::cout;
using std::endl;
using namespace UndavParserConexiones;
using UndavConjuntoConexion::ConjuntoConexiones;
using URGGrafo::Grafo;
using UndavDiccionario::Diccionario;

Diccionario* CrearDiccionarioGrafos(string pathArchivos[], int cantidad);
void MostrarGrafos(Grafo* grafos[], int cantidadGrafos);
void DestuirGrafos(Grafo* grafos[], int cantidadGrafos);

int main()
{
    string pathArchivos[3] = { 
        "C:\\Users\\wazaa\\OneDrive\\Desktop\\alex\\programacion I\\TP C++\\MaterialEntrega2\\conexiones1.txt", 
        "C:\\Users\\wazaa\\OneDrive\\Desktop\\alex\\programacion I\\TP C++\\MaterialEntrega2\\conexiones2.txt", 
        "C:\\Users\\wazaa\\OneDrive\\Desktop\\alex\\programacion I\\TP C++\\MaterialEntrega2\\conexiones3.txt" 
    };
    Diccionario* diccionarioGrafos = CrearDiccionarioGrafos(pathArchivos, 3);
    Grafo* grafos[3];
    for (int i = 0; i < 3; ++i) {
        grafos[i] = (Grafo*)UndavDiccionario::Obtener(diccionarioGrafos, pathArchivos[i]);
    }
    MostrarGrafos(grafos, 3);

    UndavDiccionario::DestruirDiccionario(diccionarioGrafos);
    DestuirGrafos(grafos, 3);
}

Diccionario* CrearDiccionarioGrafos(string pathArchivos[], int cantidad) {
    Diccionario* diccionario = UndavDiccionario::CrearDiccionario();
    for (int i = 0;i < cantidad;++i) {
        // Parsear cada archivo a un conjunto de conexiones
        ConjuntoConexiones* conexiones = UndavParserConexiones::ParsearArchivoConexiones(pathArchivos[i].c_str());
        // Por cada conjunto de conexiones creamos un Grafo
        Grafo* grafo = UndavFactoryGrafos::CrearGrafo(conexiones);
        //Cargamos el grafo en un diccionario, poniendole como clave el nombre del arhivo
        UndavDiccionario::Agregar(diccionario, pathArchivos[i], grafo);
        // Ya no necesitamos el conjunto de conexiones
        UndavConjuntoConexion::DestruirConjunto(conexiones);
    }

    return diccionario;
}

void MostrarGrafos(Grafo* grafos[], int cantidadGrafos) {
    for (int i = 0; i < cantidadGrafos;++i) {
        cout << "Grafo [" << i << "]:" << endl<<endl;
        cout << URGGrafo::ObtenerAristas(grafos[i]) << endl << endl;
    }
}

void DestuirGrafos(Grafo* grafos[], int cantidadGrafos) {
    for (int i = 0; i < cantidadGrafos;++i) {
        URGGrafo::DestruirGrafo(grafos[i]);
    }
}
