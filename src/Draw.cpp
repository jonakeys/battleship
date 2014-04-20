#include <stdlib.h>
#include "../headers/Draw.h"
#include "../headers/Field.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Draw the screen
void DrawScreen(Field& Player1Field, Field& Player2Field, string& sPlayer1, string& sPlayer2)
{
    system("clear");
    DrawTitle();
    cout << "\t " << sPlayer1
	 << setw(90) << sPlayer2 << endl
	 << "\t ________________________________________\t       ________________________________________\n"
	 << "\t|\t\t\t\t         |\t      |\t\t\t\t\t       |" << endl
	 << "\t|      a  b  c  d  e  f  g  h  i  j      |\t      |      a  b  c  d  e  f  g  h  i  j      |" << endl 
	 << "\t|\t\t\t\t         |\t      |\t\t\t\t\t       |" << endl
	 << "\t|\t\t\t\t         |\t      |\t\t\t\t\t       |" << endl;

    for(int i=0; i<10; ++i){
	cout << "\t|  " << i << "   ";
	DrawField(Player1Field, i);
	cout <<  " " << i << "  |\t      |  " << i << "   ";
	DrawField(Player2Field, i);
	cout << " " << i << "  |" << endl 
	     <<"\t|\t\t\t\t         |\t      |\t\t\t\t\t       |" << endl;
    }
    cout << "\t|\t\t\t\t         |\t      |\t\t\t\t\t       |" << endl
	 << "\t|      a  b  c  d  e  f  g  h  i  j      |\t      |      a  b  c  d  e  f  g  h  i  j      |" << endl 
	 << "\t|________________________________________|\t      |________________________________________|\n\n" << endl;
}	
      
// Draw the title
void DrawTitle()
{
    cout << endl
	 << "\t\t\t       ____________ ______  _____ _               _____ " << endl
	 << "\t\t\t      |___  /  ____|  ____|/ ____| |        /\\   / ____|" << endl
	 << "\t\t\t         / /| |__  | |__  | (___ | |       /  \\ | |  __ " << endl
	 << "\t\t\t        / / |  __| |  __|  \\___ \\| |      / /\\ \\| | |_ |" << endl
	 << "\t\t\t       / /__| |____| |____ ____) | |____ / ____ \\ |__| |" << endl
	 << "\t\t\t      /_____|______|______|_____/|______/_/    \\_\\_____|"
	 << endl << endl << endl; 
}

// Draw the field, one row at a time
void DrawField(Field& DrawField, int row)
{
    DrawField.Draw(row);
}

void DrawRemainingShips(Field& RemainFieldP1, Field& RemainFieldP2, string& P1Name, string& P2Name)
{
    int nNumber;
    int nB=0, nC1=0, nC2=0, nT1=0, nT2=0, nT3=0, nS=0;

    cout << "Schepen te gaan:\n";

    for(int i = 0; i<10; ++i) {
	for(int j = 0; j<10; ++j) {
	    nNumber = RemainFieldP1.GetContent(i,j);
	    switch(nNumber) {
	    case 1:
		++nB;
		break;
	    case 2:
		++nC1;
		break;
	    case 3:
		++nC2;
		break;
	    case 4:
		++nT1;
		break;
	    case 5:
		++nT2;
		break;
	    case 6:
		++nT3;
		break;
	    case 7:
		++nS;
		break;
	    default:
		break;
	    }
	}
    }

    cout << P1Name << ": ";
    if(nB>0) cout << "(";
    for(int i = 0; i<nB; ++i) { cout << "4"; }
    if(nB>0) cout << ") ";
    if(nC1>0) cout << "(";
    for(int i = 0; i<nC1; ++i) { cout << "3"; }
    if(nC1>0) cout << ") ";
    if(nC2>0) cout << "(";
    for(int i = 0; i<nC2; ++i) { cout << "3"; }
    if(nC2>0) cout << ") ";
    if(nT1>0) cout << "(";
    for(int i = 0; i<nT1; ++i) { cout << "2"; }
    if(nT1>0) cout << ") ";
    if(nT2>0) cout << "(";
    for(int i = 0; i<nT2; ++i) { cout << "2"; }
    if(nT2>0) cout << ") ";
    if(nT3>0) cout << "(";
    for(int i = 0; i<nT3; ++i) { cout << "2"; }
    if(nT3>0) cout << ") ";
    for(int i = 0; i<nS; ++i) { cout << "(1) "; }
    cout << endl;

    nB = 0;
    nC1 = 0;
    nC2 = 0;
    nT1 = 0;
    nT2 = 0;
    nT3 = 0;
    nS = 0;
    for(int i = 0; i<10; ++i) {
	for(int j = 0; j<10; ++j) {
	    nNumber = RemainFieldP2.GetContent(i,j);
	    switch(nNumber) {
	    case 1:
		++nB;
		break;
	    case 2:
		++nC1;
		break;
	    case 3:
		++nC2;
		break;
	    case 4:
		++nT1;
		break;
	    case 5:
		++nT2;
		break;
	    case 6:
		++nT3;
		break;
	    case 7:
		++nS;
		break;
	    default:
		break;
	    }
	}
    }

    cout << P2Name << ": ";
    if(nB>0) cout << "(";
    for(int i = 0; i<nB; ++i) { cout << "4"; }
    if(nB>0) cout << ") ";
    if(nC1>0) cout << "(";
    for(int i = 0; i<nC1; ++i) { cout << "3"; }
    if(nC1>0) cout << ") ";
    if(nC2>0) cout << "(";
    for(int i = 0; i<nC2; ++i) { cout << "3"; }
    if(nC2>0) cout << ") ";
    if(nT1>0) cout << "(";
    for(int i = 0; i<nT1; ++i) { cout << "2"; }
    if(nT1>0) cout << ") ";
    if(nT2>0) cout << "(";
    for(int i = 0; i<nT2; ++i) { cout << "2"; }
    if(nT2>0) cout << ") ";
    if(nT3>0) cout << "(";
    for(int i = 0; i<nT3; ++i) { cout << "2"; }
    if(nT3>0) cout << ") ";
    for(int i = 0; i<nS; ++i) { cout << "(1) "; }
    cout << endl << endl;
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
