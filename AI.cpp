#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "AI.h"
using namespace std;

// Returns
// @param return Returns 1 if the guess is a hit
int AIGuess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName)
{
    int nGuess = 0;
    int x, y;
    bool TRY = true;
    
    srand(time(NULL));

    while(TRY) {
	x = rand() % 10;
	y = rand() % 10;
	
	if(OtherPlayerHitField.GetContent(x,y) == 0) {
	    TRY = false;
	}
    }

    if(OtherPlayerField.GetContent(x,y) > 0 && OtherPlayerField.GetContent(x,y) < 5) {
	OtherPlayerHitField.SetLocation(x, y, OtherPlayerField.GetContent(x,y));
	nGuess = 1;
    }
    else {
	OtherPlayerHitField.SetLocation(x, y, 6); // 6 is miss
    }
	
    return nGuess;
}

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

void AICreateShip(Ship& AIShip, int size, Field& PutField)
{
    int x, y;
    char cDirection;
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

	    if(PutField.GetContent(nRandomLocX, nRandomLocY) == 0) {
		LOCOK = false;
	    }
	    else {};
	}

	x = nRandomLocX;
	y = nRandomLocY;

	while(DIROK){
	    nRandomDir = rand() % 4;

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
	    else if(size == 1) {
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
    
    AIShip.SetX(x);
    AIShip.SetY(y);
    AIShip.SetDirection(cDirection);
    AIShip.SetSize(size);

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
