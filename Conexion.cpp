#include "Conexion.h"
#include <cstdio>
#include <cctype>

namespace UndavConexion {
    
    Conexion* CrearConexion(int p, int q) {
        Conexion* conexion = new Conexion;
        conexion->p = p;
        conexion->q = q;
        return conexion;
    }

    Conexion* CrearConexion(char* conexionPQ) {
        int p, q;
        char estaDemas;
        
        int cantidadLeida=sscanf(conexionPQ, "%d-%d %c", &p, &q, &estaDemas);
        if (cantidadLeida != 2) {
            return NULL;
        }

        return CrearConexion(p, q);
    }
    
    int ObtenerP(const Conexion* conexion) {
        return conexion->p;
    }
    
    int ObtenerQ(const Conexion* conexion) {
        return conexion->q;
    }

    void DestruirConexion(Conexion* conexion) {
        delete conexion;
    }
}
