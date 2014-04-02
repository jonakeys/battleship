#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"
#include "Draw.h"
using namespace std;

void CreateShip(Ship& PlayerShip, int size, Field& PutField);
void ShipsToVector(vector <Ship>& PutVector, Ship& Battleship, Ship& Cruiser1, Ship& Cruiser2,
		   Ship& TorpedoBoat1, Ship& TorpedoBoat2, Ship& TorpedoBoat3, Ship& Submarine1,
		   Ship& Submarine2, Ship& Submarine3, Ship& Submarine4);
void PlaceShips(Field& PutField, Field& Put2Field, vector <Ship>& vShips, int player);
void DrawShipsRemaining(vector <Ship>& vShips);
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField);
int LocUpFree(int x, int y, int size, Field& TestField);
int LocDownFree(int x, int y, int size, Field& TestField);
int LocLeftFree(int x, int y, int size, Field& TestField);
int LocRightFree(int x, int y, int size, Field& TestField);

int main()
{
    Field P1Field, P2Field;
    Field P1HitField, P2HitField;
    bool PLAY = true;
    int nTurn = 0, P1Counter = 20, P2Counter = 20;
    
    Ship P1Battleship, P1Cruiser1, P1Cruiser2, P1TorpedoBoat1, P1TorpedoBoat2,
	P1TorpedoBoat3, P1Submarine1, P1Submarine2, P1Submarine3, P1Submarine4;
    vector <Ship> vP1Ships;
    ShipsToVector(vP1Ships, P1Battleship, P1Cruiser1, P1Cruiser2, P1TorpedoBoat1, P1TorpedoBoat2,
		  P1TorpedoBoat3, P1Submarine1, P1Submarine2, P1Submarine3, P1Submarine4);
    Ship P2Battleship, P2Cruiser1, P2Cruiser2, P2TorpedoBoat1, P2TorpedoBoat2,
	P2TorpedoBoat3, P2Submarine1, P2Submarine2, P2Submarine3, P2Submarine4;
    vector <Ship> vP2Ships;
    ShipsToVector(vP2Ships, P2Battleship, P2Cruiser1, P2Cruiser2, P2TorpedoBoat1, P2TorpedoBoat2,
		  P2TorpedoBoat3, P2Submarine1, P2Submarine2, P2Submarine3, P2Submarine4);
    
    P1Field.Create();
    P2Field.Create();
    P1HitField.Create();
    P2HitField.Create();

    DrawScreen(P1Field, P2Field);
    PlaceShips(P1Field, P2Field, vP1Ships, 1);
    DrawScreen(P1HitField, P2Field);
    PlaceShips(P1HitField, P2Field, vP2Ships, 2);
    DrawScreen(P2HitField, P1HitField);
    cout << endl << endl;

    while(PLAY)
    {
	if(nTurn % 2 == 0) {
	    int nGuess = Guess(nTurn, P2Field, P2HitField);
	    P1Counter -= nGuess;
	    DrawScreen(P2HitField, P1HitField);
	    if(nGuess==1)
		cout << "Speler 1 schoot raak :-)\n\n";
	    else
		cout << "Speler 1 schoot mis :-(\n\n";
	}
	if(nTurn % 2 != 0) {
	    int nGuess = Guess(nTurn, P1Field, P1HitField);
	    P2Counter -= nGuess;
	    DrawScreen(P2HitField, P1HitField);
	    if(nGuess==1)
		cout << "Speler 2 schoot raak :-)\n\n";
	    else
		cout << "Speler 2 schoot mis :-(\n\n";
	}
	if(P1Counter == 0 || P2Counter == 0) {
	    PLAY = false;
	}
	++nTurn;
    }
    
    if(P1Counter == 0) {
	cout << "Speler 1 heeft gewonnen!\n";
    }
    else if(P2Counter == 0) {
	cout << "Speler 2 heeft gewonnen!\n";
    }

    cout << "Bedankt voor het spelen, tot ziens!" << endl;

    return 0;
}

