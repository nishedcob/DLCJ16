
#ifndef _CARGAR_H_
#define _CARGAR_H_

#define FILEDEF 0xD7C71600

////////////////Definir Mascara de Registros/////////////////
#define REG_MSK_RD1 0x0 // define Dato 1
#define REG_MSK_RD2 0x1 // define Dato 2
#define REG_MSK_RD3 0x2 // define Dato 3
#define REG_MSK_RD4 0x3 // define Dato 4
#define REG_MSK_RIP 0x4 // define puntero de instruccion
#define REG_MSK_RDP 0x5 // define puntero de datos
#define REG_MSK_RSP 0x6 // define puntero de pila
#define REG_MSK_RPA 0x7 // define puntero auxiliar
#define REG_MSK_RIS 0x8 // define segmento de instruccion
#define REG_MSK_RDS 0x9 // define segmento de dato
#define REG_MSK_RSS 0xA // define segmento de pila
#define REG_MSK_RMR 0xB // define modos de registro
#define REG_MSK_RFR 0xC // define banderas de registro
#define REG_MSK_P1R 0xD // define bit de pariedad para byte 1
#define REG_MSK_P2R 0xE // define bit de pariedad para bits 8-12
#define REG_MSK_PRP 0xF // define bit de parriedad para los bits de pariedad
/////////////////////////////////////////////////////////////

////////////////Define Functions////////////////
int cargarInstrucciones(char* archivo);
int cargarDemo();
////////////////////////////////////////////////

#endif