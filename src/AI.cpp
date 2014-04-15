#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../headers/AI.h"
using namespace std;

// AI guesses a location. If it finds a ship at the location, it will search in all directions for another piece
// of the ship. When it finds two or more pieces, it will search at both ends for another piece, until the whole
// ship is destroyed.
// @param turn Turn of the game
// @param OtherPlayerField The other player's field with the actual ships
// @param OtherPlayerHitField The other player's field which tracks the guesses
// @param playerName The player's name
// @param return Returns 1 if the guess is a hit
int AIGuess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName)
{
    int nGuess = 0;
    int x, y;
    
    // xAdj = adjacent x-location, yAdj = adjacent y-location
    int xAdj = -1, yAdj = -1, nDir;
    
    // Booleans for progress of the code
    bool TRY = true, ADJACENT = true, NDIROK = true, RANDNUM = true;

    // nContent = sign at the location (e.g. 0,1,2,3,4,6,7)
    // nContentNext0 = location at right position
    // nContentNext1 = location at down position
    // nContentNext2 = location at left position
    // nContentNext3 = location at up position
    int nContent, nContentNext0=1, nContentNext1=1, nContentNext2=1, nContentNext3=1, nGetContent;
    int nCheckShip, nCheckShip2;
    int nI = 0, nJ = 0;
      
    // Creates a random number generator
    srand(time(NULL));
    
    // Inside this loop, the location is checked for a piece of a ship and searches smart in directions
    while(ADJACENT) {
	while(nI < 10) {                               // nI and nJ makes the AI start each iteration in the next position
	    while(nJ < 10) {                           // to prevent it only trying one location.
		for(int i = 0; i < 10; ++i) {
		    for(int j = 0; j < 10; ++j) {
			if((i+nI)<10) {
			    i += nI;
			    if((j+nJ)<10) {
				j += nJ;
				nGetContent = OtherPlayerHitField.GetContent(i,j);
				// Test if location is a ship
				if((nGetContent > 1) && (nGetContent < 5) && xAdj<0) {
				    // Get the content of the locations around it (up,down,left,right)
				    if((i+1)<10) { nContentNext0 = OtherPlayerHitField.GetContent(i+1,j); }
				    if((j+1)<10) { nContentNext1 = OtherPlayerHitField.GetContent(i,j+1); }
				    if((i-1)>=0) { nContentNext2 = OtherPlayerHitField.GetContent(i-1,j); }
				    if((j-1)>=0) { nContentNext3 = OtherPlayerHitField.GetContent(i,j-1); }
				    
				    // Check if there is a location which hasn't been tried yet
				    if(((nContentNext0 == 0) || (nContentNext1 == 0) ||(nContentNext2 == 0) || (nContentNext3 == 0))) {
					// Check if the ship around this location is already finished (0=not finished yet)
					if(( CheckReady(OtherPlayerHitField,i,j,nGetContent) == 0 )) {
					    // If there aren't at least two parts of a ship adjacent to each other, try around this position
					    if((CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 0)) {
						xAdj = i; yAdj = j;
					    }
					    /* Check in which position the ship is positioned and guess smart
					       1  = 2 locations up
					       2  = 3 locations up
					       9  = 1 location up
					       3  = 2 locations down
					       4  = 3 locations down
					       10 = 1 location down
					       5  = 2 locations left
					       6  = 3 locations left
					       11 = 1 location left
					       7  = 2 locations right
					       8  = 3 locations right
					       12 = 1 location right */

					    // Up locations
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 1) {
						xAdj = i; yAdj = j-2;
						if(OtherPlayerField.GetContent(i,j-2)!=7) { OtherPlayerHitField.SetLocation(i,j-2,OtherPlayerField.GetContent(i,j-2)); }
						else OtherPlayerHitField.SetLocation(i,j-2,6);
						NDIROK=false; TRY=false; nGuess = 1; 
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 2) {
						xAdj = i; yAdj = j-3;
						if(OtherPlayerField.GetContent(i,j-3)!=7) { OtherPlayerHitField.SetLocation(i,j-3,OtherPlayerField.GetContent(i,j-3)); }
						else OtherPlayerHitField.SetLocation(i,j-3,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 9) {
						xAdj = i, yAdj = j-1;
						if(OtherPlayerField.GetContent(i,j-1)!=7) { OtherPlayerHitField.SetLocation(i,j-1,OtherPlayerField.GetContent(i,j-1)); }
						else OtherPlayerHitField.SetLocation(i,j-1,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    // Down locations
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 3) {
						xAdj = i; yAdj = j+2;
						if(OtherPlayerField.GetContent(i,j+2)!=7) { OtherPlayerHitField.SetLocation(i,j+2,OtherPlayerField.GetContent(i,j+2)); }
						else OtherPlayerHitField.SetLocation(i,j+2,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 4) {
						xAdj = i; yAdj = j+3;
						if(OtherPlayerField.GetContent(i,j+3)!=7) { OtherPlayerHitField.SetLocation(i,j+3,OtherPlayerField.GetContent(i,j+3)); }
						else OtherPlayerHitField.SetLocation(i,j+3,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 10) {
						xAdj = i, yAdj = j+1;
						if(OtherPlayerField.GetContent(i,j+1)!=7) { OtherPlayerHitField.SetLocation(i,j+1,OtherPlayerField.GetContent(i,j+1)); }
						else OtherPlayerHitField.SetLocation(i,j+1,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    // Left locations
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 5) {
						xAdj = i-2; yAdj = j;
						if(OtherPlayerField.GetContent(i-2,j)!=7) { OtherPlayerHitField.SetLocation(i-2,j,OtherPlayerField.GetContent(i-2,j)); }
						else OtherPlayerHitField.SetLocation(i-2,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 6) {
						xAdj = i-3; yAdj = j;
						if(OtherPlayerField.GetContent(i-3,j)!=7) { OtherPlayerHitField.SetLocation(i-3,j,OtherPlayerField.GetContent(i-3,j)); }
						else OtherPlayerHitField.SetLocation(i-3,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 11) {
						xAdj = i-1, yAdj = j;
						if(OtherPlayerField.GetContent(i-1,j)!=7) { OtherPlayerHitField.SetLocation(i-1,j,OtherPlayerField.GetContent(i-1,j)); }
						else OtherPlayerHitField.SetLocation(i-1,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    // Right locations
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 7) {
						xAdj = i+2; yAdj = j;
						if(OtherPlayerField.GetContent(i+2,j)!=7) { OtherPlayerHitField.SetLocation(i+2,j,OtherPlayerField.GetContent(i+2,j)); }
						else OtherPlayerHitField.SetLocation(i+2,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 8) {
						xAdj = i+3; yAdj = j;
						if(OtherPlayerField.GetContent(i+3,j)!=7) { OtherPlayerHitField.SetLocation(i+3,j,OtherPlayerField.GetContent(i+3,j)); }
						else OtherPlayerHitField.SetLocation(i+3,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					    else if(CheckRow(nGetContent,i,j,OtherPlayerHitField) == 12) {
						xAdj = i+1, yAdj = j;
						if(OtherPlayerField.GetContent(i+1,j)!=7) { OtherPlayerHitField.SetLocation(i+1,j,OtherPlayerField.GetContent(i+1,j)); }
						else OtherPlayerHitField.SetLocation(i+1,j,6);
						NDIROK=false; TRY=false; nGuess = 1;
					    }
					}
				    }
				}
			    }
			}
		    }
		}
		
		// Continue when a ship is found at the location, but no adjacent parts are found
		if(xAdj>=0 && yAdj>=0) {
		    int count[4] = {0, 0, 0, 0};
		    // Keep guessing until are directions are tried
		    while(NDIROK) {
			// When at least one direction isn't searched for a free spot
			if((count[0] == 0) || (count[1] == 0) || (count[2] == 0) || (count[3] == 0)) {
			    nDir = rand() % 4; // Choose a random location
			    // 0 = up, 1 = down, 2 = left, 3 = right
			    if((nDir==0 && yAdj>=0) || (nDir==1 && yAdj<=9) || (nDir==2 && xAdj>=0) || (nDir==3 && xAdj<=9)) {
				switch(nDir) {
				case 0:
				    if((yAdj-1)>=0) { nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj-1); }
				    else { nCheckShip = 1; }
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj-1);
				    // If the location on the hitfield is free
				    if(nCheckShip==0) {
					if((yAdj-1)>=0) { // Test if location is valid
					    // If it isn't a 7 in the playing field (a buffer around a ship), use the value in the hitfield
					    if(nCheckShip2!=7)OtherPlayerHitField.SetLocation(xAdj,yAdj-1,OtherPlayerField.GetContent(xAdj,yAdj-1));
					    // It it is a 7, display it as a miss on the hitfield
					    else { OtherPlayerHitField.SetLocation(xAdj,yAdj-1,6); }
					    TRY = false; NDIROK = false; ADJACENT = false; // Exit al loops
					    if((nCheckShip>=1) && (nCheckShip<5)) { nGuess = 1; } // Return 1 if it's a hit
					}
				    }
				    count[0] = 1; // Mark the upper direction as tried
				    break;
				case 1: // As above
				    if((yAdj+1)<10) nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj+1);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj+1);
				    if(nCheckShip==0) {
					if((yAdj+1)<10) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj,yAdj+1,OtherPlayerField.GetContent(xAdj,yAdj+1));
					    else { OtherPlayerHitField.SetLocation(xAdj,yAdj+1,6); }
					    TRY = false; NDIROK = false; ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) { nGuess = 1; }
					}
				    }
				    count[1] = 1;
				    break;
				case 2: // ...
				    if((xAdj-1)>=0) nCheckShip = OtherPlayerHitField.GetContent(xAdj-1,yAdj);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj-1,yAdj);
				    if(nCheckShip==0) {
					if((xAdj-1)>=0) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj-1,yAdj,OtherPlayerField.GetContent(xAdj-1,yAdj));
					    else { OtherPlayerHitField.SetLocation(xAdj-1,yAdj,6); }
					    TRY = false; NDIROK = false; ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) { nGuess = 1; }
					}
				    }
				    count[2] = 1;
				    break;
				case 3: // ...
				    if((xAdj+1)<10) nCheckShip = OtherPlayerHitField.GetContent(xAdj+1,yAdj);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj+1,yAdj);
				    if(nCheckShip==0) {
					if((xAdj+1)<10) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj+1,yAdj,OtherPlayerField.GetContent(xAdj+1,yAdj));
					    else { OtherPlayerHitField.SetLocation(xAdj+1,yAdj,6); }
					    TRY = false; NDIROK = false; ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) { nGuess = 1; }
					}
				    }
				    count[3] = 1;
				    break;
				default:
				    break;
				}
			    }
			}
			else { NDIROK = false; }
		    }
		}
		++nJ;
	    }
	    ++nI;
	    nJ = 0;
	} 
	if(nI==10) ADJACENT = false; // When all iterations are run, stop thinking smart and move on to the random location guessing
    }
    
    while(TRY) {
	while(RANDNUM) {
	    // Choose a random location (x,y)
	    x = rand() % 10;
	    y = rand() % 10;
	    
	    if(OtherPlayerHitField.GetContent(x,y) == 0) { // If this location hasn't been guessed before
		RANDNUM = false;
	    }
	}

	// Check if location has a ship (return nGuess=1, a hit) or is a miss (all other cases)
	nContent = OtherPlayerField.GetContent(x,y);
	if(nContent > 0 && nContent < 5) {
	    OtherPlayerHitField.SetLocation(x, y, nContent);
	    nGuess = 1;
	    TRY = false;
	}
	else {
	    OtherPlayerHitField.SetLocation(x, y, 6); // 6 is miss
	    TRY = false;
	}
    }
    
    return nGuess;
}

