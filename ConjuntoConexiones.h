#ifndef CONJUNTO_CONEXIONES_H_
#define CONJUNTO_CONEXIONES_H_

#include "Conexion.h"

using UndavConexion::Conexion;

namespace UndavConjuntoConexion {
	struct ConjuntoConexiones;

	// Precondicion: Ninguna
	// Postcondicion: Crea un conjunto vacio donde los items son de tipo Conexion.
	// El conjunto es equivalente a un conjunto de pares no ordenados.
	ConjuntoConexiones* CrearConjuntoVacio();

	// Precondicion: @conjunto e @items son instancias validas
	// Postcondicion: Si @item no existe dentro de @conjunto lo agrega. 
	// Este es un conjunto de pares no ordenados entonces dos items son iguales si:
	// - Son la misma instancia (esto siempre es asi)
	// - Si los valores p y q de @item son iguales (in importar el orden, conmutativamente tambien son iguales)
	void AgregarConexion(ConjuntoConexiones* conjunto, Conexion* item);

	// Precondicion: @conjunto es una instancia valida
	// Postcondicion: Quita una conexion del conjunto (no importa en que posicion esta). Si el conjunto esta vacio devuelve NULL
	Conexion* QuitarConexion(ConjuntoConexiones* conjunto);

	namespace Iterador {
		struct IteradorConjunto;
		
		//Precondicion: @conjunto es una instancia valida
		//Psotcondicion: Crear una instancia de IteradorConjunto que esta apuntando al primer elemento de @conjunto
		IteradorConjunto* Comienzo(ConjuntoConexiones* conjunto);

		//Precondicion: @iterador es una instancia valida
		//Postcondicion: Devuelve el item que se encuentra en el nodo que apunta @iterador. Si iterador apunta al final de la coleccion devuelve NULL
		Conexion* ObtenerItem(IteradorConjunto* iterador);

		//Precondicion: @iterador es una instancia valida
		//Postcondicion: Avanza @iterador al siguiente nodo. Si no hay siguiente nodo no realiza ninguna accion
		void Siguiente(IteradorConjunto* iterador);

		//Precondicion: @iterador es una instancia valida
		//Postcondicion: Devuelve true si @iterador esta apuntando al final de la coleccion (no hay item). Caso contrario devuelve false
		bool EsFin(IteradorConjunto* iterador);

		//Precondicion: @iterador es una instancia valida
		//Postcondicion: Libera todos los recursos asociados de @iterador
		void DestruirIterador(IteradorConjunto* iterador);
	}

	// Precondicion: Ninguna
	// Postcondicion: Libera todos los recursos asociados de conjunto
	void DestruirConjunto(ConjuntoConexiones* conjunto);
}

#endif

