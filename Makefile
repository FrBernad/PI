#flags para la compilacion
cCFLAGS=-Wall -pedantic -std=c99 -fsanitize=address

#compilador
CC=gcc 

all:BDDT

BDDT: TAD.o BDDT.o 
	$(CC) $(CFLAGS) BDDT.o TAD.o -o BDDT

TAD.o: TAD.c
	$(CC) -c TAD.c $(CFLAGS) 

BDDT.o: BDDT.c
	$(CC) -c BDDT.c $(CFLAGS) 

clean: 
	rm -rf *.o BDDT
