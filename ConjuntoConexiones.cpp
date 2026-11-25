#include "ConjuntoConexiones.h"
#include "Conexion.h"      
#include <cstddef>       
#include <iostream>

namespace UndavConjuntoConexion {
	
	struct ConjuntoConexiones {
		Conexion** items;
		int cantidadItems;
		int capacidad;
	};
	
	//precondicion: a y b apuntan a instancias validas de tipo Conexion.
	//postcondicion: devuelve true cuando Conexion* a alberga los mismos enteros que Conexion* b, las conexiones son bidireccionales. 
	bool SonIguales(Conexion* a, Conexion* b){
		// CORRECCIÓN: Usar las primitivas del módulo Conexion en lugar de acceder directamente a los miembros
        int p_a = UndavConexion::ObtenerP(a);
        int q_a = UndavConexion::ObtenerQ(a);
        int p_b = UndavConexion::ObtenerP(b);
        int q_b = UndavConexion::ObtenerQ(b);
		return (p_a == p_b && q_a == q_b) || (p_a == q_b && q_a == p_b);
	}

	ConjuntoConexiones* CrearConjuntoVacio() {
		ConjuntoConexiones* conjunto=new ConjuntoConexiones;
		conjunto->capacidad=5;
		conjunto->cantidadItems=0;
		conjunto->items=new Conexion*[conjunto->capacidad];
		conjunto->items[0]=NULL;
		return conjunto;
	}
	
	void AgregarConexion(ConjuntoConexiones* conjunto, Conexion* item) {
		if (conjunto->cantidadItems > 0) {
			Iterador::IteradorConjunto* it= Iterador::Comienzo(conjunto);
			while (!Iterador::EsFin(it)) {
				Conexion* conexionActual= Iterador::ObtenerItem(it);
				if (SonIguales(conexionActual, item)) {
					Iterador::DestruirIterador(it);
					return;
				}
				Iterador::Siguiente(it);
			}
			Iterador::DestruirIterador(it);
		}

		if (conjunto->cantidadItems+1 >= conjunto->capacidad) { 
			conjunto->capacidad*=2;
			Conexion** nuevoItems=new Conexion*[conjunto->capacidad];
			for (int i=0; i<conjunto->cantidadItems; ++i)
				nuevoItems[i]=conjunto->items[i];
			delete[] conjunto->items;
			conjunto->items=nuevoItems;
		}

		conjunto->items[conjunto->cantidadItems++] = item;
		conjunto->items[conjunto->cantidadItems] = NULL;
	}

	Conexion* QuitarConexion(ConjuntoConexiones* conjunto) {
		if (conjunto->cantidadItems == 0)
			return NULL;
		Conexion* quitada=conjunto->items[conjunto->cantidadItems - 1];
		conjunto->items[--conjunto->cantidadItems] = NULL; 
		return quitada;
	}

	namespace Iterador {

		struct IteradorConjunto {
			ConjuntoConexiones* conjunto;
			int indiceActual;
		};

		IteradorConjunto* Comienzo(ConjuntoConexiones* conjunto) {
			IteradorConjunto* it = new IteradorConjunto;
			it->conjunto = conjunto;
			it->indiceActual = 0;
			return it;
		}

		Conexion* ObtenerItem(IteradorConjunto* iterador) {
			if (iterador->indiceActual < iterador->conjunto->cantidadItems)
				return iterador->conjunto->items[iterador->indiceActual];
			return NULL;
		}

		void Siguiente(IteradorConjunto* iterador) {
			iterador->indiceActual++;
		}

		bool EsFin(IteradorConjunto* iterador) {
			return iterador->indiceActual >= iterador->conjunto->cantidadItems;
		}

		void DestruirIterador(IteradorConjunto* iterador) {
			delete iterador;
		}
	}

	void DestruirConjunto(ConjuntoConexiones* conjunto) {
		Iterador::IteradorConjunto* it = Iterador::Comienzo(conjunto);
		while (!Iterador::EsFin(it)) {
			Conexion* conexionActual=Iterador::ObtenerItem(it);
			delete conexionActual;
			Iterador::Siguiente(it);
		}
		Iterador::DestruirIterador(it);

		delete[] conjunto->items;
		delete conjunto;
	}
}