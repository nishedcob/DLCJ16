
#include <stdio.h>

#include "cargar.h"
#include "registers.h"
#include "memoria.h"

/*
 * Logica de Leer el archivo
 * consulte con el formato estandarizado que hemos desarollado
 * en "BinaryFormat.ods" en la Carpeta raiz del proyecto (DLCJ16)
 */
int cargarInstrucciones(char* archivo)
{
	//Abrir archivo y comprobar que esta abierto:
	FILE* f = fopen(archivo, "r");
	if ( f == NULL ) { // condicion para ver si se abre el archivo para leerlo o para botar el error
		printf("No se puede abrir el archivo %s!\n", archivo);
		return -1;
	} else {
		printf("Archivo %s abierto con exito!\n", archivo);
	}
	//Leer y guardar el numero magico del archivo:
	unsigned int filedef; // varibale positiva 
	fread(&filedef, sizeof(int), 1, f); //lee a nivel binario 
	//Comprobar Numero Magico para el tipo de archivo:
	/*if (filedef != FILEDEF) { // si no encuentra el archivo ejecutable 
		printf("El archivo %s no es un ejecutable de DLCJ16.\n", archivo); 
		fclose(f);// cierra el archivo
		return -2;//Envia el error del tipo de archivo
	}*/
	//Leer el resto del archivo:
	//Leer Longitud de la Seccion de Datos
	unsigned short data_longitud; 
	fread(&data_longitud, sizeof(short), 1, f);//lee y copia lo que lee a esa dirección 
	//Leer Mascara de los registros:
	unsigned short mascara_registros;
	fread(&mascara_registros, sizeof(short), 1, f);
	//Verificar la Mascara de Registros
	char par_bit = 0;//tipo char para almacenar la paridad
	int i;
	for (i = 8; i < 16; i++) par_bit += (mascara_registros >> i) % 2;//Dezplaza el numero de bits segun el contador
	par_bit %= 2;//convierte el bit de paridad 1 o 0
	if (par_bit != ((mascara_registros >> 3) % 2)) {
		printf("Primer Bit de Pariedad no esta bien. Saliendo. Usa la bandera -p para ejecutar el archivo normalmente.\n");
		return -3;
	}
	par_bit = 0;
	for (i = 3; i < 8; i++) par_bit += (mascara_registros >> i) % 2;
	par_bit %= 2;
	if (par_bit != ((mascara_registros >> 2) % 2)) {
		printf("Segundo Bit de Pariedad no esta bien. Saliendo. Usa la bandera -p para ejecutar el archivo normalmente.\n");
		return -4;
	}
	par_bit = 0;
	for (i = 1; i < 3; i++) par_bit += (mascara_registros >> i) % 2;
	par_bit %= 2;
	if (par_bit != ((mascara_registros) % 2)) {
		printf("Tercer Bit de Pariedad no esta bien. Saliendo. Usa la bandera -p para ejecutar el archivo normalmente.\n");
		return -5;
	}
	//Direcciones adentro del seccion de datos de el segmento de Instruccion, Datos y Pila
	unsigned short data_direcciones[3];
	fread(&data_direcciones, sizeof(short), 3, f);
	//Contar Registros para Leer:
	/*char num_registros = 0;
	for (i = 0; i < 13; i++){
		num_registros += (mascara_registros >> i) % 2;
	}*/
	//Leer los registros de datos segun la mascara de registros
	if (mascara_registros >> 15) fread(&D1, sizeof(short), 1, f);
	if ((mascara_registros >> 14) % 2) fread(&D2, sizeof(short), 1, f);
	if ((mascara_registros >> 13) % 2) fread(&D3, sizeof(short), 1, f);
	if ((mascara_registros >> 12) % 2) fread(&D4, sizeof(short), 1, f);
	//Leer los registros de punteros segun la mascara de registros
	if ((mascara_registros >> 11) % 2) fread(&IP, sizeof(short), 1, f);
	if ((mascara_registros >> 10) % 2) fread(&PP, sizeof(short), 1, f);
	if ((mascara_registros >> 9) % 2) fread(&DP, sizeof(short), 1, f);
	if ((mascara_registros >> 8) % 2) fread(&PA, sizeof(short), 1, f);
	//Leer los registros de segmento segun la mascara de registros
	if ((mascara_registros >> 7) % 2) fread(&IS, sizeof(short), 1, f);
	if ((mascara_registros >> 6) % 2) fread(&PS, sizeof(short), 1, f);
	if ((mascara_registros >> 5) % 2) fread(&DS, sizeof(short), 1, f);
	//Leer los registros de banderas segun la mascara de registros
	if ((mascara_registros >> 4) % 2) fread(&MO, sizeof(short), 1, f);
	if ((mascara_registros >> 3) % 2) fread(&ES, sizeof(short), 1, f);
	//Saltar un byte (debe ser 00, pero no nos importa si es o no es porque no se lo utiliza)
	char basura;
	fread(&basura, sizeof(char), 1, f);
	for (i = 0; i < data_direcciones[0]; i++) fread(&basura, sizeof(char), 1, f);
	//Leer Segmento de Instruccion
	fread(&MEMORIA[IS], sizeof(char), (data_direcciones[1] - data_direcciones[0]), f);
	//Leer Segmento de Datos
	fread(&MEMORIA[DS], sizeof(char), (data_direcciones[2] - data_direcciones[1]), f);
	//Leer Segmento de Pila
	fread(&MEMORIA[PS], sizeof(char), (data_longitud - data_direcciones[2]), f);
	//Cerrar el archivo:
	fclose(f);
	return 0;
}

