#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "process.h"
#include "mechanics.h"

int movBot(int numPlayer, Game* table){
	int dice;
	int opcion = 1;
	int salida = 0;
	dice = choiceDice();
	printf("\n\t\tJugador: %d - Dado: %d - ", numPlayer, dice);
	table->players[numPlayer-1] += dice;
	printf("Pos: %d\n",table->players[numPlayer]);

	switch(table->mesa[table->players[numPlayer-1]-1]){
		case '1':
			printf("\n\t\tCaiste en una casilla ?\n");
			opcion = choiceSection1();
			switch(opcion){
				case 1:
					printf("\n\t\tRetrocedes una casilla!\n");
					table->players[numPlayer-1] += -1;
					break;
				case 2:
					printf("\n\t\tEl resto retrocede una casilla!\n");
					retroceder(table, numPlayer);
					break;
				case 3:
					printf("\n\t\tAvanzas una casilla blanca!\n");
					table->players[numPlayer-1] += 1;
					break;
				case 4:
					printf("\n\t\tEl siguiente pierde su turno!\n");
					salida = 5;
					break;
				case 5:
					printf("\n\t\tCambio el sentido!\n");
					changeDirection(table);
					break;
				default:
					break;
			}
			break;
		case '2':
			printf("\n\t\tCaiste en una casilla ??\n");
			switch(opcion){
				case 1:
					printf("\n\t\tTodos retroceden 2 casillas!\n");
					todosRetroceden(table);
					break;
				case 2:
					printf("\n\t\tEl resto avanza a la siguiente casilla blanca!\n");
					siguienteBlanca(table,numPlayer);
					break;
				case 3:
					printf("\n\t\tCambias con el ultimo!\n");
					changeLess(table, numPlayer);
					break;
				case 4:
					printf("\n\t\tCambias con el primero!\n");
					changeHighest(table, numPlayer);
					break;
				case 5:
					printf("\n\t\tCambia el sentido del tablero!\n");
					changeSide(table);
					break;
				default:
					break;	
			}
			break;
		default:
			printf("\n\n\n");
			break;
	}
	if(table->players[numPlayer-1] >= table->largo){
		table->players[numPlayer-1] = 29;
		salida = 1;
	}
	return salida;
}

int mainBot(int lPipe, int ePipe, int numPlayer, Game* table){
	int flag = True;
	ssize_t nread;
	char entrada, salida;
	time_t t;
	srand((unsigned)(((unsigned)(time(&t))%(numPlayer+ePipe))*(lPipe-getpid())));
	while(flag){
		if((nread=read(lPipe, &entrada, 1)) == -1){
			printf("ERROR: (pipe lecture) no se ha leido el pipe en el jugador %d (process %d).\n",numPlayer,getpid());
			return -1;
		}
		else if(nread==0){
			printf("MESSAGE: pipe cerrado desde el padre al jugador %d (process %d).\n",numPlayer,getpid());
			flag = False;
		}
		else{
			switch(entrada){
				case -1:
					flag = False;
					break;
				case 0:
					salida = movBot(numPlayer, table);
					if(write(ePipe, &salida, 1) == -1){
						printf("ERROR: (pipe write) no se ha escrito al padre (process %d).\n",getpid());
						return -1;
					}	
					break;
				default:
					printf("ERROR: lectura de datos.\n");
					printf("Hijo %d recibe %d (process %d).\n", numPlayer, entrada, getpid());
					return -1;	
			}
		}
	}
	closePipes(lPipe, ePipe);
	return 0;
}

int movUser(int numPlayer, Game* table){
	int dice;
	int opcion = 1;
	int salida = 0;
	char decision;
	dice = choiceDice();
	printf("\n\t\tJugador: %d - Dado: %d - ", numPlayer, dice);
	table->players[numPlayer-1] += dice;
	printf("Pos: %d\n",table->players[numPlayer]);

	switch(table->mesa[table->players[numPlayer-1]-1]){
		case '1':
			printf("\n\t\tCaiste en una casilla ? - Deseas activarla? [y|n]: ");
			scanf("%c",&decision);
			if(decision == 'y'){
				opcion = choiceSection1();
				switch(opcion){
					case 1:
						printf("\n\t\tRetrocedes una casilla!\n");
						table->players[numPlayer-1] += -1;
						break;
					case 2:
						printf("\n\t\tEl resto retrocede una casilla!\n");
						retroceder(table, numPlayer);
						break;
					case 3:
						printf("\n\t\tAvanzas una casilla blanca!\n");
						table->players[numPlayer-1] += 1;
						break;
					case 4:
						printf("\n\t\tEl siguiente pierde su turno!\n");
						salida = 5;
						break;
					case 5:
						printf("\n\t\tCambio el sentido!\n");
						changeDirection(table);
						break;
					default:
						break;
				}
			}
			break;
		case '2':
			printf("\n\t\tCaiste en una casilla ?? - Deseas activarla? [y|n]: ");
			scanf("%c",&decision);
			if(decision == 'y'){
				switch(opcion){
					case 1:
						printf("\n\t\tTodos retroceden 2 casillas!\n");
						todosRetroceden(table);
						break;
					case 2:
						printf("\n\t\tEl resto avanza a la siguiente casilla blanca!\n");
						siguienteBlanca(table,numPlayer);
						break;
					case 3:
						printf("\n\t\tCambias con el ultimo!\n");
						changeLess(table, numPlayer);
						break;
					case 4:
						printf("\n\t\tCambias con el primero!\n");
						changeHighest(table, numPlayer);
						break;
					case 5:
						printf("\n\t\tCambia el sentido del tablero!\n");
						changeSide(table);
						break;
					default:
						break;	
				}
			}
			break;
		default:
			printf("\n\n\n");
			break;
	}
	if(table->players[numPlayer-1] >= table->largo){
		table->players[numPlayer-1] = 29;
		salida = 1;
	}
	return salida;
}

int mainUser(int lPipe, int ePipe, int numPlayer, Game* table){
	int flag = True;
	ssize_t nread;
	int entrada, salida;
	time_t t;
	srand((unsigned)(((unsigned) (time(&t)) % (numPlayer+ePipe))*(lPipe-getpid())));
	while(flag){
		if((nread=read(lPipe,&entrada, 1)) == -1){
			printf("ERROR: (lecture pipe) no se ha leido el pipe en el jugador %d (process %d).\n",numPlayer,getpid());
			return -1;
		}
		else if(nread == 0){
			printf("MESSAGE: pipe cerrado desde el padre al jugador %d (process %d).\n",numPlayer,getpid());
			flag = False;
		}
		else{
			switch(entrada){
				case -1:
					flag = False;
					break;
				case 0:
					salida = movUser(numPlayer, table);
					if(write(ePipe, &salida, 1) == -1){
						printf("ERROR: no se ha escrito al padre (process %d).\n",getpid());
						return -1;
					}
					break;
				default:
					printf("ERROR: lectura de datos.\n");
					printf("Hijo %d recibe %d (process %d).\n",numPlayer, entrada, getpid());
					return -1;	
			}
		}
	}
	closePipes(lPipe, ePipe);
	return 0;
}
