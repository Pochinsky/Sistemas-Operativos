C 		= gcc
CFLAGS1 = -Wall -g -o
CFLAGS2 = -Wall -g -c
C1		= main.c
C2		= ./header/table.c
C3		= ./header/process.c
C4		= ./header/menu.c
C5		= ./header/mechanics.c
H1		= ./header/table.h
H2		= ./header/process.h
H3		= ./header/menu.h
H4		= ./header/mechanics.c
H		= $(H1) $(H2) $(H3) $(H4)
O		= main.o table.o process.o menu.o mechanics.o
CL		= rm -rf *.o run

execute: run clean

memCheck: checkMemory clean

checkMemory:
	valgrind ./main.out

run:
	./main.out

compile: cc
	$(info "¡Compilacion terminada!")

cc: main table process menu mechanics
	$(C) $(CFLAGS1) main.out $(O)

main: $(H)
	$(info "... Comenzando compilacion ...")
	$(C) $(CFLAGS2) $(C1)

table: $(H1)
	$(C) $(CFLAGS2) $(C2)

process: $(H2)
	$(C) $(CFLAGS2) $(C3)

menu: $(H3)
	$(C) $(CFLAGS2) $(C4)

mechanics: $(H4)
	$(C) $(CFLAGS2) $(C5)

clean:
	@$(CL)
