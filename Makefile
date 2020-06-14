CFLAGS = -fextended-identifiers -Wall -std=c++0x -pthread
CC = g++

umlify: main.o UMLifier.o Object.o
	$(CC) $(CFLAGS) -o umlify main.o UMLifier.o Object.o

main.o: main.cc UMLifier.h
	$(CC) $(CFLAGS) -c main.cc

UMLifier.o: UMLifier.cc UMLifier.h Object.o
	$(CC) $(CFLAGS) -c UMLifier.cc

Object.o: Object.cc Object.h
	$(CC) $(CFLAGS) -c Object.cc

clean:
	rm *.o umlify