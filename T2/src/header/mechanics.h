#define True 1
#define False 0

/*
 * Funcion:		movBot
 * Parametros:	numPlayer, jugador actual; table, tablero
 * Descripcion:	mueve a un jugador y ejecuta efectos
 * retorno:		0, nadie llego al final; 1, alguien llego al final
 */
int movBot(int numPlayer, Game* table);

/*
 * Funcion:		mainBot
 * Parametros:	lPipe, pipe de lectura; ePipe, pipe de escritura
 * 				numPlayer, jugador actual; table, tablero
 * Descripcion:	realiza el movimiento del jugador y comunicacion
 * 				entre pipes
 * retorno:		0, todo correcto; -1, algo fallo
 */
int mainBot(int lPipe, int ePipe, int numPlayer, Game* table);

/*
 * Idem a mainBot, pero pensado para el jugador controlado
 * por el usuario que utilice el programa
 */
int mainUser(int lPipe, int ePipe, int numPlayer, Game* table);

/*
 * Idem a movUser, pero pensado para el jugador controlado
 * por el usuario que utilice el programa.
 */
int movUser(int numPlayer, Game* table);