// AI places it's ships on the playing field
// @param PutField Field to put the ships on (usually the playing field)
// @param vShips All ships of the AI in a vector
void AIPlaceShips(Field& PutField, vector <Ship>& vShips)
{
    AICreateShip(vShips.at(0), 4, PutField);
    AICreateShip(vShips.at(1), 3, PutField);
    AICreateShip(vShips.at(2), 3, PutField);    
    AICreateShip(vShips.at(3), 2, PutField);
    AICreateShip(vShips.at(4), 2, PutField);
    AICreateShip(vShips.at(5), 2, PutField);
    AICreateShip(vShips.at(6), 1, PutField);
    AICreateShip(vShips.at(7), 1, PutField);
    AICreateShip(vShips.at(8), 1, PutField);
    AICreateShip(vShips.at(9), 1, PutField);
}

// Creation of a ship and place it onto the field
// @param AIShip Ship to create and place
// @param size Size of the ship
// @param PutField Field to put the ship on
void AICreateShip(Ship& AIShip, int size, Field& PutField)
{
    int x, y; // Coordinates
    char cDirection; // Char with direction (b,o,l,r)
    int nUp = 0, nDown = 0, nLeft = 0, nRight = 0;
    int nRandomDir, nRandomLocX, nRandomLocY;
    bool LOCOK = true;
    bool DIROK = true;    
    bool DONE = true;

    srand(time(NULL));
    
    while(DONE) {
	while(LOCOK) {
	    nRandomLocX = rand() % 10;
	    nRandomLocY = rand() % 10;

	    // If there's nothing at this location, move on
	    if(PutField.GetContent(nRandomLocX, nRandomLocY) == 0) {
		LOCOK = false;
	    }
	    else {};
	}

	x = nRandomLocX;
	y = nRandomLocY;

	while(DIROK){
	    nRandomDir = rand() % 4;
	    
	    // Ship 1 has no direction, so can be skipped
	    // Test a random direction if the ship can be placed
	    if(size > 1 && size < 5) {
		switch(nRandomDir) {
		case 0:
		    nUp = LocUpFree(x,y,size,PutField); // returns 1 if free
		    break;
		case 1:
		    nDown = LocDownFree(x,y,size,PutField);
		    break;
		case 2:
		    nLeft = LocLeftFree(x,y,size,PutField);
		    break;
		case 3:
		    nRight = LocRightFree(x,y,size,PutField);
		    break;
		default:
		    break;
		}

		if((nUp == 1) || (nDown == 1) || (nLeft == 1) || (nRight == 1)) {
		    if(nUp == 1) cDirection = 'b';
		    else if(nDown == 1) cDirection = 'o';
		    else if(nLeft == 1) cDirection = 'l';
		    else if(nRight == 1) cDirection = 'r';
		    DIROK = false;
		}
	    }
	    else if(size == 1) { // Placement of the '1' ships
		nUp = LocUpFree(x,y,size,PutField); // returns 1 if free
		nDown = LocDownFree(x,y,size,PutField);
		nLeft = LocLeftFree(x,y,size,PutField);
		nRight = LocRightFree(x,y,size,PutField);
		DIROK = false;

		if(((nUp == 1) || (nDown == 1) || (nLeft == 1) || (nRight == 1)) && DIROK == false) {
		    cDirection = 'r';
		}
	    }
	}
	
	if(LOCOK == false && DIROK == false) {
	    DONE = false;
	}
    }
    
    // Place the ship at the location and the chosen direction
    AIShip.SetX(x); // x
    AIShip.SetY(y); // y
    AIShip.SetDirection(cDirection); // direction
    AIShip.SetSize(size); // size and name (e.g. 1, 22, 333, 4444)

    // Add '7' around the ship as a buffer, so a new ship can't be placed adjacent to it
    switch(cDirection) {
    case 'b':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x,y-i,size);
	    if((x-1)>=0) PutField.SetLocation(x-1,y-i,7);
	    if((x+1)<10) PutField.SetLocation(x+1,y-i,7);
	}
	if((y+1)<10) PutField.SetLocation(x,y+1,7);
	if(((y+1)<10) && ((x-1)>=0)) PutField.SetLocation(x-1,y+1,7);
	if(((y+1)<10) && ((x+1)<10)) PutField.SetLocation(x+1,y+1,7);
	if((y-size)>=0) PutField.SetLocation(x,y-size,7);
	if(((x-1)>=0) && ((y-size)>=0)) PutField.SetLocation(x-1,y-size,7);
	if(((x+1)<10) && ((y-size)>=0)) PutField.SetLocation(x+1,y-size,7);
	break;
    case 'o':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x,y+i,size);
	    if((x-1)>=0) PutField.SetLocation(x-1,y+i,7);
	    if((x+1)<10) PutField.SetLocation(x+1,y+i,7);
	}
	if((y-1)>=0) PutField.SetLocation(x,y-1,7);
	if(((y-1)>=0) && ((x-1)>=0)) PutField.SetLocation(x-1,y-1,7);
	if(((y-1)>=0) && ((x+1)<10)) PutField.SetLocation(x+1,y-1,7);
	if((y+size)<10) PutField.SetLocation(x,y+size,7);
	if(((y+size)<10) && ((x-1)>=0)) PutField.SetLocation(x-1,y+size,7);
	if(((y+size)<10) && ((x+1)<10)) PutField.SetLocation(x+1,y+size,7);
	break;
    case 'l':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x-i,y,size);
	    if((y-1)>=0) PutField.SetLocation(x-i,y-1,7);
	    if((y+1)<10) PutField.SetLocation(x-i,y+1,7);
	}
	if((x+1)<10) PutField.SetLocation(x+1,y,7);
	if(((x+1)<10) && ((y-1)>=0)) PutField.SetLocation(x+1,y-1,7);
	if(((x+1)<10) && ((y+1)<10)) PutField.SetLocation(x+1,y+1,7);
	if((x-size)>=0) PutField.SetLocation(x-size,y,7);
	if(((x-size)>=0) && ((y-1)>=0)) PutField.SetLocation(x-size,y-1,7);
	if(((x-size)>=0) && ((y+1)<10)) PutField.SetLocation(x-size,y+1,7);
	break;
    case 'r':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x+i,y,size);
	    if((y-1)>=0) PutField.SetLocation(x+i,y-1,7);
	    if((y+1)<10) PutField.SetLocation(x+i,y+1,7);
	}
	if((x-1)>=0) PutField.SetLocation(x-1,y,7);
	if(((x-1)>=0) && ((y-1)>=0)) PutField.SetLocation(x-1,y-1,7);
	if(((x-1)>=0) && ((y+1)<10)) PutField.SetLocation(x-1,y+1,7);
	if((x+size)<10) PutField.SetLocation(x+size,y,7);
	if(((x+size)<10) && ((y-1)>=0)) PutField.SetLocation(x+size,y-1,7);
	if(((x+size)<10) && ((y+1)<10)) PutField.SetLocation(x+size,y+1,7);
	break;
    }
}

