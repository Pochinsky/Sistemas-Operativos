#include "table.h"

#define LEER 0
#define ESCRIBIR 1

/*
 * Funcion:		closePipes
 * Parametros:	read, pipe de lectura; write, pipe de escritura
 * Descripcion:	cierra un par de pipes
 * Retorno:		no retorna
 */
void closePipes(int read, int write);

/*
 * Funcion:		choiceDice
 * Parametros:	no recibe
 * Descripcion:	"tira el dado"
 * Retorno:		numero que sale en el dado
 */
int choiceDice();

/*
 * Funcion:		choiceSection1
 * Parametros:	no recibe
 * descripcion: determina que efecto ? realizar
 * retorno:		numero correspondiente a un cierto efecto
 */
int choiceSection1();

/*
 * Idem a choiceSection2 pero para efectos ??
 */
int choiceSection2(int number);