/// *
int cargarDemo()
{
	MEMORIA[0] = 0x00;
	MEMORIA[1] = 0x01;
	MEMORIA[2] = 0x00;
	MEMORIA[3] = 0x03;
	/*MEMORIA[4] = 0x00;
	MEMORIA[5] = 0x05;
	MEMORIA[6] = 0x0F;
	MEMORIA[7] = 0xFF;*/
	MEMORIA[4] = 0x10;
	MEMORIA[5] = 0x01;
	MEMORIA[6] = 0x10;
	MEMORIA[7] = 0x01;
	MEMORIA[8] = 0x00;
	MEMORIA[9] = 0x05;
	MEMORIA[10] = 0x30;
	MEMORIA[11] = 0x04;
	MEMORIA[12] = 0x0F;
	MEMORIA[13] = 0xFF;
	//Salir con Exito
	return 0;
}
//* /

/*
MODA	0x0001 (Modo de Ahorro, operaciones no se hacen POP de la Pila)
MODP	0x0002 (Modo de Pila, operaciones hacen un POP de la Pila)
MODI	0x0003 (Modo Immediato, todo operando de 12-bit es un constante)
MODV	0x0004 (Modo Variable, todo operando de 12-bit da modo a los operandos de 16 bits que siguen)
MODC	0x0005 (Modo Conteo, todo operando de 12-bit repite la instruccion un numero de veces indicado)
///////////////////----------------------////////////////////////////
F1DD	0x0101 (Modo Data Directo para Fuente 1)
F1SA	0x0102 (Modo Una Direccion para Fuente 1)MODO DE OPERANDO DE FUENTE 1 (MODO DE LECTURA)
F1DA	0x0103 (Modo Double Direccion para Fuente 1)
///////////////////////////////////////////////////////////
F2DD	0x0201 (Modo Data Directo para Fuente 2)
F2SA	0x0202 (Modo Una Direccion para Fuente 2)MODO DE OPERANDO DE FUENTE 2 (MODO DE LECTURA)
F2DA	0x0203 (Modo Double Direccion para Fuente 2)
//////////////////////////////////////////////////////////
DEDD	0x0301 (Modo Data Directo para Destino)
DESA	0x0302 (Modo Una Direccion para Destino)MODOS DE OPERANDO DE DESTINO (MODO DE LECTURA)
DEDA	0x0303 (Modo Double Direccion para Destino)
*/
/* Prueba de banderas de modo: */
/*
int cargarDemo()
{
	MEMORIA[0] = 0x00;
	MEMORIA[1] = 0x01;
	MEMORIA[2] = 0x00;
	MEMORIA[3] = 0x02;
	MEMORIA[4] = 0x00;
	MEMORIA[5] = 0x03;
	MEMORIA[6] = 0x00;
	MEMORIA[7] = 0x04;
	MEMORIA[8] = 0x00;
	MEMORIA[9] = 0x05;
	MEMORIA[10] = 0x01;
	MEMORIA[11] = 0x01;
	MEMORIA[12] = 0x01;
	MEMORIA[13] = 0x02;
	MEMORIA[14] = 0x01;
	MEMORIA[15] = 0x03;
	MEMORIA[16] = 0x02;
	MEMORIA[17] = 0x01;
	MEMORIA[18] = 0x02;
	MEMORIA[19] = 0x02;
	MEMORIA[20] = 0x02;
	MEMORIA[21] = 0x03;
	MEMORIA[22] = 0x03;
	MEMORIA[23] = 0x01;
	MEMORIA[24] = 0x03;
	MEMORIA[25] = 0x02;
	MEMORIA[26] = 0x03;
	MEMORIA[27] = 0x03;
	MEMORIA[28] = 0x0F;
	MEMORIA[29] = 0xFF;
	//Salir con Exito
	return 0;
}
*/