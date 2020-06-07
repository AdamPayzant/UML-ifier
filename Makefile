umlify: main.o UMLify.o Object.o
	g++ -o umlify main.o UMLify.o Object.o

main.o: main.cc UMLify.h
	g++ -c main.cc

UMLify.o: UMLify.cc UMLify.h Object.o
	g++ -c UMLify.cc

Object.o: Object.cc Object.o
	g++ -c Object.cc

clean:
	rm *.o