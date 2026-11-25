#ifndef CONEXION_H_
#define CONEXION_H_

namespace UndavConexion {
	struct Conexion {
		int p;
		int q;
	};

	// Precondicion: Ninguna
	// Postcondicion: Devuelve una instancia valida de Conexion que contiene a @p y a @q
	Conexion* CrearConexion(int p, int q);

	// Precondicion: @conexionPQ es una cadena de caracteres
	// Postcondicion: Si @conexionPQ tiene un formato valido devuelve una intancia valida de Conexion. Caso contrario devuelve NULL.
	// El formato valido esta dado "p-q" donde p y q son enteros separados por el caracter '-' 
	Conexion* CrearConexion(char* conexionPQ);

	// Precondicion: @conexion es una instancia valida
	// Postcondicion: Devuelve el valor de p de @conexion
	int ObtenerP(const Conexion* conexion);

	// Precondicion: @conexion es una instancia valida
	// Postcondicion: Devuelve el valor de q de @conexion
	int ObtenerQ(const Conexion* conexion);

	// Precondicion: @conexion es una instancia valida
	// Postcondicion: Libera todos los recursos asociados de @conexion
	void DestruirConexion(Conexion* conexion);
}

#endif
