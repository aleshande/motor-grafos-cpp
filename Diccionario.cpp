#include "Diccionario.h" // <-- Incluye las definiciones de struct desde el .h
#include <iostream>
#include <string> 
#include <cstdlib> // Para NULL

// Usamos 'using namespace std;' aquí en el .cpp para que 'string' funcione
using namespace std; 

namespace UndavDiccionario {

    // --- NO HAY DEFINICIÓN DE ESTRUCTURAS AQUÍ ---
    // (Ya están en Diccionario.h, borrarlas de aquí arregla la REDEFINICIÓN)
    
    // Función auxiliar:
	static NodoDiccionario* BuscarNodoPorClave(const Diccionario* diccionario, string clave) {
		NodoDiccionario* iterador = diccionario->primerNodo;
		while (iterador != NULL) {
            // Esto compila porque la definición de NodoDiccionario vino del .h
			if (iterador->clave == clave) { 
				return iterador;
			}
			iterador = iterador->siguiente;
		}
		return NULL;
	}

    // --- Implementación de Primitivas ---
    // Las firmas ahora coinciden con el .h

	Diccionario* CrearDiccionario() {
		Diccionario* nuevoDiccionario = new Diccionario;
		nuevoDiccionario->primerNodo = NULL;
		nuevoDiccionario->cantidad = 0;
		return nuevoDiccionario;
	}

	void Agregar(Diccionario* diccionario, string clave, void* valor) {
		NodoDiccionario* nodoExistente = BuscarNodoPorClave(diccionario, clave);

		if (nodoExistente != NULL) {
			nodoExistente->valor = valor;
		} else {
			NodoDiccionario* nuevoNodo = new NodoDiccionario;
			nuevoNodo->clave = clave; 
			nuevoNodo->valor = valor;
			
			nuevoNodo->siguiente = diccionario->primerNodo;
			diccionario->primerNodo = nuevoNodo;
			diccionario->cantidad++;
		}
	}

	void Quitar(Diccionario* diccionario, string clave) {
		NodoDiccionario* actual = diccionario->primerNodo;
		NodoDiccionario* anterior = NULL;

		while (actual != NULL) {
			if (actual->clave == clave) {
				if (anterior == NULL) {
					diccionario->primerNodo = actual->siguiente;
				} else {
					anterior->siguiente = actual->siguiente;
				}
				
				delete actual;
				diccionario->cantidad--;
				return; 
			}
			
			anterior = actual;
			actual = actual->siguiente;
		}
	}

	void* Obtener(Diccionario* diccionario, string clave) {
		NodoDiccionario* nodo = BuscarNodoPorClave(diccionario, clave);
		if (nodo != NULL) {
			return nodo->valor;
		}
		return NULL;
	}

	bool Contiene(const Diccionario* diccionario, string clave) {
		return BuscarNodoPorClave(diccionario, clave) != NULL;
	}

	int CantidadElementos(const Diccionario* diccionario) {
		return diccionario->cantidad;
	}
	
	void DestruirDiccionario(Diccionario* diccionario) {
		if (diccionario == NULL) return; 
		
		NodoDiccionario* actual = diccionario->primerNodo;
		NodoDiccionario* aBorrar;

		while (actual != NULL) {
			aBorrar = actual;
			actual = actual->siguiente;
			delete aBorrar; 
		}

		delete diccionario;
	}
}
