#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./header/process.h"
#include "./header/menu.h"
#include "./header/mechanics.h"

int main(int argc, char const *argv[]){
	/*
	 * Variables
	 */
	pid_t players[4];
	int padre_hijo[4][2];
	int hijo_padre[4][2];
	int posPlayer;
	int entrada, salida;
	ssize_t nread;
	Game* table;
	int flag;
	/*
	 * Creacion de jugadores
	 */
	table = newGame();
	posPlayer = getPos();
	posPlayer -= 1;
	for(int i=0; i<4; i++){
		if(pipe(padre_hijo[i])==-1 || pipe(hijo_padre[i])==-1){
			perror("ERROR: (pipes) no se han creado los pipes.\n");
			exit(EXIT_FAILURE);
		}
		if((players[i]=fork()) < 0){
			perror("ERROR: (fork) no se ha cread un jugador.\n");
			abort();
		}
		if(players[i] == 0){ /* proceso hijo */
			closePipes(hijo_padre[i][LEER], padre_hijo[i][ESCRIBIR]);
			if(i==posPlayer){ /* REVISAR */
				if(mainUser(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR], i+1, table) == -1){
					printf("ERROR: ha ocurrido un error durante la ejecución del jugador %d (process %d).\n", i+1, players[i]);
					exit(1);
				}
				exit(0);
			}
		}
		else{
			closePipes(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR]);
		}
	}
	/*
	 * Ejecucion del juego
	 */
	flag = True;
	printf("\n\t\t\t========== OCALIMOCHO ==========\n\n");
	printTable(table);
	sleep(1); 	
	while(flag){
		salida = 0;
		for(beginIteration(table); flag && (getMov(table) > -1 && getMov(table) < 4); nextIteration(table)){
			if(write(padre_hijo[getMov(table)][ESCRIBIR], &salida, 1) == -1){
				printf("ERROR: no se ha escrito al hijo %d (process %d).\n",getMov(table)+1, players[getMov(table)]);
				return 1;
			}
			if((nread=read(hijo_padre[getMov(table)][LEER], &entrada, 1)) == -1){
				printf("ERROR: (pipe lecture) no se ha leido el pipe del jugador %d (process %d).\n",getMov(table)+1,players[getMov(table)]);
				return -1;
			}
			else if(nread==0){
				printf("ERROR: (pipe close) se ha cerrado el pipe desde el jugador %d (process %d).\n",getMov(table)+1,players[getMov(table)]);
				flag = False;
			}
			else{
				printTable(table);
				switch(entrada){
					case 1:
						printf("El ganador es el jugador %d.\n",getMov(table)+1);
						flag = False;
						break;
					case 5:
						perderTurno(table);
						break;
					default:
						break;
				}
			}
			sleep(3);
		}
	}
	salida = -1;
	for(int i=0; i<4; i++){
		if(write(padre_hijo[i][ESCRIBIR], &salida, 1) == -1){
			printf("ERROR: no se ha escrito sobre el jugador %d.\n",i+1);
			return 1;
		}
		waitpid(players[i], NULL, 0);
		closePipes(padre_hijo[i][ESCRIBIR], hijo_padre[i][LEER]);
	}
	freeGame(table);
	printf("\n\t\t=== Juego terminado ===\n");
	return 0;
}