void CreateShip(Ship& PlayerShip, int size, Field& PutField)
{
    int x, y;
    char cX;
    char direction;
    int nUp = 0, nDown = 0, nLeft = 0, nRight = 0;
    bool DirOk = false;
    bool DONE = false;
    
    while(!DONE) {
	cout << "\nKies startcoordinaat (bijvoorbeeld: 'c 6'): ";
	cin >> cX  >> y;
	if(size > 1) {
	    cout << "Richting ('b'oven, 'o'nder, 'l'inks, 'r'echts): ";
	    cin >> direction;
	}
	else {
	    direction = 'r';
	}
	
	switch(cX) {
	case 'a':
	    x = 0;
	    break;
	case 'b':
	    x = 1;
	    break;
	case 'c':
	    x = 2;
	    break;
	case 'd':
	    x = 3;
	    break;
	case 'e':
	    x = 4;
	    break;
	case 'f':
	    x = 5;
	    break;
	case 'g':
	    x = 6;
	    break;
	case 'h':
	    x = 7;
	    break;
	case 'i':
	    x = 8;
	    break;
	case 'j':
	    x = 9;
	    break;
	default:
	    break;
	}

	nUp = LocUpFree(x,y,size,PutField);
	nDown = LocDownFree(x,y,size,PutField);
	nLeft = LocLeftFree(x,y,size,PutField);
	nRight = LocRightFree(x,y,size,PutField);

	if((nUp == 0) && (nUp == 0) && (nLeft == 0) && (nRight == 0)) {
	    cout << "Deze locatie is niet beschikbaar. Probeer het opnieuw.\n";
	}
	
	if(direction == 'b' && nUp==1) {
	    DirOk = true;
	}
	if(direction == 'o' && nDown==1) {
	    DirOk = true;
	}
	if(direction == 'l' && nLeft==1) {
	    DirOk = true;
	}
	if(direction == 'r' && nRight==1) {
	    DirOk = true;
	}

	if(DirOk == false) {
	    cout << "Deze richting is niet mogelijk. Probeer het opnieuw.\n";
	}
	
	if((nUp==1||nDown==1||nLeft==1||nRight==1) && (DirOk==true)) {
	    DONE = true;
	}
    }
    
    PlayerShip.SetX(x);
    PlayerShip.SetY(y);
    PlayerShip.SetDirection(direction);
    PlayerShip.SetSize(size);

    switch(direction) {
    case 'b':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x,y-i,size);
	}
	break;
    case 'o':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x,y+i,size);
	}
	break;
    case 'l':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x-i,y,size);
	}
	break;
    case 'r':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x+i,y,size);
	}
	break;
    }
}

void ShipsToVector(vector <Ship>& PutVector, Ship& Battleship, Ship& Cruiser1, Ship& Cruiser2,
		   Ship& TorpedoBoat1, Ship& TorpedoBoat2, Ship& TorpedoBoat3, Ship& Submarine1,
		   Ship& Submarine2, Ship& Submarine3, Ship& Submarine4)
{
    PutVector.push_back(Battleship);
    PutVector.push_back(Cruiser1);
    PutVector.push_back(Cruiser2);
    PutVector.push_back(TorpedoBoat1);
    PutVector.push_back(TorpedoBoat2);
    PutVector.push_back(TorpedoBoat3);
    PutVector.push_back(Submarine1);
    PutVector.push_back(Submarine2);
    PutVector.push_back(Submarine3);
    PutVector.push_back(Submarine4);
}

