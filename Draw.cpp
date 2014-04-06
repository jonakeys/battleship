#include <stdlib.h>
#include "Draw.h"
#include "Field.h"

#include <iostream>
using namespace std;

// Draw the screen
void DrawScreen(Field& Player1Field, Field& Player2Field)
{
    system("clear");
    DrawTitle();
    cout << "\t Speler 1\t\t\t\t\t       Speler 2\n"
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
