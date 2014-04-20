#include <fstream>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string>
#include <vector>
#include "../headers/Field.h"
#include "../headers/Ship.h"
#include "../headers/Draw.h"
#include "../headers/AI.h"
using namespace std;

void PlaceShips(Field& PutField, Field& Put2Field, Field& RemainField, vector <Ship>& vShips, int player, string playerName,
		string& player1, string& player2);
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName, Field& OtherPlayerRemainField);

int main()
{
    Field P1Field, P2Field; // Player fields
    Field P1HitField, P2HitField; // Fields to keep track of hits or misses
    Field P1RemainField, P2RemainField;
    bool PLAY = true, GO = true, DONE = false;
    int nTurn = 0, nTurn1 = 0, nTurn2 = 0, P1Counter = 20, P2Counter = 20; // nTurn counts turns, Counters deduct points from 20; if 0 all ships are destroyed
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

    statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
    statsFile << "---- BEGIN LOGBESTAND ----\n";
    statsFile.close();
    
    while(GO)
    {
	DONE = false;
	DrawTitle();
	cout << "ZEESLAG\n\n"
	     << "Zeeslag is een spel waarbij je strijdt om de macht op de zee. Het doel\n"
	     << "is om de schepen van je tegenstander te vinden en tot zinken te brengen.\n"
	     << "Het spel begint met het plaatsen van de schepen op het speelveld. Daarna\n"
	     << "mag je om de beurt een schot afvuren. Als je raakt, zie je het nummer\n"
	     << "van het schip. Als je mist, zie je een 'm'. De schepen mogen alleen\n"
	     << "horizontaal en verticaal geplaatst worden. Ook mogen ze elkaar niet raken.\n\n"
	     << "Veel plezier gewenst!\n- Jonathan\n\n"
	     << "HOOFDMENU\n"
	     << "1) Speler tegen speler\n"
	     << "2) Speler tegen computer\n"
	     << "3) Stoppen\n";
	    while(!DONE) {
		cout << "\nMaak je keuze (1-3): ";
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

	    // Create the fields for both players, their hitfields and remainfields
	    P1Field.Create();
	    P2Field.Create();
	    P1HitField.Create();
	    P2HitField.Create();
	    P1RemainField.Create();
	    P2RemainField.Create();

	    // Print the fields to the screen
	    // Players setup their ships on the field
	    DrawScreen(P1Field, P2Field, player1, player2);
	    PlaceShips(P1Field, P2Field, P1RemainField, vP1Ships, 1, player1, player1, player2);
	    DrawScreen(P1HitField, P2Field, player1, player2);
	    if(nChoice == 1) {
		PlaceShips(P1HitField, P2Field, P2RemainField, vP2Ships, 2, player2, player1, player2);
	    }
	    else if(nChoice == 2) {
		AIPlaceShips(P2Field, vP2Ships, P2RemainField);
	    }
	    DrawScreen(P2HitField, P1HitField, player1, player2);
	    cout << endl << endl;

	    while(PLAY)
	    {
		// Player 1 turn
		if(nTurn % 2 == 0) {
		    nGuess = Guess(nTurn, P2Field, P2HitField, player1, P2RemainField); // Guess returns 1 if hit
		    P1Counter -= nGuess;
		    DrawScreen(P2HitField, P1HitField, player1, player2);
		    DrawRemainingShips(P2RemainField, P1RemainField, player1, player2);
		    if(nGuess==1)
			cout << player1 << " schoot raak :-)\n\n";
		    else
			cout << player1 << " schoot mis :-(\n\n";
		    ++nTurn1;
		}
		// Player 2 turn
		if(nTurn % 2 != 0) {
		    if(nChoice == 1) {
			nGuess = Guess(nTurn, P1Field, P1HitField, player2, P1RemainField); // Guess returns 1 if hit
		    }
		    else if(nChoice == 2) {
			nGuess = AIGuess(nTurn, P1Field, P1HitField, player2, P1RemainField);
		    }
		    P2Counter -= nGuess;
		    DrawScreen(P2HitField, P1HitField, player1, player2);
		    DrawRemainingShips(P2RemainField, P1RemainField, player1, player2);
		    if(nGuess==1)
			cout << player2 << " schoot raak :-)\n\n";
		    else
			cout << player2 << " schoot mis :-(\n\n";
		    ++nTurn2;
		}
		if(P1Counter == 0 || P2Counter == 0) { // When one counter reaches zero, the game is won
		    PLAY = false;
		}
		++nTurn;
	    }
    
	    if(P1Counter == 0) {
		cout << player1 << " heeft gewonnen!\n";
		cout << "Je hebt er " << nTurn1 << " beurten over gedaan.\n\n";
		statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
		statsFile << player1 << " heeft gewonnen!\n"
			  << "De tegenstander was: " << player2 << ".\n"
			  << player1 << " heeft er " << nTurn1 << " beurten over gedaan.\n"
			  << player2 << " had nog " << P2Counter << " te raden.\n\n";
		statsFile.close();
	    }
	    else if(P2Counter == 0) {
		cout << player2 << " heeft gewonnen!\n";
		cout << "Je hebt er " << nTurn2 << " beurten over gedaan.\n\n";
		statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
		statsFile << player2 << " heeft gewonnen!\n"
			  << "De tegenstander was: " << player1 << ".\n"
			  << player2 << " heeft er " << nTurn2 << " beurten over gedaan.\n"
			  << player1 << " had nog " << P1Counter << " te raden.\n\n";		
		statsFile.close();
	    }
	    cin.ignore();
	}

	else if(nChoice == 3) {
	    statsFile.open("statsFile.txt", ios::out | ios::ate | ios::app);
	    statsFile << "Zeeslag is afgesloten.\n"
		      << "---- EINDE LOGBESTAND ----\n\n";
	    statsFile.close();
	    GO = false;
	}
    }

    cout << "Bedankt voor het spelen, tot ziens!" << endl;

    return 0;
}

