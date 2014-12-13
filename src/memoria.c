
#include <stdio.h>
#include <stdlib.h>

#include "memoria.h"
#include "registers.h"

/*
 * Reserva Espacio en memoria para la memoria de nuestra maquina
 */
int inicializarMemoria()
{
	MEMORIA = (unsigned char*) malloc(MEMORIA_TAMANO);
	MEM_INICIO = &MEMORIA[0];
	MEM_FIN = MEM_INICIO + MEMORIA_TAMANO;
	//Salir con Exito
	return 0;
}

/*
 * Da los valores que viene por defecto en los registros en caso de que el ejectuable no define sus propios
 */
int inicializarRegistros()
{
	//Punteros y Segmentos:
	PA = 0;  //Puntero Auxiliar empieza en 0
	IS = 0;  //Inicio de Memoria
	IP = IS; //Inicio del Segmento de Instruccion
	DS = MEMORIA_TAMANO / 4; //16 KB para Instrucciones
	DP = DS; //Inicio del Segmento de Datos
	PS = MEMORIA_TAMANO / 2; //16 KB para Datos
	PP = MEMORIA_TAMANO - 1; //32 KB para la Pila
		 //Fin del Segmento de Pila
	//printf("PP == %d, PS == %d\n", PP, PS);
	D1 = 0;  
	D2 = 0;  //Registros de Datos empiezan en 0
	D3 = 0;
	D4 = 0;
	//Registros de Estado:
	MO = 0x1248;
	ES = 0;
	//Salir con Exito
	return 0;
}

