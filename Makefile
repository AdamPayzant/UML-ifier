CFLAGS = -fextended-indentifiers -Wall
CC = g++

umlify: main.o UMLify.o Object.o
	$(CC) $(CFLAGS) -o umlify main.o UMLify.o Object.o

main.o: main.cc UMLify.h
	$(CC) $(CFLAGS) -c main.cc

UMLify.o: UMLify.cc UMLify.h Object.o
	$(CC) $(CFLAGS) -c UMLify.cc

Object.o: Object.cc Object.o
	$(CC) $(CFLAGS) -c Object.cc

clean:
	rm *.o umlify