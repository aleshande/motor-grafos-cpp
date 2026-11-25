#ifndef PARSER_CONEXIONES_H_
#define PARSER_CONEXIONES_H_
#include "ConjuntoConexiones.h"

using UndavConjuntoConexion::ConjuntoConexiones;

namespace UndavParserConexiones {

	// Precondicion: @pathArchivo es una cadena de caracteres valido. Si existe el archivo, el archivo cumple 
	// con el formato valido descripto en la entrega 1
	// Postcondicion: Si @pathArchivo es un path valido devuelve el conjunto de conexiones. Si no existe el archivo devuelve 
	// NULL
	ConjuntoConexiones* ParsearArchivoConexiones(const char* pathArchivo);
}

#endif