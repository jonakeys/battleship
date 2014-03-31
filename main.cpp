#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"
using namespace std;

void CreateShip(Ship& PlayerShip, int size, Field& PutField);
void Draw(Field& DrawField);

int main()
{
    Field P1Field, P2Field;
    Field P1HitField, P2HitField;
    
    Ship P1Battleship, P1Cruiser1, P1Cruiser2, P1TorpedoBoat1, P1TorpedoBoat2,
	P1TorpedoBoat3, P1Submarine1, P1Submarine2, P1Submarine3, P1Submarine4;
    
    P1Field.Create();
    P2Field.Create();
    P1HitField.Create();
    P2HitField.Create();
    Draw(P1Field);

    cout << "Speler 1, plaats je schepen!\n\n"
	 << "Slagschip\n";
    CreateShip(P1Battleship, 4, P1Field);
    cout << "Kruisers (1/2)\n";
    CreateShip(P1Cruiser1, 3, P1Field);
    cout << "Kruisers (2/2)\n";
    CreateShip(P1Cruiser2, 3, P1Field);
    cout << "Torpedoboten (1/3)\n";
    CreateShip(P1TorpedoBoat1, 2, P1Field);
    cout << "Torpedoboten (2/3)\n";
    CreateShip(P1TorpedoBoat2, 2, P1Field);
    cout << "Torpedoboten (3/3)\n";
    CreateShip(P1TorpedoBoat3, 2, P1Field);
    cout << "Onderzeeërs (1/4)\n";
    CreateShip(P1Submarine1, 1, P1Field);
    cout << "Onderzeeërs (2/4)\n";
    CreateShip(P1Submarine2, 1, P1Field);
    cout << "Onderzeeërs (3/4)\n";
    CreateShip(P1Submarine3, 1, P1Field);
    cout << "Onderzeeërs (4/4)\n";
    CreateShip(P1Submarine4, 1, P1Field);
  
    return 0;
}

void CreateShip(Ship& PlayerShip, int size, Field& PutField)
{
    int x, y;
    char direction;

    cout << "x horizontaal (0-9): ";
    cin >> x;
    cout << "y verticaal (0-9): ";
    cin >> y;
    cout << "Richting ('b'oven, 'o'nder, 'l'inks, 'r'echts): ";
    cin >> direction;

    PlayerShip.SetX(x);
    PlayerShip.SetY(y);
    PlayerShip.SetDirection(direction);
    PlayerShip.SetSize(size);

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
    
    Draw(PutField);
}

void Draw(Field& DrawField)
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
    DrawField.Draw();
}

