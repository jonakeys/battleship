CC=g++
CFLAGS=-c -Wall
SRCDIR=src
BUILDDIR=build

all: main

main: main.o Field.o Ship.o Draw.o Loc.o AI.o
	$(CC) main.o Field.o Ship.o Draw.o Loc.o AI.o -o battleship

main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/main.cpp

Field.o: $(SRCDIR)/Field.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/Field.cpp

Ship.o: $(SRCDIR)/Ship.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/Ship.cpp

Draw.o: $(SRCDIR)/Draw.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/Draw.cpp

Loc.o: $(SRCDIR)/Loc.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/Loc.cpp

AI.o: $(SRCDIR)/AI.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/AI.cpp

clean:
	rm -rf $(BUILDDIR)/*.o battleship
 
