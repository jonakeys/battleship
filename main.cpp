#include <fstream>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Field.h"
#include "Ship.h"
#include "Draw.h"
#include "AI.h"
using namespace std;

void PlaceShips(Field& PutField, Field& Put2Field, vector <Ship>& vShips, int player, string playerName);
void DrawShipsRemaining(vector <Ship>& vShips);
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName);

int main()
{
    Field P1Field, P2Field; // Player fields
    Field P1HitField, P2HitField; // Fields to keep track of hits or misses
    bool PLAY = true, GO = true, DONE = false;
    int nTurn = 0, P1Counter = 20, P2Counter = 20; // nTurn counts turns, Counters deduct points from 20; if 0 all ships are destroyed
    string player1, player2;
    int nChoice, nGuess;
    ofstream statsFile;
    
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

    while(GO)
    {
	DONE = false;
	DrawTitle();
	cout << "ZEESLAG - HOOFDMENU\n\n"
	     << "Zeeslag is een spel waarbij je strijdt om de macht op de zee. Het is de bedoeling om de schepen \n"
	     << "van je tegenstander te vinden en tot zinken te brengen.\n"
	     << "Het spel begint met het plaatsen van de schepen op het speelveld. Daarna mag je om de beurt een \n"
	     << "schot afvuren. Als het raak is, zie je het nummer van het schip. Als het mis is zie je een 'M'.\n\n"
	     << "Bij het plaatsen mogen de schepen alleen horizontaal en verticaal geplaatst worden. Ook mogen ze \n"
	     << "elkaar niet raken.\n\n"
	     << "Veel plezier gewenst!\n- Jonathan\n\n"
	     << "1) Speler tegen speler\n"
	     << "2) Speler tegen computer\n"
	     << "3) Stoppen\n";
	    while(!DONE) {
		cout << "Maak je keuze (1-3): ";
		cin >> nChoice;
		if(0 < nChoice && nChoice < 4)
		    DONE = true;
		else
		    cout << "Ongeldige invoer. Probeer het opnieuw (1-3):\n";
	    }
    
	if(nChoice == 1 || nChoice == 2) {
	    // Let players enter their name
	    cout << "Speler 1, typ je naam: ";
	    cin >> player1;
	    if(nChoice == 1) {
		cout << "Speler 2, typ je naam: ";
		cin >> player2;
	    }
	    else if(nChoice == 2) {
		player2 = "Computer";
	    }

	    // Create the fields for both players and their accompanying hitfields
	    P1Field.Create();
	    P2Field.Create();
	    P1HitField.Create();
	    P2HitField.Create();

	    // Print the fields to the screen
	    // Players setup their ships on the field
	    DrawScreen(P1Field, P2Field);
	    PlaceShips(P1Field, P2Field, vP1Ships, 1, player1);
	    DrawScreen(P1HitField, P2Field);
	    if(nChoice == 1) {
		PlaceShips(P1HitField, P2Field, vP2Ships, 2, player2);
	    }
	    else if(nChoice == 2) {
		AIPlaceShips(P2Field, vP2Ships);
	    }
	    DrawScreen(P2HitField, P1HitField);
	    cout << endl << endl;

	    while(PLAY)
	    {
		// Player 1 turn
		if(nTurn % 2 == 0) {
		    nGuess = Guess(nTurn, P2Field, P2HitField, player1); // Guess returns 1 if hit
		    P1Counter -= nGuess;
		    DrawScreen(P2HitField, P1HitField);
		    if(nGuess==1)
			cout << player1 << " schoot raak :-)\n\n";
		    else
			cout << player1 << " schoot mis :-(\n\n";
		}
		// Player 2 turn
		if(nTurn % 2 != 0) {
		    if(nChoice == 1) {
			nGuess = Guess(nTurn, P1Field, P1HitField, player2); // Guess returns 1 if hit
		    }
		    else if(nChoice == 2) {
			nGuess = AIGuess(nTurn, P1Field, P1HitField, player2);
		    }
		    P2Counter -= nGuess;
		    DrawScreen(P2HitField, P1HitField);
		    if(nGuess==1)
			cout << player2 << " schoot raak :-)\n\n";
		    else
			cout << player2 << " schoot mis :-(\n\n";
		}
		if(P1Counter == 0 || P2Counter == 0) { // When one counter reaches zero, the game is won
		    PLAY = false;
		}
		++nTurn;
	    }
    
	    if(P1Counter == 0) {
		cout << player1 << " heeft gewonnen!\n";
		statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
		statsFile << player1 << " heeft gewonnen.\n"
			  << "De tegenstander was: " << player2 << ".\n"
			  << player1 << " heeft er " << nTurn << " beurten over gedaan.\n";
		statsFile.close();
	    }
	    else if(P2Counter == 0) {
		cout << player2 << " heeft gewonnen!\n";
		statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
		statsFile << player2 << " heeft gewonnen.\n"
			  << "De tegenstander was: " << player1 << ".\n"
			  << player2 << " heeft er " << nTurn << " beurten over gedaan.\n";
		statsFile.close();

	    }
	    cout << "Je hebt er " << nTurn << " beurten over gedaan.\n\n";
	    cin.ignore();
	}

	else if(nChoice == 2) {
	    cout << "Sorry, deze functie is nog niet geimplementeerd.\n";
	}
	
	else if(nChoice == 3) {
	    statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
	    statsFile << "Zeeslag is afgesloten.\n\n";
	    statsFile.close();
	    GO = false;
	}
    }

    cout << "Bedankt voor het spelen, tot ziens!" << endl;

    return 0;
}

// Player puts their ships on the field
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

// Draws a line with the remaining ships to place on the field
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
	cout << "(1)";
    cout << "\n\n";
}

// Guess a location
// @return Returns 1 if it's a hit, returns 0 if it's a miss
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName)
{
    int x, y;
    char cX;
    int guess = 0; // Returns 1 when hit
    bool VALIDINPUT = true;

    while(VALIDINPUT) {
	if(turn % 2 == 0) {
	    cout << playerName << ", geef een locatie (bijvoorbeeld 'c 6'): ";
	    cin >> cX >> y;
	}
	if(turn % 2 != 0) {
	    cout << playerName << ", geef een locatie (bijvoorbeeld 'c 6'): ";
	    cin >> cX >> y;
	}

	if(cX != 'a' && cX != 'b' && cX != 'c' && cX != 'd' && cX != 'e' &&
	   cX != 'f' && cX != 'g' && cX != 'h' && cX != 'i' && cX != 'j') {
	    cout << "Ongeldig x-coordinaat. Probeer het opnieuw (a-j).\n";
	    cin.ignore(10000,'\n');
	}
	else if(y < 0 || y > 9) {
	    cout << "Ongeldig y-coordinaat. Probeer het opnieuw (0-9).\n";
	    cin.ignore(10000,'\n');
	}
	else {
	    VALIDINPUT = false;
	}
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
