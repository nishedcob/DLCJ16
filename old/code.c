#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Definiciones de Constantes
#define MEMORIA_TAMANO 65536 //(2^16) //Nuestro Processador de 16-bits
// = solo puede direccionar directamente 2^16 bytes de memoria
// o 65,536 bytes (64 Kilobytes).


////////////////Define VM/////////////////
unsigned char* MEM_INICIO;
unsigned char* MEM_FIN;
signed int status;
//////////////////////////////////////////

////////////////Define Memory////////////////
unsigned char* mem;
/////////////////////////////////////////////

////////////////Define Registers////////////////

////Define Data Registers////
unsigned short D1, D2, RS;
/////////////////////////////

////Define Pointer Registers////
unsigned short IP, PP;
////////////////////////////////

////Define Segment Pointers////
unsigned short IS, PS;
///////////////////////////////

////Define Flags Register////
unsigned short ES;
/////////////////////////////

////////////////////////////////////////////////

////////////////Define Functions////////////////
int inicializarMemoria();
int inicializarRegistros();
int cargarInstrucciones(int argc, char* argv[]);
int cargarDemo();
int ejecutarInstruccion();
int imprimerPila();
////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	//Arg check
	if (argc == 1) {
		printf("Suponiendo que el programa ha sido pasado atraves de stdin (un pipe)...\n");
	} else if (argc == 2) {
		printf("Suponiendo que el argumento pasado es el nombre del archivo para leer como programa...\n");
	} else {
		printf("Como argumento, se debe pasar el nombre de archivo de programa o el programa mismo atravez de un pipe.\n");
		return 1;
	}
	//Inicialize Memory
	status = inicializarMemoria();
	if (status < 0) {
		printf("Error %d: Error en allocacion de memoria.\n", status);
		return status;
	} else {
		printf("Memoria Incializado con exito...\n");
	}
	//Inicialize Registers
	inicializarRegistros();
	if (status < 0) {
		printf("Error %d: Error en allocacion de registros.\n", status);
		return status;
	} else {
		printf("Registros Incializados con exito...\n");
	}
	//Cargar Programa
	/////////////////////////////////////ERROR AQUI://////////////////////////////////////////////////////////
	//status = cargarInstrucciones(argc, argv); // con un archivo, llega a un 
						    // segmentation fault en IP = 4096
						    // con stdin se entra a un bucle infinito
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	status = cargarDemo();
	if (status < 0) {
		printf("Error %d: Error en cargar el programa.\n", status);
		return status;
	} else {
		printf("Programa cargado con exito...\n");
	}
	//Ejecutar Programa
	printf("Entrando al Processo...\n");
	printf("----------------------------------------\n");
	while (status == 0) { //(status != 0x7FFFFFFF) {
		status = ejecutarInstruccion();
		if (status > 0) {
			printf("Cerrando la Maquina Virtual.\n");
			return 0;
		}
		//if (status == 0x7FFFFFFF) break;
		if (status < 0) {
			///////////////////////////////////ERROR AQUI:///////////////////////////////////////////////////
			printf("Error %d: Error en ejecutar instruccion en posicion %d\n", status, IP); // al salir de
				   // ejecutarInstruccion() bota error -25  (Error de SUMP) aunque no esta en una suma
			/////////////////////////////////////////////////////////////////////////////////////////////////
			return status;
		}
	}
	//Salir con Exito
	return 0;
}

/*
 * Codigos de Error reservados:
 * -1 = 
 * -2 = 
 * -3 = 
 * -4 =  
 */
int inicializarMemoria()
{
	mem = (unsigned char*) malloc(MEMORIA_TAMANO);
	MEM_INICIO = &mem[0];
	MEM_FIN = MEM_INICIO + MEMORIA_TAMANO;
	//Salir con Exito
	return 0;
}

/*
 * Codigos de Error reservados:
 * -5  = 
 * -6  = 
 * -7  = 
 * -8  =  
 * -9  = 
 * -10 = 
 * -11 = 
 * -12 = 
 * -13 = 
 * -14 = 
 */
