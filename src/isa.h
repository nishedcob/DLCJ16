
#ifndef _ISA_H_
#define _ISA_H_

////////////////Define Function Pointers////////////////
int (*op_func)(int);
////////////////////////////////////////////////////////

////////////////Define Functions////////////////
int ejecutarInstruccion() ;
////////////////////////////////////////////////

////////////Define Instructions////////////
int MODA(int operands);
int MODP(int operands);
int MODI(int operands);
int MODV(int operands);
int MODC(int operands);
int F1DD(int operands);
int F1SA(int operands);
int F1DA(int operands);
int F2DD(int operands);
int F2SA(int operands);
int F2DA(int operands);
int DEDD(int operands);
int DESA(int operands);
int DEDA(int operands);
int SOVE(int operands);
int SDIR(int operands);
int SINT(int operands);
int STRP(int operands);
int SSIG(int operands);
int SCER(int operands);
int SACR(int operands);
int SACX(int operands);
int SPAR(int operands);
int ROVE(int operands);
int RDIR(int operands);
int RINT(int operands);
int RTRP(int operands);
int RSIG(int operands);
int RCER(int operands);
int RACR(int operands);
int RACX(int operands);
int RPAR(int operands);
int SALR(int operands);
int EMPU(int operands);
int SCRP(int operands);
int SUMP(int operands);
int RESP(int operands);
int MULP(int operands);
int DIVP(int operands);
int MDUP(int operands);
int PSHL(int operands);
///////////////////////////////////////////

////////Metodos de Lectura Auxiliar////////
int operand_mode();
char* obtenerCodigoOp(int opers);
short obtenerOperando(char op_code, char op_num);
char* obtenerModoLectura(char op_num);
short enviarOperando(short valor, char op_code, char op_num);
///////////////////////////////////////////

#endif
