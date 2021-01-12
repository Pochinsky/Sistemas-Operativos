typedef struct {
    char *mesa; // tablero
    char signo; // creciente(1) o decreciente(-1)
    int largo; // largo tablero
    int mov; // variable para comenzar la iteracion de los jugadores
    int *players;// agregar jugadores
    int key1, key2, key3; // keys de la memoria compartida
}Game;

/*
 * Funcion:		newGame
 * Parametros:	no recibe
 * Descripcion:	inicializa un tablero
 * Retorno:		un tablero
 */
Game* newGame();

/*
 * Funcion:		newGame
 * Parametros:	no recibe
 * Descripcion: libera un tablero
 * Retorno:		no retorna
 */
void freeGame(Game* table);

/*
 * Funcion:		printTable
 * Parametros:	table, el tablero
 * Descripcion:	imprime el tablero en la consola
 * Retorno:		no retorna
 */
void printTable(Game* table);

/*
 * Funcion:		nextIteration
 * Parametros:	table, el tablero
 * Descripcion:	salta a la siguiente ronda
 * Retorno		no retorna
 */
void nextIteration(Game* table);

/*
 * Funcion:		beginIteration
 * Parametros: 	table, el tablero
 * Descripcion:	inicia una ronda
 * Retorno:		no retorna
 */
void beginIteration(Game* table);

/*
 * Funcion:		changeDirection
 * Parametros:	table, el tablero
 * Descripcion:	cambia el sentido de los turnos
 * Retorno:		no retorna
 */
void changeDirection(Game* table);

/*
 * Funcion:		changeSide
 * Parametros:	table, el tablero
 * Descripcion:	cambia el sentido del tablero
 * Retorno:		no retorna
 */
void changeSide(Game* table);

/*
 * Funcion:		changeLess
 * Parametros:	table, el tablero; player, jugador actual
 * Descripcion: cambia a player por el ultimo jugador
 * Retorno:		no retorna
 */
void changeLess(Game* table, int player);

/*
 * Funcion:		changeHighest
 * Parametros:	table, el tablero; player, jugador actual
 * Descripcion:	cambia a player por el primer jugador
 * Retorno:		no retorna
 */
void changeHighest(Game* table, int player);

/*
 * Funcion:		getMov
 * Parametros:	table, el tablero
 * Descripcion:	obtiene el numero de ronda
 * Retorno:		el numero de ronda
 */
int getMov(Game* table);

/*
 * Funcion:		retroceder
 * Parametros:	table, el tablero; player, jugador actual
 * Descripcion:	retrocede a player
 * Retorno:		no retorna
 */
void retroceder(Game* table, int player);

/*
 * Funcion:		perderTurno
 * Parametros:	table, el tablero
 * Descripcion:	se salta al siguiente jugador
 * Retorno:		no retorna
 */
void perderTurno(Game* table);

/*
 * Funcion:		todosRetroceden
 * Parametros:	table, el tablero
 * Descripcion:	retrocede a todos los jugadores
 * Retorno:		no retorna
 */
void todosRetroceden(Game* table);

/*
 * Funcion:		where
 * Parametros:	table, el tablero, pos
 * Descripcion:	encuentra la proxima casilla blanca	
 * Retorno:		el numero de la casilla blanca o -1 si no quedan1
 */
int where(Game* table, int pos);

/*
 * Funcion:		siguienteBlanca
 * Parametros:	table, el tablero; player, jugador actual
 * Descripcion:	mueve a player a la siguiente casilla blanca
 * Retorno:		no retorna
 */
void siguienteBlanca(Game* table, int player);
