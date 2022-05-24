# To compile prog:
#    make
#----------------------------------------------------------------------
CC=gcc
CFLAGS=-g -Wall -std=c99
FLAGSFINAL = -Wall -std=c99 -O3
FILES = $(shell ls Surpresa/*.camp)

campista: main.o admissivel.o
	$(CC) $(FLAGSFINAL) -o campista main.o admissivel.o

teste: main.o admissivel.o
	$(CC) $(CFLAGS) -o campista main.o admissivel.o

main.o: main.c admissivel.h
	$(CC) -c $(CFLAGS) main.c

admissivel.o: admissivel.c admissivel.h
	$(CC) -c $(CFLAGS) admissivel.c

clean::
	rm -f *.o core a.out campista *~

t: 
	for F in ${FILES}; do ./campista $${F} ; done;
