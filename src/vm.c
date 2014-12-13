
#include <stdio.h>

#include "vm.h"
#include "registers.h"
#include "memoria.h"

int imprimerPila()
{
	//printf("MEMORIA_TAMANO = %d\n", MEMORIA_TAMANO);
	printf("---La Pila:---\n");
	short tmp_pp = PP;
	while (PP < (MEMORIA_TAMANO - 1)) {
		short tmp;
		PP++;
		tmp = MEMORIA[PP] << 8;
		PP++;
		tmp += MEMORIA[PP];
		printf("    %5d\n", D1);
		//printf("%5d -> %5d -> %5d\n", (PP - 1), D1, PP);
	}
	printf("--------------\n");
	PP = tmp_pp;
	return 0;
}
