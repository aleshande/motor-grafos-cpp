#include "FactoryGrafos.h"
#include "Grafo.h"
#include "ConjuntoConexiones.h"
#include "Conexion.h"
#include <algorithm> // Para std::max si se usara, aunque el bucle es mejor para listas

using URGGrafo::Grafo;
using UndavConjuntoConexion::ConjuntoConexiones;
using UndavConjuntoConexion::Iterador::IteradorConjunto;
using UndavConexion::Conexion;

namespace UndavFactoryGrafos {

	// Implementación auxiliar: Se definió en FactoryGrafos.h como prototipo
	int ObtenerCantidadVertices(ConjuntoConexiones* conjunto) {
		int maxVertice = -1;
		
		// Seguridad: si el conjunto es NULL (por fallo de parseo), devolver 0.
		if (conjunto == NULL) return 0;
		
		IteradorConjunto* it = UndavConjuntoConexion::Iterador::Comienzo(conjunto);
		
		while (!UndavConjuntoConexion::Iterador::EsFin(it)) {
			Conexion* conexion = UndavConjuntoConexion::Iterador::ObtenerItem(it);
			
			int p = UndavConexion::ObtenerP(conexion);
			int q = UndavConexion::ObtenerQ(conexion);
			
			if (p > maxVertice) maxVertice = p;
			if (q > maxVertice) maxVertice = q;

			UndavConjuntoConexion::Iterador::Siguiente(it);
		}
		
		UndavConjuntoConexion::Iterador::DestruirIterador(it);
		
		// Si el máximo es N, necesitamos N+1 vértices (de 0 a N).
		return maxVertice + 1;
	}

	Grafo* CrearGrafo(ConjuntoConexiones* conjunto) {
		
		if (conjunto == NULL) {
            return NULL;
        }
        
		int cantidadVertices = ObtenerCantidadVertices(conjunto);
		
		// 1. Crear un grafo NO DIRIGIDO.
		Grafo* nuevoGrafo = URGGrafo::CrearGrafoNoDirigido("Grafo Generado", cantidadVertices);
		
        if (nuevoGrafo == NULL) {
            return NULL;
        }
        
		// 2. Conectar las aristas.
		IteradorConjunto* it = UndavConjuntoConexion::Iterador::Comienzo(conjunto);

		while (!UndavConjuntoConexion::Iterador::EsFin(it)) {
			Conexion* conexion = UndavConjuntoConexion::Iterador::ObtenerItem(it);
			
			int verticeOrigen = UndavConexion::ObtenerP(conexion);
			int verticeDestino = UndavConexion::ObtenerQ(conexion);
			
			// Conectar la arista (p, q).
			URGGrafo::Conectar(nuevoGrafo, verticeOrigen, verticeDestino);

			UndavConjuntoConexion::Iterador::Siguiente(it);
		}

		UndavConjuntoConexion::Iterador::DestruirIterador(it);
		
		return nuevoGrafo;
	}
}