int inicializarRegistros()
{
	IS = 0;  //Inicio de Memoria
	IP = IS; //Inicio del Segmento de Instruccion
	PS = MEMORIA_TAMANO / 2; //32 KB para Instrucciones
	PP = MEMORIA_TAMANO - 1; //32 KB para la Pila
		 //Fin del Segmento de Pila
	//printf("PP == %d, PS == %d\n", PP, PS);
	D1 = 0;  
	D2 = 0;  //Registros de Datos empiezan en 0
	RS = 0;
	//Salir con Exito
	return 0;
}

/*
 * Codigos de Error reservados:
 * -15 = Numero de Argumentos Disconocido
 * -16 = No se pudo abrir el programa
 * -17 = 
 * -18 =  
 * -19 =  
 */
int cargarInstrucciones(int argc, char* argv[])
{
	FILE* ptr_instrucciones;
	if (argc == 1) {
		//reading from Pipe IN
		ptr_instrucciones = freopen(NULL, "rb", stdin);
	} else if (argc == 2) {
		//reading from File
		ptr_instrucciones = fopen(argv[0],"rb");
	} else {
		printf("Error -15: Numero de Argumentos Disconocido\n");
		return -15;
	}
	if (!ptr_instrucciones) {	
		printf("Error -16: No se pudo abrir el binario del programa\n");
		return -16;
	}
	unsigned short val = 0;
	while (val != 0x0FFF) {
		char al = fgetc(ptr_instrucciones);
		printf("al = %d\n", al);
		mem[IP] = al;
		printf("mem[IP] = al\n");
		IP++;
		printf("IP = %d\n", IP);
		char bj = fgetc(ptr_instrucciones);
		printf("bj = %d\n", bj);
		mem[IP] = bj;
		printf("mem[IP] = bj\n");
		IP++;
		printf("IP = %d\n", IP);
		val = al << 8;
		val += bj;
		printf("val = %d\n", val);
	}
	//Volver puntero de instruccion a su puesto original:
	IP = IS;
	//Salir con Exito
	return 0;
}

/*
 * Calcule el serie de fibonacci (primeros 5 numeros)
 * Solo para probar que la maquina funciona
 */
int cargarDemo()
{
	mem[0] = 0x00;
	mem[1] = 0x01;
	mem[2] = 0x10;
	mem[3] = 0x01;
	mem[4] = 0x10;
	mem[5] = 0x01;
	mem[6] = 0x30;
	mem[7] = 0x04;
	mem[8] = 0x0F;
	mem[9] = 0xFF;
	//Salir con Exito
	return 0;
}

/*
 * Codigos de Error reservados:
 * -20 = Error MODA
 * -21 = Error MODP
 * -22 = Error SALR
 * -23 = Error EMPU 
 * -24 = Error SCRP
 * -25 = Error SUMP
 * -26 = Error RESP
 * -27 = Error SUMP
 * -28 = Error MULP
 * -29 = Error DIVP
 * -35 = Error PSHL
 */
