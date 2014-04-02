#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"
#include "Draw.h"
using namespace std;

void PlaceShips(Field& PutField, Field& Put2Field, vector <Ship>& vShips, int player, string playerName);
void DrawShipsRemaining(vector <Ship>& vShips);
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName);

int main()
{
    Field P1Field, P2Field;
    Field P1HitField, P2HitField;
    bool PLAY = true;
    int nTurn = 0, P1Counter = 20, P2Counter = 20;
    string player1, player2;
    
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
    
    cout << "Speler 1, typ je naam: ";
    cin >> player1;
    cout << "Speler 2, typ je naam: ";
    cin >> player2;

    P1Field.Create();
    P2Field.Create();
    P1HitField.Create();
    P2HitField.Create();

    DrawScreen(P1Field, P2Field);
    PlaceShips(P1Field, P2Field, vP1Ships, 1, player1);
    DrawScreen(P1HitField, P2Field);
    PlaceShips(P1HitField, P2Field, vP2Ships, 2, player2);
    DrawScreen(P2HitField, P1HitField);
    cout << endl << endl;

    while(PLAY)
    {
	if(nTurn % 2 == 0) {
	    int nGuess = Guess(nTurn, P2Field, P2HitField, player1);
	    P1Counter -= nGuess;
	    DrawScreen(P2HitField, P1HitField);
	    if(nGuess==1)
		cout << player1 << " schoot raak :-)\n\n";
	    else
		cout << player1 << " schoot mis :-(\n\n";
	}
	if(nTurn % 2 != 0) {
	    int nGuess = Guess(nTurn, P1Field, P1HitField, player2);
	    P2Counter -= nGuess;
	    DrawScreen(P2HitField, P1HitField);
	    if(nGuess==1)
		cout << player2 << " schoot raak :-)\n\n";
	    else
		cout << player2 << " schoot mis :-(\n\n";
	}
	if(P1Counter == 0 || P2Counter == 0) {
	    PLAY = false;
	}
	++nTurn;
    }
    
    if(P1Counter == 0) {
	cout << player1 << " heeft gewonnen!\n";
    }
    else if(P2Counter == 0) {
	cout << player2 << " heeft gewonnen!\n";
    }

    cout << "Je hebt er " << nTurn << " beurten over gedaan.\n" 
	 << "Bedankt voor het spelen, tot ziens!" << endl;

    return 0;
}

void PlaceShips(Field& PutField, Field& Put2Field, vector <Ship>& vShips, int player, string playerName)
{
    if(player == 1) {
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (1/2)\n";
	CreateShip(vShips.at(1), 3, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (2/2)\n";
	CreateShip(vShips.at(2), 3, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (1/3)\n";
	CreateShip(vShips.at(3), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (2/3)\n";
	CreateShip(vShips.at(4), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (3/3)\n";
	CreateShip(vShips.at(5), 2, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (1/4)\n";
	CreateShip(vShips.at(6), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, PutField);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (4/4)\n";
	CreateShip(vShips.at(9), 1, PutField);
	DrawScreen(PutField, Put2Field);
    }
    else if(player == 2) {
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (1/2)\n";
	CreateShip(vShips.at(1), 3, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (2/2)\n";
	CreateShip(vShips.at(2), 3, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (1/3)\n";
	CreateShip(vShips.at(3), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (2/3)\n";
	CreateShip(vShips.at(4), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (3/3)\n";
	CreateShip(vShips.at(5), 2, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (1/4)\n";
	CreateShip(vShips.at(6), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, Put2Field);
	DrawScreen(PutField, Put2Field);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (4/4)\n";
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

int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName)
{
    int x, y;
    char cX;
    int guess = 0; // Returns 1 when hit

    if(turn % 2 == 0) {
	cout << playerName << ", geef een locatie (bijvoorbeeld 'c 6'): ";
	cin >> cX >> y;
    }
    if(turn % 2 != 0) {
	cout << playerName << ", geef een locatie (bijvoorbeeld 'c 6'): ";
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
