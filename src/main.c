
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "registers.h"
#include "memoria.h"
#include "vm.h"
#include "isa.h"
#include "cargar.h"

int main(int argc, char* argv[])
{
	//ARG Prueba
	if ( argc == 1 ) {
		printf("Falta argumento que es el archivo que toca ejecutar.\nEjemplo: ./dlcj16 [opciones] nombre_del_archivo\n");
		return -1;
	}
	status = inicializarMemoria(); //inicializamos la memoria
	if (status < 0) { //comparamos los estados
		printf("Error %d: Error en allocacion de memoria.\n", status);//Error si se aloco la memoria
		return status;//retorna el estado
	} else {
		printf("Memoria Incializado con exito...\n");//Inicializa la memoria con exito
	}
	//Inicializamos los registros con el metodo correspondiente
	status = inicializarRegistros();
	if (status < 0) {//comparamos el estado
		printf("Error %d: Error en allocacion de registros.\n", status); //Error si se aloco la memoria
		return status;//retorna el estado
	} else {
		printf("Registros Incializados con exito...\n");//Caso contrario Iniciaaliza con exito
	}
	//Cargar Programa
	status = cargarInstrucciones(argv[argc - 1]);
	//status = cargarDemo(); // Carga el demo y lo asigan a estado
	if (status < 0) { // hacer la comparacion si ha cargado el demo de una manera correcta
		printf("Error %d: Error en cargar el programa.\n", status); //NO carga con exito
		return status;
	} else {
		printf("Programa cargado con exito...\n");//Carga con exito el demo
	}
	//Ejecutar Programa
	printf("Entrando al Proceso...\n");
	printf("----------------------------------------\n");
	while (status == 0) { //Mientras que tengamos exito en ejecutar las instrucciones
		//printf("MO: 0x%04x\n", MO);
		imprimerPila();
		status = ejecutarInstruccion(); //ejecutamos las instrucciones y asiganmos a estado
		if (status > 0) { // comparamos si es mayor a 0
			printf("Cerrando la Maquina Virtual.\n"); //ira cerrando la maquina virtual
			return 0;
		}
		//if (status == 0x7FFFFFFF) break;
		if (status < 0) { //si esl estado es menor a 0
			printf("Error %d: Error en ejecutar instruccion en posicion %d\n", status, (IP - 2)); //Ejecutara un error
			return status;//retorna el estado
		}
	}
	//Salir con Exito
	return 0;
}
