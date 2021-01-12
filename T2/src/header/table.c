#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "table.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"


Game* newGame(){
	/*
	 * Variables varias
	 */
	int i;
	Game* table;
	/*
	 * 0: casilla blanca
	 * 1: casilla ?
	 * 2: casilla ??
	 */
	char temp[] = {'0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0',
                    '0', '1', '0', '1', '0', '2', '0', '0', '0', '0', '1',
                    '2', '1', '2', '1', '2', '1', '0'};
	/*
	 * Variables para memoria compartida
	 */
	int shm_id1, shm_id2, shm_id3;
	key_t mem_key1, mem_key2, mem_key3;
	mem_key1 = ftok(".", 1);
	mem_key2 = ftok(".", 2);
	mem_key3 = ftok(".", 3);
	shm_id1 = shmget(mem_key1, sizeof(table), IPC_CREAT|0666);
	if(shm_id1 < 0){
		printf("ERROR: (dynamic memory key) no se ha creado el tablero.\n");
		exit(1);
	}
	shm_id2 = shmget(mem_key2, sizeof(int)*29, IPC_CREAT|0666);
	if(shm_id2 < 0){
		printf("ERROR: (dynamic memory key) no se ha creado el tablero.\n");
		exit(1);
	}
	shm_id3 = shmget(mem_key3, sizeof(int)*4, IPC_CREAT|0666);
	if(shm_id3 < 0){
		printf("ERROR: (dynamic memory key) no se ha creado el tablero.\n");
		exit(1);
	}
	/*
	 * Tablero
	 */
	table = (Game*)shmat(shm_id1, (void*)0, 0);
	if(table == (Game*)-1){
		printf("ERROR: no se ha creado el tablero.\n");
		exit(1);
	}
	table->largo = 29;
	table->signo = 1;
	table->mesa = (char*)shmat(shm_id2, (void*)0, 0);
	if(table->mesa == (char*)-1){
		printf("ERROR: (array table) no se ha creado el tablero.\n");
		exit(1);
	}
	for(i=0; i<29; i++)
		table->mesa[i] = temp[i];
	table->players = (int*)shmat(shm_id3, (void*)0, 0);
	if(table->players == (int*)-1){
		printf("ERROR: (array players) no se ha creado el tablero.\n");
		exit(1);
	}
	for(i=0; i<4; i++)
		table->players[i] = 1;
	table->key1 = shm_id1;
	table->key2 = shm_id2;
	table->key3 = shm_id3;
	return table;
}

void freeGame(Game* table){
    shmdt(table->mesa);
    shmdt(table->players);
    shmctl(table->key3, IPC_RMID, NULL);
    shmctl(table->key2, IPC_RMID, NULL);
    shmctl(table->key1, IPC_RMID, NULL);
    shmdt(table);
}

void printTable(Game* table){
	int i;
    printf("\n\t\t\t=========================== OCALIMOCHO ===========================\n");
    printf("   1   |");
    for(i=1; i<table->largo-1; i++)
        printf(" %d%s|", i+1, (i+1 > 9 ? " ": "  "));
    printf(" 29\n");
    printf("INICIO |");
    for(i = 1; i < table->largo - 1; i++){
        if(table ->mesa[i] != '0')
			printf(" %s |", (table->mesa[i] == '1'? "? " : "??"));
        else
			printf(" %s |", "  ");
    }
    printf(" FINAL\n");
    for(i=0; i<table->largo; i++){
        //player 1
        if(table->players[0] == i+1)
			printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, (i==0 || i==28) ? " 1" : "1");
        else
			printf("%s", (i==0) ? "  " : " ");
        //player 2
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, (table->players[1] == i+1) ? "2" : " ");
        //player 3
        printf(ANSI_COLOR_YELLOW  "%s" ANSI_COLOR_RESET, (table->players[2] == i+1)? "3" : " ");
        //player 4
        if(table->players[3] == i+1){
            if (i == 0) {
                printf(ANSI_COLOR_BLUE "4  " ANSI_COLOR_RESET "|");
            }
            else if(i == 28) {
                printf(ANSI_COLOR_BLUE  "4" ANSI_COLOR_RESET "\n");
            }
            else {
                printf(ANSI_COLOR_BLUE  "4" ANSI_COLOR_RESET "|");
            }
        }
        else{
            if (i == 0) {
                printf("   |");
            }
            else if(i == 28) {
                printf("\n");
            }
            else {
                printf(" |");
            }
            
        } 
    }
    printf("Jugador 1: %d; ", table->players[0]);
    printf("Jugador 2: %d; ", table->players[1]);
    printf("Jugador 3: %d; ", table->players[2]);
    printf("Jugador 4: %d\n", table->players[3]);
    printf("             ===============================================================\n");
    printf("\n");
}

void nextIteration(Game* table){
	table->mov = table->mov+table->signo;
}

void beginIteration(Game* table){
	if(table->signo == 1)
		table->mov = 0;
	else
		table->mov = 3;
}

void changeDirection(Game* table){
	table->signo = table->signo*(-1);
}

void changeSide(Game* table){
	int i;
	char temp;
	for(i=0; i<table->largo/2; i++){
		temp = table->mesa[i];
		table->mesa[i] = table->mesa[table->largo-i-1];
		table->mesa[table->largo-i-1] = temp;
		if(table->mesa[i]!='0')
			table->mesa[i] = (table->mesa[i]=='1'?'2':'1');
		if(table->mesa[table->largo-i-1]!='0')
			table->mesa[table->largo-i-1] = (table->mesa[table->largo-i-1]=='1'?'2':'1');
		if(table->mesa[i]!='0')
			table->mesa[i]=(table->mesa[i]=='1'?'2':'1');
		for(i=0; i<4; i++)
			table->players[i] = 29-table->players[i]+1;
	}		
}

void changeLess(Game* table, int player){
	int i, player2, less=100;
	for(i=0; i<4; i++){
		if(table->players[i] < less){
			less = table->players[i];
			player2 = i;
		}
	}
	table->players[player2] = table->players[player-1];
	table->players[player-1] = less;
}

void changeHighest(Game* table, int player){
	int i, player2, max=-1;
	for(i=0; i<4; i++){
		if(table->players[i] > max){
			max = table->players[i];
			player2 = i;
		}
	}
	table->players[player2] = table->players[player-1];
	table->players[player-1] = max;
}

int getMov(Game* table){
	return table->mov;
}
	
void retroceder(Game* table, int player){
	int i;
	for(i=0; i<4; i++)
		if(i!=player-1)
			table->players[i] += (table->players[i]==1?0:-1);
}

void perderTurno(Game* table){
	/*
	 * REVISAR
	 */
	table->mov = table->mov+table->signo;
	if(getMov(table)==-1||getMov(table)==4){
		if(getMov(table)==-1)
			table->mov=3;
		else
			table->mov=0;
	}
}

void todosRetroceden(Game* table){
	int i;
	for(i=0; i<4; i++){
		table->players[i] += -2;
		if(table->players[i] < 1)
			table->players[i] = 1;
	}
}

int where(Game* table, int pos){
	int i;
	for(i=pos; i<28; i++)
		if(table->mesa[i]=='0')
			return i+1;
	return -1;		
}

void siguienteBlanca(Game* table, int player){
	int i, avanza;
	for(i=0; i<4; i++){
		if(i!=player-1){
			avanza = where(table,table->players[i]);
		   	if(avanza!=-1){
			   	table->players[i] = avanza;
			}
		}
	}
}

