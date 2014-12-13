
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "memoria.h"
#include "isa.h"
#include "registers.h"

/*
 * Devuelve el numero de byte que ha leido para ejecutar la instruccion
 */
int ejecutarInstruccion()
{
	unsigned char al = MEMORIA[IP];
	IP++;
	unsigned char bj = MEMORIA[IP];
	IP++;
	short val = (al << 8) + bj;
	printf("Instruction [%5d][%5d]: 0x%04X -> ", (IP-2), (IP-1), val);
	if (val == 0x0000) {
		goto memoria_no_inicializada;
	} else if (al < 0x10) {
		//instruccions sin operandos:
		switch (al) {
			case 0x00:
				//Modos del processador:
				switch (bj) {
					case 0x01:
						//MODA:
						op_func = MODA;
						break;
					case 0x02:
						//MODP:
						op_func = MODP;
						break;
					case 0x03:
						//MODI:
						op_func = MODI;
						break;
					case 0x04:
						//MODV:
						op_func = MODV;
						break;
					case 0x05:
						//MODC:
						op_func = MODC;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			case 0x01:
				//Modos de Direccionamiento para Fuente 1:
				switch (bj) {
					case 0x01:
						//F1DD:
						op_func = F1DD;
						break;
					case 0x02:
						//F1SA:
						op_func = F1SA;
						break;
					case 0x03:
						//F1DA:
						op_func = F1DA;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			case 0x02:
				//Modos de Direccionamiento para Fuente 2:
				switch(bj){
					case 0x01:
						//F2DD;
						op_func = F2DD;
						break;
					case 0x02:
						//F2SA;
						op_func = F2SA;
						break;
					case 0x03:
						//F2DA;
						op_func = F2DA;
						break;
					default:
						goto instruccion_no_conocido;		
				}
				break;
			case 0x03:
				//Modos de Direccionamiento para Destino:
				switch(bj){
					case 0x01:
						//DEDD;
						op_func = DEDD;
						break;
					case 0x02:
						//DESA;
						op_func = DESA;
						break;
					case 0x03:
						//DEDA;
						op_func = DEDA;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			case 0x04:
				//Poner Banderas en 1:
				switch(bj){
					case 0x01:
						//SOVE
						op_func = SOVE;
						break;
					case 0x02:
						//SDIR
						op_func = SDIR;
						break;
					case 0x03:
						//SINT;
						op_func = SINT;
						break;
					case 0x04:
						//STRP;
						op_func = STRP;
						break;
					case 0x05:
						//SSIG
						op_func = SSIG;
						break;
					case 0x06:
						//SCER
						op_func = SCER;
						break;
					case 0x07:
						//SACR;
						op_func = SACR;
						break;
					case 0x08:
						//SACX;
						op_func = SACX;
						break;
					case 0x09:
						//SPAR;
						op_func = SPAR;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			case 0x05:
				//Poner Banderas en 0:
				switch(bj){
					case 0x01:
						//ROVE
						op_func = ROVE;
						break;
					case 0x02:
						//RDIR;
						op_func = RDIR;
						break;
					case 0x03:
						//RINT;
						op_func = RINT;
						break;
					case 0x04:
						//RTRP;
						op_func = RTRP;
						break;
					case 0x05:
						//RSIG;
						op_func = RSIG;
						break;
					case 0x06:
						//RCER;
						op_func = RCER;
						break;
					case 0x07:
						//RACR;
						op_func = RACR;
						break;
					case 0x08:
						//RACX;
						op_func = RACX;
						break;
					case 0x09:
						//RPAR;
						op_func = RPAR;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			case 0x0E:
			case 0x0F:
				//Codigos de Salida:
				switch(bj){
					case 0xFF:
						//SALR;
						op_func = SALR;
						break;
					default:
						goto instruccion_no_conocido;
				}
				break;
			default:
				//instruccions no conociodos:
				goto instruccion_no_conocido;
		}
	} else {
		char op = al >> 4;
		val &= 0x0FFF;
		switch (op) {
			case 0x01:
				//EMPU:
				op_func = EMPU;
				break;
			case 0x02:
				//SCRP:
				op_func = SCRP;
				break;
			case 0x03:
				//SUMP:
				op_func = SUMP;
				break;
			case 0x04:
				//RESP:
				op_func = RESP;
				break;
			case 0x05:
				//MULP:
				op_func = MULP;
				break;
			case 0x06:
				//DIVP:
				op_func = DIVP;
				break;
			case 0x07:
				//MDUP:
				op_func = MDUP;
				break;
			case 0x0C:
				//PSHL:
				op_func = PSHL;
				break;
			default:
				goto instruccion_no_conocido;
		}
	}
	return op_func(val);
	memoria_no_inicializada:
	printf("Memoria no inicializada!\n");//IP esta en memoria no inicializado y debemos terminar la ejecutacion
	return -999;
	instruccion_no_conocido:
	printf("Instruccion Disconocida!\n");//No se reconoce el instruccion a que apunta IP
	return -1;
}

int MODA(int operands)
{
	MO |= (1 << (15 - M_MPNA)); //Modo de Ahorro
	printf("MODA\n Modo Ahorro\n");
	return 0;
}

int MODP(int operands)
{
	MO &= ~(1 << (15 - M_MPNA)); //Modo de Pila
	printf("MODP\n Modo Pila\n");
	return 0;
}

/*
bool modi = false;
bool modv = true;
bool modc = false;
*/

int MODI(int operands)
{
	MO |= (1 << (15 - M_MOPI)); //Activar Modo de Immediato
	MO &= ~(1 << (15 - M_MOPV)); //Desactivar Modo Variable
	MO &= ~(1 << (15 - M_MOPC)); //Desactivar Modo de Conteo
	printf("MODI\nActiva modo immediato\n");
	/*
	modi = true;
	modv = false;
	modc = false;
	*/
	return 0;
}

int MODV(int operands)
{
	MO &= ~(1 << (15 - M_MOPI)); //Desactivar Modo de Immediato
	MO |= (1 << (15 - M_MOPV)); //Activar Modo Variable
	MO &= ~(1 << (15 - M_MOPC)); //Desactivar Modo de Conteo 
	printf("MODV\nActiva modo variable\n");
	/*
	modi = false;
	modv = true;
	modc = false;
	*/
	return 0;
}

int MODC(int operands)//
{
	MO &= ~(1 << (15 - M_MOPI)); //Desactivar Modo de Immediato
	MO &= ~(1 << (15 - M_MOPV)); //Desactivar Modo Variable
	MO |= (1 << (15 - M_MOPC)); //Activar Modo de Conteo
	printf("MODC\nActiva modo conteo\n");
	/*
	modi = false;
	modv = false;
	modc = true;
	*/
	return 0;
}

int F1DD(int operands)//
{
	MO |= (1 << (15 - M_S1DD)); //Activar Modo Dato Directo para Fuente 1
	MO &= ~(1 << (15 - M_S1SA)); //Desactivar Modo Direccion Unica para Fuente 1
	MO &= ~(1 << (15 - M_S1DA)); //Desactivar Modo Direccion Doble para Fuente 1
	printf("F1DD\nActiva direccionamiento directo de fuente 1\n");
	return 0;
}

int F1SA(int operands)
{
	MO &= ~(1 << (15 - M_S1DD)); //Desactivar Modo Dato Directo para Fuente 1
	MO |= (1 << (15 - M_S1SA)); //Activar Modo Direccion Unica para Fuente 1
	MO &= ~(1 << (15 - M_S1DA)); //Desactivar Modo Direccion Doble para Fuente 1
	printf("F1SA\nActiva direccionamiento unica de fuente 1\n");
	return 0;
}

int F1DA(int operands)
{
	MO &= ~(1 << (15 - M_S1DD)); //Desactivar Modo Dato Directo para Fuente 1
	MO &= ~(1 << (15 - M_S1SA)); //Desactivar Modo Direccion Unica para Fuente 1
	MO |= (1 << (15 - M_S1DA)); //Activar Modo Direccion Doble para Fuente 1
	printf("F1DA\nActiva direccionamiento doble de fuente 1\n");
	return 0;
}

int F2DD(int operands)
{
	MO |= (1 << (15 - M_S2DD)); //Activar Modo Dato Directo para Fuente 2
	MO &= ~(1 << (15 - M_S2SA)); //Desactivar Modo Direccion Unica para Fuente 2
	MO &= ~(1 << (15 - M_S2DA)); //Desactivar Modo Direccion Doble para Fuente 2
	printf("F2DD\nActiva direccionamiento directo de fuente 2\n");
	return 0;
}

int F2SA(int operands)
{
	MO &= ~(1 << (15 - M_S2DD)); //Desactivar Modo Dato Directo para Fuente 2
	MO |= (1 << (15 - M_S2SA)); //Activar Modo Direccion Unica para Fuente 2
	MO &= ~(1 << (15 - M_S2DA)); //Desactivar Modo Direccion Doble para Fuente 2
	printf("F2SA\nActiva direccionamiento unica de fuente 2\n");
	return 0;
}

int F2DA(int operands)
{
	MO &= ~(1 << (15 - M_S2DD)); //Desactivar Modo Dato Directo para Fuente 2
	MO &= ~(1 << (15 - M_S2SA)); //Desactivar Modo Direccion Unica para Fuente 2
	MO |= (1 << (15 - M_S2DA)); //Activar Modo Direccion Doble para Fuente 2
	printf("F2DA\nActiva direccionamiento doble de fuente 2\n");
	return 0;
}

int DEDD(int operands)
{
	MO |= (1 << (15 - M_DEDD)); //Activar Modo Dato Directo para Destino
	MO &= ~(1 << (15 - M_DESA)); //Desactivar Modo Direccion Unica para Destino
	MO &= ~(1 << (15 - M_DEDA)); //Desactivar Modo Direccion Doble para Destino
	printf("DEDD\nActiva direccionamiento directo del destino\n");
	return 0;
}

int DESA(int operands)
{
	MO &= ~(1 << (15 - M_DEDD)); //Desactivar Modo Dato Directo para Destino
	MO |= (1 << (15 - M_DESA)); //Activar Modo Direccion Unica para Destino
	MO &= ~(1 << (15 - M_DEDA)); //Desactivar Modo Direccion Doble para Destino
	printf("DESA\nActiva direccionamiento unica del destino\n");
	return 0;
}

int DEDA(int operands)
{
	MO &= ~(1 << (15 - M_DEDD)); //Desactivar Modo Dato Directo para Destino
	MO &= ~(1 << (15 - M_DESA)); //Desactivar Modo Direccion Unica para Destino
	MO |= (1 << (15 - M_DEDA)); //Activar Modo Direccion Doble para Destino
	printf("DEDA\nActiva direccionamiento doble del destino\n");
	return 0;
}

int SOVE(int operands)
{
	ES |= (1 << (15 - F_OVER)); //Setear la bandera de Overflow
	printf("SOVE\nSetear Overflow\n");
	return 0;
}

int SDIR(int operands)
{
	ES |= (1 << (15 - F_DIRE)); //Setear la bandera de la direccion
	printf("SDIR\nSetear direccion\n");
	return 0;
}

int SINT(int operands)
{
	ES |= (1 << (15 - F_INTE)); //Setear la bandera de la interrupcion
	printf("SINT\nSetear interrupcion\n");
	return 0;
}

int STRP(int operands)
{
	ES |= (1 << (15 - F_TRAP)); //Setear la bandera de la Trap
	printf("STRP\nSetear Trap\n");
	return 0;
}

int SSIG(int operands)
{
	ES |= (1 << (15 - F_SIGN)); //Setear la bandera de Signo
	printf("SSIG\nSetear Signo\n");
	return 0;
}

int SCER(int operands)
{
	ES |= (1 << (15 - F_CERO)); //Setear la bandera de Cero
	printf("SCER\nSetear Cero\n");
	return 0;
}

int SACR(int operands)
{
	ES |= (1 << (15 - F_ACAR)); //Setear la bandera de Acarreo
	printf("SACR\nSetear Acarreo\n");
	return 0;
}

int SACX(int operands)
{
	ES |= (1 << (15 - F_ACAX)); //Setear la bandera de Acarreo Auxiliar
	printf("SACX\nSetear Acarreo Auxiliar\n");
	return 0;
}

int SPAR(int operands)
{
	ES |= (1 << (15 - F_PARI)); //Setear la bandera de Pariedad
	printf("SPAR\nSetear Pariedad\n");
	return 0;
}

int ROVE(int operands)
{
	ES &= ~(1 << (15 - F_OVER)); //Resetear la bandera de Overflow
	printf("ROVE\nResetear Overflow\n");
	return 0;
}

int RDIR(int operands)
{
	ES &= ~(1 << (15 - F_DIRE)); //Resetear la bandera de Direccion
	printf("RDIR\nResetear Direccion\n");
	return 0;
}

int RINT(int operands)
{
	ES &= ~(1 << (15 - F_INTE)); //Resetear la bandera de Interrupcion
	printf("RINT\nResetear interrupcion\n");
	return 0;
}

int RTRP(int operands)
{
	ES &= ~(1 << (15 - F_TRAP)); //Resetear la bandera de trap
	printf("RTRP\nResetear trap\n");
	return 0;
}

int RSIG(int operands)
{
	ES &= ~(1 << (15 - F_SIGN)); //Resetear la bandera de Signo
	printf("RSIG\nResetear signo\n");
	return 0;
}

int RCER(int operands)
{
	ES &= ~(1 << (15 - F_CERO)); //Resetear la bandera de Cero
	printf("RCER\nResetear Cero\n");
	return 0;
}

int RACR(int operands)
{
	ES &= ~(1 << (15 - F_ACAR)); //Resetear la bandera de Acarreo
	printf("RACR\nResetear Acarreo\n");
	return 0;
}

int RACX(int operands)
{
	ES &= ~(1 << (15 - F_ACAX)); //Resetear la bandera de Acarreo Auxiliar
	printf("RACX\nResetear acarreo auxiliar\n");
	return 0;
}

int RPAR(int operands)
{
	ES &= ~(1 << (15 - F_PARI)); //Resetear la bandera de Pariedad
	printf("RPAR\nResetear PAriedad\n");
	return 0;
}

int SALR(int operands)
{
	printf("SALR\nSalir\n");
	return 45;
}

int EMPU(int operands)
{	
	//SPEC Logic
	unsigned short old_pp = PP;
	//STD Logic
	int oper_mode = operand_mode();
	if (oper_mode != 3) printf("EMPU\nEmpujar a la pila (PUSH).\n");
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en EMPU: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			MEMORIA[PP] = (char)(operands & 0x00FF);
			PP--;
			MEMORIA[PP] = (char)((operands & 0x0F00) >> 8);
			PP--;
			return (old_pp == PP - 2) ? 0 : -1;
		case 2: ;
			//Modo Variable
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			short operand_1 = obtenerOperando(op_codes[0], 1);
			short operand_2 = obtenerOperando(op_codes[1], 2);
			short operand_3 = obtenerOperando(op_codes[2], 3);
			MEMORIA[PP] = (char)(operand_1 & 0x00FF);
			PP--;
			MEMORIA[PP] = (char)((operand_1 & 0x0F00) >> 8);
			PP--;
			MEMORIA[PP] = (char)(operand_2 & 0x00FF);
			PP--;
			MEMORIA[PP] = (char)((operand_2 & 0x0F00) >> 8);
			PP--;
			MEMORIA[PP] = (char)(operand_3 & 0x00FF);
			PP--;
			MEMORIA[PP] = (char)((operand_3 & 0x0F00) >> 8);
			PP--;
			return (old_pp == PP - 6) ? 0 : -1;
		case 3:
			//Modo Conteo
			//Mover el puntero de pila sin cambiar valores de la pila
			PP--;
			PP--;
			//Solo queremos imprimir el nombre de la operacion una vez
			if(operands == 0) printf("EMPU\nEmpujar a la pila (PUSH).\n");
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (PP == (old_pp - 2)) ?
				((operands > 0) ? 
					EMPU(operands - 1) : 0) 
				: (-1);
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE EMPU: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int SCRP(int operands)
{
	//SPEC Logic
	unsigned short old_pp = PP;
	//STD Logic
	int oper_mode = operand_mode();
	if (oper_mode != 3) printf("SCRP\nSacar de la Pila (POP).\n");
	short status;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en EMPU: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//No nos importa los valores en la pila, solo debemos mover el puntero de pila
			PP++;
			PP++;
			return (old_pp == PP + 2) ? 0 : -1;
		case 2: ;
			//Modo Variable
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//SACAR 3 VALORES DE LA PILA Y ENVIALES A SUS DESTINOS
			//Sacar Primer Valor de la Pila
			short val1 = MEMORIA[PP];
			val1 = val1 << 8;
			PP++;
			val1 += MEMORIA[PP];
			PP++;
			//Enviar Primer Valor
			//status = enviarOperando(val1, op_codes[0], (char)(1));
			//if ( status < 0 ) return status;
			//Sacar Segundo Valor de la Pila
			short val2 = MEMORIA[PP];
			val2 = val2 << 8;
			PP++;
			val2 += MEMORIA[PP];
			PP++;
			//Enviar Segundo Valor
			status = enviarOperando(val2, op_codes[1], (char)(2));
			if ( status < 0 ) return status;
			//Sacar Tercer Valor
			short val3 = MEMORIA[PP];
			val3 = val3 << 8;
			PP++;
			val3 += MEMORIA[PP];
			PP++;
			//Enviar Tercer Valor
			status = enviarOperando(val3, op_codes[2], (char)(3));
			if (status < 0 ) return status;
			return (old_pp == PP + 6) ? 0 : -1;
		case 3:
			//Modo Conteo
			//Mover el puntero de pila sin cambiar valores de la pila
			PP++;
			PP++;
			//Imprimir solo una vez
			if (oper_mode == 0) printf("SCRP\nSacar de la Pila (POP).\n");
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (PP == (old_pp + 2)) ?
				((operands > 0) ? 
					SCRP(operands - 1) : 0) 
				: (-1);
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE SCRP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int SUMP(int operands)
{
	//STD Logic
	int oper_mode = operand_mode();
	if (oper_mode != 3) printf("SUMP\nSumar.\n");
	short operand_1, operand_2, resultado;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en SUMP: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//POP Pila, SUMAR y Guardar a la Pila
			//POP PILA
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			//Hacer el Calculo
			resultado = operand_1 + ((short)operands);
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			return 0;
		case 2: ;
			//Modo Variable
			//Obtener los codigos de los operandos
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//Obtener Operandos
			operand_1 = obtenerOperando(op_codes[0], 1);
			operand_2 = obtenerOperando(op_codes[1], 2);
			//Realizar la calculacion
			resultado = operand_1 + operand_2;
			//Guardar el resultado en destino
			enviarOperando(resultado, op_codes[2], (char)(3));
			return 0;
		case 3:
			//Modo Conteo
			//SUMAR VALORES DE LA PILA
			//POP Pila, SUMAR y Guardar a la Pila
			//POP PILA
			//POP Primer Operando
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//POP Segundo Operando
			operand_2 = MEMORIA[PP];
			operand_2 = operand_2 << 8;
			PP++;
			operand_2 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 4;
			//Hacer el Calculo
			resultado = operand_1 + operand_2;
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			//Imprimir solo una vez
			if (operands == 0) printf("SUMP\nSumar.\n");
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (operands > 0) ? SUMP(operands - 1) : 0;
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE SUMP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int RESP(int operands)
{
	printf("RESP\nRestar.\n");
	//STD Logic
	int oper_mode = operand_mode();
	short operand_1, operand_2, resultado;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en RESP: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//POP Pila, RESTAR y Guardar a la Pila
			//POP PILA
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			//Hacer el Calculo
			resultado = operand_1 - ((short)operands);
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			return 0;
		case 2: ;
			//Modo Variable
			//Obtener los codigos de los operandos
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//Obtener Operandos
			operand_1 = obtenerOperando(op_codes[0], 1);
			operand_2 = obtenerOperando(op_codes[1], 2);
			//Realizar la calculacion
			resultado = operand_1 - operand_2;
			//Guardar el resultado en destino
			enviarOperando(resultado, op_codes[2], (char)(3));
			return 0;
		case 3:
			//Modo Conteo
			//RESTAR VALORES DE LA PILA
			//POP Pila, RESTAR y Guardar a la Pila
			//POP PILA
			//POP Primer Operando
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//POP Segundo Operando
			operand_2 = MEMORIA[PP];
			operand_2 = operand_2 << 8;
			PP++;
			operand_2 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 4;
			//Hacer el Calculo
			resultado = operand_1 - operand_2;
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (operands > 0) ? RESP(operands - 1) : 0;
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE RESP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int MULP(int operands)
{
	printf("MULP\nMultiplicar.\n");
	//STD Logic
	int oper_mode = operand_mode();
	short operand_1, operand_2, resultado;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en MULP: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//POP Pila, MULTIPLICAR y Guardar a la Pila
			//POP PILA
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			//Hacer el Calculo
			resultado = operand_1 * ((short)operands);
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			return 0;
		case 2: ;
			//Modo Variable
			//Obtener los codigos de los operandos
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//Obtener Operandos
			operand_1 = obtenerOperando(op_codes[0], 1);
			operand_2 = obtenerOperando(op_codes[1], 2);
			//Realizar la calculacion
			resultado = operand_1 * operand_2;
			//Guardar el resultado en destino
			//enviarOperando(resultado, op_codes[2], (char)(3));
			return 0;
		case 3:
			//Modo Conteo
			//MULTIPLICAR VALORES DE LA PILA
			//POP Pila, MULTIPLICAR y Guardar a la Pila
			//POP PILA
			//POP Primer Operando
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//POP Segundo Operando
			operand_2 = MEMORIA[PP];
			operand_2 = operand_2 << 8;
			PP++;
			operand_2 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 4;
			//Hacer el Calculo
			resultado = operand_1 * operand_2;
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (operands > 0) ? MULP(operands - 1) : 0;
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE MULP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int DIVP(int operands)
{
	printf("DIVP\nDividir.\n");
	//STD Logic
	int oper_mode = operand_mode();
	short operand_1, operand_2, resultado;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en DIVP: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//POP Pila, DIVIDIR y Guardar a la Pila
			//POP PILA
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			//Hacer el Calculo
			resultado = operand_1 / ((short)operands);
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			return 0;
		case 2: ;
			//Modo Variable
			//Obtener los codigos de los operandos
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//Obtener Operandos
			operand_1 = obtenerOperando(op_codes[0], 1);
			operand_2 = obtenerOperando(op_codes[1], 2);
			//Realizar la calculacion
			resultado = operand_1 / operand_2;
			//Guardar el resultado en destino
			enviarOperando(resultado, op_codes[2], (char)(3));
			return 0;
		case 3:
			//Modo Conteo
			//DIVIDIR VALORES DE LA PILA
			//POP Pila, DIVIDIR y Guardar a la Pila
			//POP PILA
			//POP Primer Operando
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//POP Segundo Operando
			operand_2 = MEMORIA[PP];
			operand_2 = operand_2 << 8;
			PP++;
			operand_2 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 4;
			//Hacer el Calculo
			resultado = operand_1 / operand_2;
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (operands > 0) ? DIVP(operands - 1) : 0;
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE DIVP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int MDUP(int operands)
{
	printf("MDUP\nCalcular Modulo.\n");
	//STD Logic
	int oper_mode = operand_mode();
	short operand_1, operand_2, resultado;
	switch(oper_mode){
		case -1:
			//ERROR
			printf("ERROR en MDUP: Registro de Modos tiene mas que un modo registrado para el modo de operandos.\n");
			return -1;
		case 1:
			//Modo Immediato
			//POP Pila, MODULO y Guardar a la Pila
			//POP PILA
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			//Hacer el Calculo
			resultado = operand_1 % ((short)operands);
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			return 0;
		case 2: ;
			//Modo Variable
			//Obtener los codigos de los operandos
			char* op_codes = malloc(sizeof(char) * 3);
			op_codes = obtenerCodigoOp(operands);
			//Obtener Operandos
			operand_1 = obtenerOperando(op_codes[0], 1);
			operand_2 = obtenerOperando(op_codes[1], 2);
			//Realizar la calculacion
			resultado = operand_1 % operand_2;
			//Guardar el resultado en destino
			enviarOperando(resultado, op_codes[2], (char)(3));
			return 0;
		case 3:
			//Modo Conteo
			//MODULO VALORES DE LA PILA
			//POP Pila, MODULO y Guardar a la Pila
			//POP PILA
			//POP Primer Operando
			operand_1 = MEMORIA[PP];
			operand_1 = operand_1 << 8;
			PP++;
			operand_1 += MEMORIA[PP];
			PP++;
			//POP Segundo Operando
			operand_2 = MEMORIA[PP];
			operand_2 = operand_2 << 8;
			PP++;
			operand_2 += MEMORIA[PP];
			PP++;
			//Conservar posision de pila en modo de ahorro
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 4;
			//Hacer el Calculo
			resultado = operand_1 % operand_2;
			//Guardar resultado a la Pila
			MEMORIA[PP] = (char)(resultado >> 8);
			PP--;
			MEMORIA[PP] = (char)(resultado & 0x00FF);
			PP--;
			//Devolver valor recursivamente para repetir hasta que el conteador es menor a 0:
			return (operands > 0) ? MDUP(operands - 1) : 0;
		default:
			//GRAVE ERROR
			printf("ERROR GRAVE MDUP: oper_mode = %d\n", oper_mode);
			return (oper_mode < 0) ? oper_mode : (-1 * oper_mode);
	}
	return -1;
}

int PSHL(int operands)
{
	short imm = MEMORIA[IP];
	imm = imm << 8;
	IP++;
	imm += MEMORIA[IP];
	IP++;
	MEMORIA[PP] = (char)(imm >> 8);
	PP--;
	MEMORIA[PP] = (char)(imm & 0x00FF);
	PP--;
	return (operands > 0) ? PSHL(operands - 1) : 0;
}

/*int operand_mode()
{
	if ( (((MO << M_MOPI) >> (15 - M_MOPI)) == 1 )// >> M_MOPI) == 1) 
		&& (((MO << M_MOPV) >> (15 - M_MOPV)) == 0)// >> M_MOPV) == 0) 
		&& (((MO << M_MOPC) >> (15 - M_MOPC)) == 0) ){//>> M_MOPC) == 0) )
			printf("Modo Immediato\n");
			return 1;
	}
	else if ( (((MO << M_MOPI) >> (15 - M_MOPI)) == 0)// >> M_MOPI) == 0) 
		&& (((MO << M_MOPV) >> (15 - M_MOPV)) == 1)// >> M_MOPV) == 1) 
		&& (((MO << M_MOPC) >> (15 - M_MOPC)) == 0) ){// >> M_MOPC) == 0) )
			printf("Modo Variable\n");
			return 2;
	}
	else if ( (((MO << M_MOPI) >> (15 - M_MOPI)) == 0) // >> M_MOPI) == 0) 
		&& (((MO << M_MOPV) >> (15 - M_MOPV)) == 0) // >> M_MOPV) == 0) 
		&& (((MO << M_MOPC) >> (15 - M_MOPC)) == 1) ){ // >> M_MOPC) == 1) )
			printf("Modo Conteo\n");
			return 3;
	}
	else return -1;
}*/

int operand_mode()
{
	/*
	printf("MOPI: 0x%04X\n", ((MO & (1 << M_MOPI)) && (~(MO & ((1 << M_MOPC) || (1 << M_MOPV))))));
	printf("MOPV: 0x%04X\n", ((MO & (1 << M_MOPV)) && (~(MO & ((1 << M_MOPI) || (1 << M_MOPC))))));
	printf("MOPC: 0x%04X\n", ((MO & (1 << M_MOPC)) && (~(MO & ((1 << M_MOPI) || (1 << M_MOPV))))));
	*/
	/*
	if ( (MO & (1 << M_MOPI)) && (~(MO & ((1 << M_MOPC) || (1 << M_MOPV)))) ) {
			printf("Modo Immediato\n");
			return 1;
	}
	else if ( (MO & (1 << M_MOPV)) && (~(MO & ((1 << M_MOPI) || (1 << M_MOPC)))) ) {
			printf("Modo Variable\n");
			return 2;
	}
	else if ( (MO & (1 << M_MOPC)) && (~(MO & ((1 << M_MOPI) || (1 << M_MOPV)))) ) {
			printf("Modo Conteo\n");
			return 3;
	}
	//*/
	/*
	if (modi == true && modv == false && modc == false) return 1;
	else if (modi == false && modv == true && modc == false) return 2;
	else if (modi == false && modv == false && modc == true) return 3;
	*/
	printf("MODOS: 0x%04X\n", MO);
	printf("MOPI: %d\n", ((MO >> M_MOPI) % 2));
	printf("MOPV: %d\n", ((MO >> M_MOPV) % 2));
	printf("MOPC: %d\n", ((MO >> M_MOPC) % 2));
	/*
	if (((MO >> M_MOPI) % 2 == 1) && ((MO >> M_MOPV) % 2 == 0) && ((MO >> M_MOPC) % 2 == 0)) return 1;
	else if (((MO >> M_MOPI) % 2 == 0) && ((MO >> M_MOPV) % 2 == 1) && ((MO >> M_MOPC) % 2 == 0)) return 2;
	else if (((MO >> M_MOPI) % 2 == 0) && ((MO >> M_MOPV) % 2 == 0) && ((MO >> M_MOPC) % 2 == 1)) return 3;
	*/
	if (((MO >> M_MOPI) % 2 == 1)) return 1;
	else if (((MO >> M_MOPV) % 2 == 1)) return 2;
	else if (((MO >> M_MOPC) % 2 == 1)) return 3;
	else return -1;
}

char* obtenerCodigoOp(int opers)
{
	char* op_code = malloc(sizeof(char) * 3);
	op_code[0] = opers >> 8;
	op_code[1] = (opers << 8) >> 12;
	op_code[2] = (char)(opers & 0x000F);
	return op_code;
}

short obtenerOperando(char op_code, char op_num)
{
	short val, val2;
	char* op_lec_mode = malloc(sizeof(char) * 3);
	op_lec_mode = obtenerModoLectura(op_num);
	switch(op_code){
		case 0x00:
			//PILA:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = MEMORIA[PP];
			val = val << 8;
			PP++;
			val += MEMORIA[PP];
			PP++;
			if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP -= 2;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x01:
			//DATA 1:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = D1;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x02:
			//DATA 2:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = D2;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x03:
			//DATA 3:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = D3;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x04:
			//DATA 4:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = D4;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x05:
			//Puntero de Instruccion
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = IP;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x06:
			//Puntero de Datos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = DP;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x07:
			//Puntero de Pila
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = PP;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x08:
			//Puntero Auxiliar
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = PA;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x09:
			//Segmento de Instrucciones
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = IS;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0A:
			//Segmento de Datos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = DS;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0B:
			//Segmento de Pila
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = PS;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0C:
			//Modos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = MO;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0D:
			//Estados
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = ES;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0E: ;
			//Memoria
			short dir = MEMORIA[IP];
			dir = dir << 8;
			IP++;
			dir += MEMORIA[IP];
			IP++;
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = MEMORIA[dir];
			dir++;
			val = val << 8;
			val += MEMORIA[dir];
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		case 0x0F: ;
			//Immediato
			short imm = MEMORIA[IP];
			imm = imm << 8;
			IP++;
			imm += MEMORIA[IP];
			IP++;
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			val = imm;
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) return val;
			val2 = MEMORIA[val];
			val2 = val2 << 8;
			val++;
			val2 += MEMORIA[val];
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) return val2;
			else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				val = MEMORIA[val2];
				val = val << 8;
				val2++;
				val += MEMORIA[val2];
				return val;
			}
			return -1;
		default:
			return -1;
	}
}

char* obtenerModoLectura(char op_num)
{
	char modo_lectura[3];
	modo_lectura[0] = ((op_num == 1) ? ((MO << (15 - M_S1DD)) >> M_S1DD) :
		((op_num == 2) ? ((MO << (15 - M_S2DD)) >> M_S2DD) :
			((op_num == 3) ? ((MO << (15 - M_DEDD)) >> M_DEDD) :
			(-1))));
	modo_lectura[1] = ((op_num == 1) ? ((MO << (15 - M_S1SA)) >> M_S1SA) :
		((op_num == 2) ? ((MO << (15 - M_S2SA)) >> M_S2SA) :
			((op_num == 3) ? ((MO << (15 - M_DESA)) >> M_DESA) :
			(-1))));
	modo_lectura[2] = ((op_num == 1) ? ((MO << (15 - M_S1DA)) >> M_S1DA) :
		((op_num == 2) ? ((MO << (15 - M_S2DA)) >> M_S2DA) :
			((op_num == 3) ? ((MO << (15 - M_DEDA)) >> M_DEDA) :
			(-1))));
	return modo_lectura;
}


short enviarOperando(short valor, char op_code, char op_num)
{
	char val, val2;
	val = (char)(valor >> 8);
	val2 = (char)(valor & 0x00FF);
	char* op_lec_mode = malloc(sizeof(char) * 3);
	op_lec_mode = obtenerModoLectura(op_num);
	switch(op_code){
		case 0x00:
			//PILA:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				short tmp_pp = PP;
				MEMORIA[PP] = val;
				PP--;
				MEMORIA[PP] = val2;
				PP--;
				if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP += 2;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				short dir = MEMORIA[PP];
				PP--;
				dir = dir << 8;
				dir += MEMORIA[PP];
				PP--;
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
				if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP += 2;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[PP];
				PP--;
				dir = dir << 8;
				dir += MEMORIA[PP];
				PP--;
				short dir2 = MEMORIA[dir];
				dir++;
				dir2 = dir2 << 8;
				dir2 += MEMORIA[dir];
				MEMORIA[dir2] = val2;
				dir2++;
				MEMORIA[dir2] = val;
				if ( ((MO << (15 - M_MPNA)) >> M_MPNA) ) PP += 2;
				return 0;
			}
			return -1;
		case 0x01:
			//DATA 1:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				D1 = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[D1] = val2;
				MEMORIA[D1 + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[D1];
				dir = dir << 8;
				dir += MEMORIA[D1 + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x02:
			//DATA 2:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				D2 = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[D2] = val2;
				MEMORIA[D2 + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[D2];
				dir = dir << 8;
				dir += MEMORIA[D2 + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x03:
			//DATA 3:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				D3 = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[D3] = val2;
				MEMORIA[D3 + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[D3];
				dir = dir << 8;
				dir += MEMORIA[D3 + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x04:
			//DATA 4:
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				D4 = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[D4] = val2;
				MEMORIA[D4 + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[D4];
				dir = dir << 8;
				dir += MEMORIA[D4 + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x05:
			//Puntero de Instruccion
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				IP = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[IP] = val2;
				MEMORIA[IP + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[IP];
				dir = dir << 8;
				dir += MEMORIA[IP + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x06:
			//Puntero de Datos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				DP = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[DP] = val2;
				MEMORIA[DP + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[DP];
				dir = dir << 8;
				dir += MEMORIA[DP + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x07:
			//Puntero de Pila
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				PP = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[PP] = val2;
				MEMORIA[PP + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[PP];
				dir = dir << 8;
				dir += MEMORIA[PP + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x08:
			//Puntero Auxiliar
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				PA = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[PA] = val2;
				MEMORIA[PA + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[PA];
				dir = dir << 8;
				dir += MEMORIA[PA + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x09:
			//Segmento de Instrucciones
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				IS = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[IS] = val2;
				MEMORIA[IS + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[IS];
				dir = dir << 8;
				dir += MEMORIA[IS + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x0A:
			//Segmento de Datos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				DS = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[DS] = val2;
				MEMORIA[DS + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[DS];
				dir = dir << 8;
				dir += MEMORIA[DS + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x0B:
			//Segmento de Pila
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				PS = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[PS] = val2;
				MEMORIA[PS + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[PS];
				dir = dir << 8;
				dir += MEMORIA[PS + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x0C:
			//Modos
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				MO = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[MO] = val2;
				MEMORIA[MO + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[MO];
				dir = dir << 8;
				dir += MEMORIA[MO + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x0D:
			//Estados
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				ES = valor;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[ES] = val2;
				MEMORIA[ES + 1] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir = MEMORIA[ES];
				dir = dir << 8;
				dir += MEMORIA[ES + 1];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
			}
			return -1;
		case 0x0E: ;
			//Memoria
			short dir = MEMORIA[IP];
			dir = dir << 8;
			IP++;
			dir += MEMORIA[IP];
			IP++;
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				short dir2 = MEMORIA[dir];
				dir2 = dir2 << 8;
				dir++;
				dir2 += MEMORIA[dir];
				MEMORIA[dir2] = val2;
				dir2++;
				MEMORIA[dir2] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir2 = MEMORIA[dir];
				dir2 = dir2 << 8;
				dir++;
				dir2 += MEMORIA[dir];
				dir = MEMORIA[dir2];
				dir = dir << 8;
				dir2++;
				dir += MEMORIA[dir2];
				MEMORIA[dir] = val2;
				dir++;
				MEMORIA[dir] = val;
				return 0;
			}
			return -1;
		case 0x0F: ;
			//Immediato
			short imm = MEMORIA[IP];
			imm = imm << 8;
			IP++;
			imm += MEMORIA[IP];
			IP++;
			if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				return -1;
			}
			if ( op_lec_mode[0] == 1 && op_lec_mode[1] == 0 && op_lec_mode[2] == 0 ) {
				//En Modo de Data Dirrecto, no hacemos nada, pero debemos resetear el puntero de instruccion:
				IP -= 2;
				//Basicamente, en ese conjunto de modos, la respuesta no nos importa y asi lo botamos
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 1 && op_lec_mode[2] == 0 ) {
				MEMORIA[imm] = val2;
				imm++;
				MEMORIA[imm] = val;
				return 0;
			} else if ( op_lec_mode[0] == 0 && op_lec_mode[1] == 0 && op_lec_mode[2] == 1 ) {
				short dir2 = MEMORIA[imm];
				dir2 = dir2 << 8;
				imm++;
				dir2 += MEMORIA[imm];
				MEMORIA[dir2] = val2;
				dir2++;
				MEMORIA[dir2] = val;
				return 0;
			}
			return -1;
		default:
			return -1;
	}
}