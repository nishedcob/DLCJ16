
////////////////////////////////////Registros////////////////////////////////////

////////////Registros de Datos////////////
unsigned short D1, D2, D3, D4;
//////////////////////////////////////////

////////////Registros de Punteros////////////
unsigned short IP, PP, DP, PA;
/////////////////////////////////////////////

////////////Registros de Segmento////////////
unsigned short IS, PS, DS;
/////////////////////////////////////////////

////////////Registros de Banderas////////////
unsigned short MO, ES;
/////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////Banderas de Modo///////////////////////////////////////////////
#define M_MPNA 0x0 //Modo de la Pila ([0] Normal, 1 Ahorro)
// 1 NO ESTA EN USO
#define M_MOPI 0x2 //Modo Immediato ([0] Falso,  1  Verdadero) //
#define M_MOPV 0x3 //Modo Variable  ( 0  Falso, [1] Verdadero) // Modo de Operando
#define M_MOPC 0x4 //Modo Conteo    ([0] Falso,  1  Verdadero) //
// 5 NO ESTA EN USO
#define M_S1DD 0x6 //Modo Data Directo     ( 0  Falso, [1] Verdadero) //
#define M_S1SA 0x7 //Modo Una Direccion    ([0] Falso,  1  Verdadero) // Fuente 1 //
#define M_S1DA 0x8 //Modo Double Direccion ([0] Falso,  1  Verdadero) //          ////
#define M_S2DD 0x9 //Modo Data Directo     ( 0  Falso, [1] Verdadero) //          ////// Modo  de Lectura  de
#define M_S2SA 0xA //Modo Una Direccion    ([0] Falso,  1  Verdadero) // Fuente 2 ////// Operandos  con  Modo
#define M_S2DA 0xB //Modo Double Direccion ([0] Falso,  1  Verdadero) //          ////// Variable de Operando
#define M_DEDD 0xC //Modo Data Directo     ( 0  Falso, [1] Verdadero) //          ////
#define M_DESA 0xD //Modo Una Direccion    ([0] Falso,  1  Verdadero) // Destino  //
#define M_DEDA 0xE //Modo Double Direccion ([0] Falso,  1  Verdadero) //
// F NO ESTA EN USO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////Banderas de Estado/////////////////////////////////////////////
#define F_OVER 0x0 // Indica Overflow
// 1 NO ESTA EN USO
#define F_DIRE 0x2 // Indica Direccion
// 3 NO ESTA EN USO
#define F_INTE 0x4 // Indica Interrupcion
// 5 NO ESTA EN USO
#define F_TRAP 0x6 // Indica Trap
// 7 NO ESTA EN USO
#define F_SIGN 0x8 // Indica Signo
// 9 NO ESTA EN USO
#define F_CERO 0xA // Indica Cero
// B NO ESTA EN USO
#define F_ACAR 0xC // Indica Accareo
#define F_ACAX 0xD // Indica Accareo Auxiliar
// E NO ESTA EN USO
#define F_PARI 0xF // Indica Pariedad
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

