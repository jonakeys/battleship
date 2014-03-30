#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"
using namespace std;

void PutShipOnField(Ship& PutShip, Field& PutField);
Ship PlaceShip(int size);
void Draw(Field& Field1);

int main()
{
    Field P1Field;
    P1Field.Create();
    Draw(P1Field);

    cout << "Speler 1, plaats je schepen!\n\n"
	 << "Slagschip\n";
    Ship P1Battleship = PlaceShip(4);
    PutShipOnField(P1Battleship, P1Field);
    Draw(P1Field);
    cout << "Kruisers (1/2)\n";
    Ship P1Cruiser1 = PlaceShip(3);
    PutShipOnField(P1Cruiser1, P1Field);
    Draw(P1Field);
    cout << "Kruisers (2/2)\n";
    Ship P1Cruiser2 = PlaceShip(3);
    PutShipOnField(P1Cruiser2, P1Field);
    Draw(P1Field);
    cout << "Torpedoboten (1/3)\n";
    Ship P1TorpedoBoat1 = PlaceShip(2);
    PutShipOnField(P1TorpedoBoat1, P1Field);
    Draw(P1Field);
    cout << "Torpedoboten (2/3)\n";
    Ship P1TorpedoBoat2 = PlaceShip(2);
    PutShipOnField(P1TorpedoBoat2, P1Field);
    Draw(P1Field);
    cout << "Torpedoboten (3/3)\n";
    Ship P1TorpedoBoat3 = PlaceShip(2);
    PutShipOnField(P1TorpedoBoat3, P1Field);
    Draw(P1Field);
    cout << "Onderzeeërs (1/4)\n";
    Ship P1Submarine1 = PlaceShip(1);
    PutShipOnField(P1Submarine1, P1Field);
    Draw(P1Field);
    cout << "Onderzeeërs (2/4)\n";
    Ship P1Submarine2 = PlaceShip(1);
    PutShipOnField(P1Submarine2, P1Field);
    Draw(P1Field);
    cout << "Onderzeeërs (3/4)\n";
    Ship P1Submarine3 = PlaceShip(1);
    PutShipOnField(P1Submarine3, P1Field);
    Draw(P1Field);
    cout << "Onderzeeërs (4/4)\n";
    Ship P1Submarine4 = PlaceShip(1);
    PutShipOnField(P1Submarine4, P1Field);
    Draw(P1Field);
    
    return 0;
}

void PutShipOnField(Ship& PutShip, Field& PutField)
{
    int x = PutShip.GetX();
    int y = PutShip.GetY();
    int size = PutShip.GetSize();
    char direction = PutShip.GetDirection();
    switch(direction) {
    case 'b':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(y-i,x,size);
	}
	break;
    case 'o':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation((y+i),x,size);
	}
	break;
    case 'l':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(y,x-i,size);
	}
	break;
    case 'r':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(y,x+i,size);
	}
	break;
    }
}

Ship PlaceShip(int size)
{
    int x, y, nSize;
    char direction;

    nSize = size;

    cout << "x horizontaal (0-9): ";
    cin >> x;
    cout << "y verticaal (0-9): ";
    cin >> y;
    cout << "Richting ('b'oven, 'o'nder, 'l'inks, 'r'echts): ";
    cin >> direction;

    return Ship(x, y, direction, nSize);
}

void Draw(Field& Field1)
{
    system("clear");
    cout << endl
	 << "  ____________ ______  _____ _               _____ " << endl
	 << " |___  /  ____|  ____|/ ____| |        /\\   / ____|" << endl
	 << "    / /| |__  | |__  | (___ | |       /  \\ | |  __ " << endl
	 << "   / / |  __| |  __|  \\___ \\| |      / /\\ \\| | |_ |" << endl
	 << "  / /__| |____| |____ ____) | |____ / ____ \\ |__| |" << endl
	 << " /_____|______|______|_____/|______/_/    \\_\\_____|"
	 << endl << endl << endl; 
    Field1.Draw();
}
