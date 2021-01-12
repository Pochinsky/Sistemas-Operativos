#include <stdio.h>
#include "menu.h"

int getPos(){
	int pos;
	printf("\n\t\t\t========== OCALIMOCHO ==========\n\n");
	printf("\t\tIngrese que Jugador desea ser [1|2|3|4]: ");
	scanf("%d", &pos);
	return pos;
}