// Check if the ship using this location is already destroyed
// @param OtherPlayerHitField Field to check on
// @param x, y Coordinates
// @param size Size and name of the ship
// @param return Returns 1 if ship is destroyed, 0 if not
int CheckReady(Field& OtherPlayerHitField, int x, int y, int size)
{
    int nReady = 0;
    int i = x;
    int j = y;

    // Test ship '4444'
    if(size==4) {
	if((OtherPlayerHitField.GetContent(i+1,j)==size) && (OtherPlayerHitField.GetContent(i+2,j)==size) &&
	   (OtherPlayerHitField.GetContent(i+3,j)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-1,j)==size) && (OtherPlayerHitField.GetContent(i+1,j)==size) &&
	   (OtherPlayerHitField.GetContent(i+2,j)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-2,j)==size) && (OtherPlayerHitField.GetContent(i-1,j)==size) &&
	   (OtherPlayerHitField.GetContent(i+1,j)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-3,j)==size) && (OtherPlayerHitField.GetContent(i-2,j)==size) &&
	   (OtherPlayerHitField.GetContent(i-1,j)==size)) { nReady = 1; }
	
	else if((OtherPlayerHitField.GetContent(i,j+1)==size) && (OtherPlayerHitField.GetContent(i,j+2)==size) &&
	   (OtherPlayerHitField.GetContent(i,j+3)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-1)==size) && (OtherPlayerHitField.GetContent(i,j+1)==size) &&
	   (OtherPlayerHitField.GetContent(i,j+2)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-2)==size) && (OtherPlayerHitField.GetContent(i,j-1)==size) &&
	   (OtherPlayerHitField.GetContent(i,j+1)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-3)==size) && (OtherPlayerHitField.GetContent(i,j-2)==size) &&
	   (OtherPlayerHitField.GetContent(i,j-1)==size)) { nReady = 1; }
    }
    // Test ship '333'
    else if(size==3) {
	if((OtherPlayerHitField.GetContent(i+1,j)==size) && (OtherPlayerHitField.GetContent(i+2,j)==size)) {
	    nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-1,j)==size) && (OtherPlayerHitField.GetContent(i+1,j)==size)) {
	    nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-2,j)==size) && (OtherPlayerHitField.GetContent(i-1,j)==size)) {
	    nReady = 1; }

	else if((OtherPlayerHitField.GetContent(i,j+1)==size) && (OtherPlayerHitField.GetContent(i,j+2)==size)) {
	    nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-1)==size) && (OtherPlayerHitField.GetContent(i,j+1)==size)) {
	    nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-2)==size) && (OtherPlayerHitField.GetContent(i,j-1)==size)) {
	    nReady = 1; }
    }
    // Test ship '22'
    else if(size==2) {
	if((OtherPlayerHitField.GetContent(i+1,j)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-1,j)==size)) { nReady = 1; }

	else if((OtherPlayerHitField.GetContent(i,j+1)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-1)==size)) { nReady = 1; }
    }
    
    // '1' is not checked, because it's already destroyed with one hit

    return nReady;
}