int ejecutarInstruccion()
{
	char al = mem[IP];
	IP++;
	char bj = mem[IP];
	IP++;
	short val = al * 256;
	val += bj;
	printf("Instruction [%5d][%5d]: 0x%04X -> ", (IP-2), (IP-1), val);
	if (val == 0x0000) {
		return -999; //IP is in uninicialized Memory, terminate execution via error
	} else if (val == 0x0001) {
		//MODA
		ES |= 0x4000;
		printf("MODA\nProcessador esta en modo de ahorro.\n");
		imprimerPila();
		return ((ES & 0x4000) >> 14) == 1 ? 0 : -21;
	} else if (val == 0x0002) {
		//MODP
		ES &= 0xBFFF;
		printf("MODP\nProcessador esta en modo de pila.\n");
		imprimerPila();
		return ((ES & 0x4000) >> 14) == 0 ? 0 : -22;
	} else if (val == 0x0FFF || val == 0x0EFF) {
		//SALR
		printf("SALR\nSalir\n");
		imprimerPila();
		return 45; //0x0FFF; //0x7FFFFFFF;
	}
	char op = al >> 4;
	val &= 0x0FFF;
	switch(op) {
		case 0x01:
			//EMPU
			printf("EMPU %d\nEmpujar %d a la Pila.\n", val, val);
			mem[PP] = val % 256;
			PP--;
			mem[PP] = val / 256;
			PP--;
			imprimerPila();
			return PP > PS ? 0 : -23;
		case 0x02:
			//SCRP
			printf("SCRP %d\nSacar %d valores de la Pila.\n", val, (val+1));
			do {
				PP++;
				short tmp = mem[PP] * 256;
				mem[PP] = 0;
				PP++;
				tmp += mem[PP];
				mem[PP] = 0;
				printf("Sacar %d de la Pila\n", tmp);
				val--;
				imprimerPila();
			} while (val >= 0);
			return PP < (MEMORIA_TAMANO - 1) ? 0 : -24;
			break;
		case 0x03:
			//SUMP
			printf("SUMP %d\nSumar %d veces usando la Pila.\n", val, (val+1));
			do {
				PP++;
				D2 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D2 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				if (((ES & 0x4000) >> 14) == 1) {
					PP -= 4;
				}
				RS = D1 + D2;
				printf("Sumar %d y %d\n", D1, D2);
				mem[PP] = RS % 256;
				PP--;
				mem[PP] = RS / 256;
				PP--;
				val--;
				imprimerPila();
			} while (val >= 0);
			//printf("PP == %d, PS == %d\n", PP, PS);
			return (PP > PS && PP < (MEMORIA_TAMANO - 1)) ? 0 : -25;
		case 0x04:
			//RESP
			printf("RESP %d\nRestar %d veces usando la Pila.\n", val, (val+1));
			do {
				PP++;
				D2 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D2 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				if (((ES & 0x4000) >> 14) == 1) {
					PP -= 4;
				}
				RS = D1 - D2;
				printf("Restar %d de %d\n", D2, D1);
				mem[PP] = RS % 256;
				PP--;
				mem[PP] = RS / 256;
				PP--;
				val--;
				imprimerPila();
			} while (val >= 0);
			return (PP > PS && PP < (MEMORIA_TAMANO - 1)) ? 0 : -26;
		case 0x05:
			//MULP
			printf("MULP %d\nMultiplicar %d veces usando la Pila.\n", val, (val+1));	
			do {
				PP++;
				D2 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D2 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				if (((ES & 0x4000) >> 14) == 1) {
					PP -= 4;
				}
				RS = D1 * D2;
				printf("Multiplicar %d y %d\n", D1, D2);
				mem[PP] = RS % 256;
				PP--;
				mem[PP] = RS / 256;
				PP--;
				val--;
				imprimerPila();	
			} while (val >= 0);
			return (PP > PS && PP < (MEMORIA_TAMANO - 1)) ? 0 : -27;
		case 0x06:
			//DIVP
			printf("DIVP %d\nDividir %d veces usando la Pila.\n", val, (val+1));
			do {
				PP++;
				D2 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D2 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 = mem[PP] * 256;
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				PP++;
				D1 += mem[PP];
				mem[PP] = ((ES & 0x4000) >> 14) == 1 ? mem[PP] : 0;
				if (((ES & 0x4000) >> 7) == 1) {
					PP -= 4;
				}
				RS = D1 / D2;
				printf("Dividir %d por %d\n", D1, D2);
				mem[PP] = RS % 256;
				PP--;
				mem[PP] = RS / 256;
				PP--;
				val--;
				imprimerPila();
			} while (val >= 0);
			return (PP > PS && PP < (MEMORIA_TAMANO - 1)) ? 0 : -26;
		case 0x0C:
			//PUSHL
			printf("PUSHL %d\nEmpujar %d valores de 16-bits a la Pila.\n", val, (val+1));
			do {
				D1 = mem[IP] * 256;
				IP++;
				D1 += mem[IP];
				IP++;
				printf("Empujar %d a la Pila\n", D1);
				mem[PP] = D1 % 256;
				PP--;
				mem[PP] = D1 / 256;
				PP--;
				val--;
				imprimerPila();
			} while (val >= 0);	
			return PP > PS ? 0 : -35;
	}
	//Salir con Exito
	return 0;
}

int imprimerPila()
{
	//printf("MEMORIA_TAMANO = %d\n", MEMORIA_TAMANO);
	printf("---La Pila:---\n");
	D2 = PP;
	while (PP < (MEMORIA_TAMANO - 1)) {
		PP++;
		D1 = mem[PP] * 256;
		PP++;
		D1 += mem[PP];
		printf("    %5d\n", D1);
		//printf("%5d -> %5d -> %5d\n", (PP - 1), D1, PP);
	}
	printf("--------------\n");
	PP = D2;
	return 0;
}
