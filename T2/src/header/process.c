#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "process.h"

void closePipes(int read, int write){
	if(close(read)==-1 || close(write)==-1){
		perror("ERROR: pipes no se han creado.\n");
		exit(EXIT_FAILURE);
	}
}

int choiceDice(){
	return (rand() % 6)+1;
}

int choiceSection1(){
	return (rand() % 5) +1;
}

int choiceSection2(int number){
	int opcion;
   	opcion = ((rand()*number) % 10)+1;
    if (1 <= opcion && opcion <= 3) { // todos retroceden 2
        return 1;
    }
    else if(4 <= opcion && opcion <= 5) { // los demas avanzan hasta la proxima blanca
        return 2;
    }
    else if(6 <= opcion && opcion <= 7) { // cambia con el que va ultimo
        return 3;
    }
    else if(8 <= opcion && opcion <= 9) { // cambia con el que va primero
        return 4;
    }
    else {
        return 5;
    }
}
