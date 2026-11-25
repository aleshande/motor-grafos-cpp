#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype> 
using namespace std;

#define TOPECAMPO 32
#define TOPEARCHIVO 500

namespace UndavArchivoTexto {
	
	void eliminarEspaciosCampo(char* campo); 
    bool esCampoValido(const char* campo);
    void copiarCampoValido(const char* campo, char* destino, int &inEscritura);
    char* eliminarCaracteresInvalidos(char* contenido);
    char* ObtenerContenidoLimpio(const char* pathArchivo);
	
	//precondicion: campo apunta a una cadena de caracteres válida.
	//postcondicion: elimina los espacios, sangrias, o el caracter \r que se crea en windows al final de los .txt, del arreglo de chars.
	void eliminarEspaciosCampo(char* campo){
	    int inEscritura=0, inLectura=0;
	    while (campo[inLectura]!='\0') {
	        if (campo[inLectura]!=' ' && campo[inLectura]!='\t' && campo[inLectura]!='\r'){
				campo[inEscritura++]=campo[inLectura];
			}
	        inLectura++;
	    }
	    campo[inEscritura]='\0';
	}
	
	//precondicion: campo apunta a una cadena de caracteres válida.
	//postcondicion: devuelve true si la cadena cumple el formato <entero>-<entero>. de lo contrario devuelve false.
	bool esCampoValido(char const* campo){
	    int in=0;
	    //Debe empezar con un entero
	    if (!isdigit(campo[in])) return false;
	    while (isdigit(campo[in])) in++;
	    // Luego un guion
	    if (campo[in]!='-') return false;
	    in++;
	    //y despues otro entero
	    if (!isdigit(campo[in])) return false;
	    while (isdigit(campo[in])) in++;
	    //despues del segundo entero, terminaria con el barra cero
	    return (campo[in]=='\0');
	}
	
	//precondicion: campo apunta a una cadena válida terminada en '\0', contenido apunta a otra cadena con suficiente espacio, e inEscritura
	//indica la posicion de destino en la cual se quiere empezar a generar la copia.
	//postcondicion:copia todos los caracteres de campo a contenido empezando a hacer la copia en contenido[inEscritura++], al terminar agrega un \n,
	// para cortar con el campo copiado.
	void copiarCampo(char const* campo, char* destino, int &inEscritura){
	    int inLectura=0;
	    while (campo[inLectura] != '\0') {
	        destino[inEscritura++]=campo[inLectura++];
	    }
	    destino[inEscritura++]= '\n';
	}
	
	//precondicion: contenido apunta a un arreglo de caracteres valido.
	//postcondicion: el arreglo de caracteres al que contenido apunta, ahora contiene campos con caracteres válidos, separados por \n, o \0 al final.
	char* ProcesarContenido(char* contenido){
	    int inLectura=0;
	    int inEscritura=0;
	    while (contenido[inLectura] != '\0') {
	        while (contenido[inLectura]==' ' || contenido[inLectura]=='\r' || contenido[inLectura]=='\t'){
				inLectura++;
			}
	        if (contenido[inLectura]=='\0') break;
	
	        char campo[TOPECAMPO];
	        int inCampo=0;
	        while (contenido[inLectura]!='\n' && contenido[inLectura]!='\0' && inCampo<99){
	            campo[inCampo++]=contenido[inLectura++];
	        }
	        if (contenido[inLectura]=='\n') inLectura++;
	        campo[inCampo]='\0';
	        eliminarEspaciosCampo(campo);
	        if (esCampoValido(campo)){
	            copiarCampo(campo,contenido,inEscritura);
	        }
	    }
	
	    //reemplaza el ultimo \n por un \0
	    if (inEscritura>0 && contenido[inEscritura-1]=='\n'){
	    	inEscritura--;
		}
	    contenido[inEscritura] = '\0';
	    return contenido;
	}
	
	//precondicion: pathArchivo apunta a una cadena valida con la ruta de un archivo .txt.
	//postcondicion: Si el archivo existe y se puede leer, devuelve un puntero a una nueva cadena dinámica (contenido) sin espacios, ni caracteres invalidos,
	//esta cadena estara formada por campos constituidos por un entero un guion y otro entero, y terminados con un \n.
	char* ObtenerContenidoLimpio(const char* pathArchivo){
	    ifstream archivo(pathArchivo, ios::binary | ios::ate);
	    if (!archivo.is_open()) {
	        cout << "Error al abrir el archivo" << endl;
	        return 	NULL;
	    }
	
	    streamsize tamano=archivo.tellg();
	    if (tamano>TOPEARCHIVO) {
	        cout<<"Archivo demasiado grande"<<endl;
	        return NULL;
	    }
	
	    archivo.seekg(0, ios::beg);
	    char* contenido=new char[tamano+2]; 
	    archivo.read(contenido, tamano);
	    int bytesLeidos=archivo.gcount();
	    contenido[bytesLeidos]='\0';
	
	    ProcesarContenido(contenido); 
	
	    return contenido;
	}
}
