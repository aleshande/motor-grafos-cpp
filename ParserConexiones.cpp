#include "ParserConexiones.h"
#include "ConjuntoConexiones.h"
#include "Conexion.h"
#include "ArchivoTexto.h" 
#include <cstdio>
#include <cstring>
#include <iostream>

#define TOPECAMPO 32 

using UndavConjuntoConexion::ConjuntoConexiones;
using UndavConexion::Conexion;

namespace UndavParserConexiones {
    
    ConjuntoConexiones* ParsearArchivoConexiones(const char* pathArchivo) {
        
        // 1. Obtener el contenido limpio ("p1-q1\np2-q2\n...pN-qN\0")
        char* contenidoLimpio = UndavArchivoTexto::ObtenerContenidoLimpio(pathArchivo);
        
        if (contenidoLimpio == NULL) {
            return NULL; 
        }
        
        ConjuntoConexiones* conexiones = UndavConjuntoConexion::CrearConjuntoVacio();
        
        char* iterador = contenidoLimpio;
        char* inicio_conexion = contenidoLimpio;
        char bufferConexion[TOPECAMPO];
        
        // 2. Iterar y separar conexiones por el delimitador '\n'
        while (*iterador != '\0') {
            
            if (*iterador == '\n') {
                // Se encontró el final de una conexión.
                size_t longitud = iterador - inicio_conexion;
                
                if (longitud > 0 && longitud < TOPECAMPO) {
                    strncpy(bufferConexion, inicio_conexion, longitud);
                    bufferConexion[longitud] = '\0'; 
                    
                    // Crear y agregar
                    Conexion* nuevaConexion = UndavConexion::CrearConexion(bufferConexion);
                    if (nuevaConexion != NULL) {
                        UndavConjuntoConexion::AgregarConexion(conexiones, nuevaConexion);
                    }
                }
                
                inicio_conexion = iterador + 1; // Avanza al inicio del siguiente campo
            }
            
            iterador++;
        }
        
        // 3. Procesar la ÚLTIMA conexión (si el archivo no termina en '\n')
        if (*inicio_conexion != '\0') {
            size_t longitud = iterador - inicio_conexion;
            
            if (longitud > 0 && longitud < TOPECAMPO) {
                strncpy(bufferConexion, inicio_conexion, longitud);
                bufferConexion[longitud] = '\0';
                
                Conexion* nuevaConexion = UndavConexion::CrearConexion(bufferConexion);
                if (nuevaConexion != NULL) {
                    UndavConjuntoConexion::AgregarConexion(conexiones, nuevaConexion);
                }
            }
        }
        
        // 4. Liberar la memoria
        delete[] contenidoLimpio;

        return conexiones;
    }
}