void PlaceShips(Field& PutField, Field& Put2Field, vector <Ship>& vShips, int player)
{
    if(player == 1) {
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats kruiser (3 3 3) (1/2)\n";
	CreateShip(vShips.at(1), 3, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats kruiser (3 3 3) (2/2)\n";
	CreateShip(vShips.at(2), 3, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats torpedoboot (2 2) (1/3)\n";
	CreateShip(vShips.at(3), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats torpedoboot (2 2) (2/3)\n";
	CreateShip(vShips.at(4), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats torpedoboot (2 2) (3/3)\n";
	CreateShip(vShips.at(5), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats onderzeeer (1) (1/4)\n";
	CreateShip(vShips.at(6), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 1, plaats onderzeeer (1) (4/4)\n";
	CreateShip(vShips.at(9), 1, PutField);
	DrawScreen(PutField, Put2Field);
    }
    else if(player == 2) {
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats kruiser (3 3 3) (1/2)\n";
	CreateShip(vShips.at(1), 3, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats kruiser (3 3 3) (2/2)\n";
	CreateShip(vShips.at(2), 3, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats torpedoboot (2 2) (1/3)\n";
	CreateShip(vShips.at(3), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats torpedoboot (2 2) (2/3)\n";
	CreateShip(vShips.at(4), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats torpedoboot (2 2) (3/3)\n";
	CreateShip(vShips.at(5), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats onderzeeer (1) (1/4)\n";
	CreateShip(vShips.at(6), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << "Speler 2, plaats onderzeeer (1) (4/4)\n";
	CreateShip(vShips.at(9), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
    }
}

void DrawShipsRemaining(vector <Ship>& vShips)
{
    cout << "\tDe volgende schepen volgen:\n\t";
    if(vShips.at(0).GetSize()==0)
	cout << "Slagschip: (4 4 4 4) ";
    if(vShips.at(2).GetSize()==0)
	cout << "Kruisers: (3 3 3) ";
    if(vShips.at(1).GetSize()==0)
	cout << "(3 3 3) ";
    if(vShips.at(5).GetSize()==0)
	cout << "Torpedoboten: (2 2) ";
    if(vShips.at(3).GetSize()==0)
	cout << "(2 2) ";
    if(vShips.at(4).GetSize()==0)
	cout << "(2 2) ";
    if(vShips.at(9).GetSize()==0)
	cout << "Onderzeeers: (1) ";
    if(vShips.at(6).GetSize()==0)
	cout << "(1) ";
    if(vShips.at(7).GetSize()==0)
	cout << "(1) ";
    if(vShips.at(8).GetSize()==0)
	cout << "(1)\n\n";
}

int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField)
{
    int x, y;
    char cX;
    int guess = 0; // Returns 1 when hit

    if(turn % 2 == 0) {
	cout << "Speler 1, geef een locatie (bijvoorbeeld 'c 6'): ";
	cin >> cX >> y;
    }
    if(turn % 2 != 0) {
	cout << "Speler 2, geef een locatie (bijvoorbeeld 'c 6'): ";
	cin >> cX >> y;
    }

    switch(cX) {
    case 'a':
	x = 0;
	break;
    case 'b':
	x = 1;
	break;
    case 'c':
	x = 2;
	break;
    case 'd':
	x = 3;
	break;
    case 'e':
	x = 4;
	break;
    case 'f':
	x = 5;
	break;
    case 'g':
	x = 6;
	break;
    case 'h':
	x = 7;
	break;
    case 'i':
	x = 8;
	break;
    case 'j':
	x = 9;
	break;
    default:
	break;
    }
    
    if(OtherPlayerField.GetContent(x,y) > 0 && OtherPlayerField.GetContent(x,y) < 5) {
	OtherPlayerHitField.SetLocation(x, y, OtherPlayerField.GetContent(x,y));
	guess = 1;
     }
    else {
	OtherPlayerHitField.SetLocation(x, y, 6); // 6 is miss
    }
    
    return guess;
}

int LocUpFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	   (TestField.GetContent(x,y-2)==0) && (TestField.GetContent(x,y-3)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	   (TestField.GetContent(x,y-2)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y)==0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocDownFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0) && 
	   (TestField.GetContent(x,y+2)==0) && (TestField.GetContent(x,y+3)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0) && 
	   (TestField.GetContent(x,y+2)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocLeftFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0) && 
	   (TestField.GetContent(x-2,y)==0) && (TestField.GetContent(x-3,y)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0) && 
	   (TestField.GetContent(x-2,y)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocRightFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0) && 
	   (TestField.GetContent(x+2,y)==0) && (TestField.GetContent(x+3,y)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0) && 
	   (TestField.GetContent(x+2,y)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}
