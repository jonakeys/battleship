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
    int xAdj = -1, yAdj = -1, nDir;
    int nUp, nDown, nLeft, nRight;
    bool TRY = true, ADJACENT = true, NDIROK = true, RANDNUM = true;
    
    srand(time(NULL));
    
    while(ADJACENT) {
	for(int i = 0; i < 10; ++i) {
	    for(int j = 0; j < 10; ++j) {
		if(OtherPlayerHitField.GetContent(i,j)>=1 && OtherPlayerHitField.GetContent(i,j)<=4 
		   && xAdj==-1 && yAdj==-1) {
		    xAdj = i;
		    xAdj = j;
		}
	    }
	}

	nUp = yAdj-1;
	nDown = yAdj+1;
	nLeft = xAdj-1;
	nRight = xAdj+1;
       	if(xAdj!=-1 && yAdj!=-1) {
	    while(NDIROK) {
		srand(time(NULL));
		nDir = rand() % 4;
		if((nDir==0 && yAdj>0) || (nDir==1 && yAdj<9) || (nDir==2 && xAdj>0) || (nDir==3 && xAdj<9)) {
		    switch(nDir) {
		    case 0:
			if(yAdj>0) {
			    if(OtherPlayerHitField.GetContent(xAdj,yAdj-1)==0) {
				OtherPlayerHitField.SetLocation(xAdj,yAdj-1,OtherPlayerField.GetContent(xAdj,yAdj-1));
				TRY = false;
				NDIROK = false;
				ADJACENT = false;
			    }
			}
			break;
		    case 1:
			if(yAdj<9) {
			    if(OtherPlayerHitField.GetContent(xAdj,yAdj+1)==0) {
				OtherPlayerHitField.SetLocation(xAdj,yAdj+1,OtherPlayerField.GetContent(xAdj,yAdj+1));
				TRY = false;
				NDIROK = false;
				ADJACENT = false;
			    }
			}
			break;
		    case 2:
			if(xAdj>0) {
			    if(OtherPlayerHitField.GetContent(xAdj-1,yAdj)==0) {
				OtherPlayerHitField.SetLocation(xAdj-1,yAdj,OtherPlayerField.GetContent(xAdj-1,yAdj));
				TRY = false;
				NDIROK = false;
				ADJACENT = false;
			    }
			}
			break;
		    case 3:
			if(xAdj<9) {
			    if(OtherPlayerHitField.GetContent(xAdj+1,yAdj)==0) {
				OtherPlayerHitField.SetLocation(xAdj+1,yAdj,OtherPlayerField.GetContent(xAdj+1,yAdj));
				TRY = false;
				NDIROK = false;
				ADJACENT = false;
			    }
			}
			break;
		    default:
			break;
		    }
		}
		else { ADJACENT = false; NDIROK = false;}
	    }
	}
	else if(xAdj==-1 && yAdj==-1) {
	    NDIROK = false;
	    ADJACENT = false;
	}
    }
    
    while(TRY) {
	while(RANDNUM) {
	    x = rand() % 10;
	    y = rand() % 10;
	    
	    if(OtherPlayerHitField.GetContent(x,y) == 0) {
		RANDNUM = false;
	    }
	}
	
	if(OtherPlayerField.GetContent(x,y) > 0 && OtherPlayerField.GetContent(x,y) < 5) {
	    OtherPlayerHitField.SetLocation(x, y, OtherPlayerField.GetContent(x,y));
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