// Player puts their ships on the field
void PlaceShips(Field& PutField, Field& Put2Field, Field& RemainField, vector <Ship>& vShips, int player, 
		string playerName, string& player1, string& player2)
{
    int nCount=1;

    if(player == 1) {
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (1/2)\n";
	++nCount;
	CreateShip(vShips.at(1), 3, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (2/2)\n";
	++nCount;
	CreateShip(vShips.at(2), 3, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (1/3)\n";
	++nCount;
	CreateShip(vShips.at(3), 2, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (2/3)\n";
	++nCount;
	CreateShip(vShips.at(4), 2, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (3/3)\n";
	++nCount;
	CreateShip(vShips.at(5), 2, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (1/4)\n";
	++nCount;
	CreateShip(vShips.at(6), 1, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (4/4)\n";
	CreateShip(vShips.at(9), 1, PutField, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
    }
    else if(player == 2) {
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats slagschip (4 4 4 4)\n";
	CreateShip(vShips.at(0), 4, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (1/2)\n";
	++nCount;
	CreateShip(vShips.at(1), 3, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats kruiser (3 3 3) (2/2)\n";
	++nCount;
	CreateShip(vShips.at(2), 3, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (1/3)\n";
	++nCount;
	CreateShip(vShips.at(3), 2, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (2/3)\n";
	++nCount;
	CreateShip(vShips.at(4), 2, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats torpedoboot (2 2) (3/3)\n";
	++nCount;
	CreateShip(vShips.at(5), 2, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (1/4)\n";
	++nCount;
	CreateShip(vShips.at(6), 1, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (2/4)\n";
	CreateShip(vShips.at(7), 1, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (3/4)\n";
	CreateShip(vShips.at(8), 1, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
	DrawShipsRemaining(vShips);
	cout << playerName << ", plaats onderzeeer (1) (4/4)\n";
	CreateShip(vShips.at(9), 1, Put2Field, RemainField, nCount);
	DrawScreen(PutField, Put2Field, player1, player2);
    }
}

// Guess a location
// @return Returns 1 if it's a hit, returns 0 if it's a miss
int Guess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName, Field& OtherPlayerRemainField)
{
    int x, y;
    char cX;
    int guess = 0; // Returns 1 when hit
    bool VALIDINPUT = true;

    while(VALIDINPUT) {
	if(turn % 2 == 0) {
	    cout << playerName << ", geef een locatie (bijvoorbeeld 'c6'): ";
	    cin >> cX >> y;
	}
	else if(turn % 2 != 0) {
	    cout << playerName << ", geef een locatie (bijvoorbeeld 'c6'): ";
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

	if(OtherPlayerHitField.GetContent(x,y)==0) {
	    VALIDINPUT = false;
	}
	else if(OtherPlayerHitField.GetContent(x,y)>0) {
	    cout << "De gekozen locatie is al bezet. Probeer het opnieuw.\n";
	}
    }
    
    if(OtherPlayerField.GetContent(x,y) > 0 && OtherPlayerField.GetContent(x,y) < 5) {
	OtherPlayerHitField.SetLocation(x, y, OtherPlayerField.GetContent(x,y));
	OtherPlayerRemainField.SetLocation(x,y,0);
	guess = 1;
    }
    else {
	OtherPlayerHitField.SetLocation(x, y, 6); // 6 is miss
    }
    
    return guess;
}
