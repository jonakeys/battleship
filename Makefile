CC=g++
CFLAGS=-c -Wall

all: main

main: main.o Field.o Ship.o Draw.o Loc.o
	$(CC) main.o Field.o Ship.o Draw.o Loc.o -o battleship

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Field.o: Field.cpp
	$(CC) $(CFLAGS) Field.cpp

Ship.o: Ship.cpp
	$(CC) $(CFLAGS) Ship.cpp

Draw.o: Draw.cpp
	$(CC) $(CFLAGS) Draw.cpp

Loc.o: Loc.cpp
	$(CC) $(CFLAGS) Loc.cpp

clean:
	rm -rf *.o battleship
 