// Check to see if there are already 2 or 3 parts of a ship are adjacent to each other
// If there are for example 2 parts of a '3' ship horizontal next to each other, the last part must be to the left or right of it.
// When the boundaries are found, the other side is chosen. If the checked location and the location right to it are both '3', the
// function will return the right position (x + 2) to make a guess.
// @param size Size and name of the ship
// @param x, y Coordinates
// @param OtherPlayerHitField Field where the guesses are found
// @param return Returns an int which represents the location to make the guess at
// 1  = 2 locations up
// 2  = 3 locations up
// 9  = 1 location up
// 3  = 2 locations down
// 4  = 3 locations down
// 10 = 1 location down
// 5  = 2 locations left
// 6  = 3 locations left
// 11 = 1 location left
// 7  = 2 locations right
// 8  = 3 locations right
// 12 = 1 location right
int CheckRow(int size, int x, int y, Field& OtherPlayerHitField)
{
    int nCheck = 0;
    int nUp = OtherPlayerHitField.GetContent(x,y-1);
    int nUp2 = OtherPlayerHitField.GetContent(x,y-2);
    int nUp3 = OtherPlayerHitField.GetContent(x,y-3);
    int nDown = OtherPlayerHitField.GetContent(x,y+1);
    int nDown2 = OtherPlayerHitField.GetContent(x,y+2);
    int nDown3 = OtherPlayerHitField.GetContent(x,y+3);
    int nLeft = OtherPlayerHitField.GetContent(x-1,y);
    int nLeft2 = OtherPlayerHitField.GetContent(x-2,y);
    int nLeft3 = OtherPlayerHitField.GetContent(x-3,y);
    int nRight = OtherPlayerHitField.GetContent(x+1,y);
    int nRight2 = OtherPlayerHitField.GetContent(x+2,y);
    int nRight3 = OtherPlayerHitField.GetContent(x+3,y);
	
    // If size of ship is 4, find it's direction
    if(size==4) {
	if(nUp==4) {
	    if(((y-2)>=0) && nUp2==0) { nCheck = 1; }
	    else if(nDown==0) nCheck = 10;
	}
	else if((nUp==4) && (nUp2==4)) {
	    if(((y-3)>=0) && nUp3==0) { nCheck = 2; }
	    else if(nDown==0) nCheck = 10;
	}
	else if(nDown==4) {
	    if(((y+2)<10) && nDown2==0) { nCheck = 3; }
	    else if(nUp==0) nCheck = 9;
	}
	else if((nDown==4) && (nDown2==4)) {
	    if(((y+3)<10) && nDown3==0) { nCheck = 4; }
	    else if(nUp==0) nCheck = 9;
	}
	else if(nLeft==4) {
	    if(((x-2)>=0) && nLeft2==0) { nCheck = 5; }
	    else if(nRight==0) nCheck = 12;
	}
	else if((nLeft==4) && (nLeft2==4)) {
	    if(((x-3)>=0) && nLeft3==0) { nCheck = 6; }
	    else if(nRight==0) nCheck = 12;
	}
	else if(nRight==4) {
	    if(((x+2)<10) && nRight2==0) { nCheck = 7; }
	    else if(nLeft==0) nCheck = 11;
	}
	else if((nRight==4) && (nRight2==4)) {
	    if(((x+3)<10) && nRight3==0) { nCheck = 8;}
	    else if(nLeft==0) nCheck = 11;
	}
    }
    // If size of ship is 3, find it's direction
    else if(size==3) {
	if(nUp==3) {
	    if(((y-2)>=0) && nUp2==0) { nCheck = 1; }
	    else if(nDown==0) nCheck = 10;
	}
	else if(nDown==3) {
	    if(((y+2)<10) && nDown2==0) { nCheck = 3; }
	    else if(nUp==0) nCheck = 9;
	}
	else if(nLeft==3) {
	    if(((x-2)>=0) && nLeft2==0) { nCheck = 5; }
	    else if(nRight==0) nCheck = 12;
	}
	else if(nRight==3) {
	    if(((x+2)<10) && nRight2==0) { nCheck = 7; }
	    else if(nLeft==0) nCheck = 11;
	}
    }
    // If size of ship is 2 do nothing, just try for locations around x and y
    else if(size==2) { }
    // If size of ship is 1 do nothing, ship is destroyed
    else if(size==1) { }

    return nCheck;
}
