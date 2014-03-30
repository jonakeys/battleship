CC=g++
CFLAGS=-c -Wall

all: main

main: main.o Field.o Ship.o
	$(CC) main.o Field.o Ship.o -o battleship

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Field.o: Field.cpp
	$(CC) $(CFLAGS) Field.cpp

Ship.o: Ship.cpp
	$(CC) $(CFLAGS) Ship.cpp

clean:
	rm -rf *.o battleship
 
