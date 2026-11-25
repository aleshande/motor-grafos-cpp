#ifndef DICCIONARIO_H_
#define DICCIONARIO_H_

#include <string> // Necesario para std::string

namespace UndavDiccionario {
	
	// --- DEFINICIÓN DE ESTRUCTURAS INTERNAS (DEBEN ESTAR AQUÍ) ---
	struct NodoDiccionario {
		std::string clave; 
		void* valor;
		NodoDiccionario* siguiente;
	};
	
	struct Diccionario {
		NodoDiccionario* primerNodo;
		int cantidad;
	};
    // --------------------------------------------------------

	// --- Prototipos de Funciones Públicas ---
	Diccionario* CrearDiccionario();

	void Agregar(Diccionario* diccionario, std::string clave, void* valor);

	void Quitar(Diccionario* diccionario, std::string clave);

	void* Obtener(Diccionario* diccionario, std::string clave);

	bool Contiene(const Diccionario* diccionario, std::string clave);

	int CantidadElementos(const Diccionario* diccionario);
	
	void DestruirDiccionario(Diccionario* diccionario);
}

#endif