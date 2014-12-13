
#ifndef _MEMORIA_H_
#define _MEMORIA_H_

#define MEMORIA_TAMANO 65536 //(2^16) //Nuestro Processador de 16-bits
// = solo puede direccionar directamente 2^16 bytes de memoria
// o 65,536 bytes (64 Kilobytes).

////////////////Definir VM/////////////////
unsigned char* MEM_INICIO;
unsigned char* MEM_FIN;
///////////////////////////////////////////

////////////////Define Memory////////////////
unsigned char* MEMORIA;
/////////////////////////////////////////////

////////////////Define Functions////////////////
int inicializarMemoria();
int inicializarRegistros();
////////////////////////////////////////////////

#endif
