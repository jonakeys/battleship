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
    bool TRY = true, ADJACENT = true, NDIROK = true, RANDNUM = true;
    int nContent, nContentNext0=0, nContentNext1=0, nContentNext2=0, nContentNext3=0;
    int nCheckShip, nCheckShip2;
    int nI = 0, nJ = 0;
      
    srand(time(NULL));
    
    while(ADJACENT) {
// Van hier
	while(nI < 10) {
	    while(nJ < 10) {
		for(int i = 0; i < 10; ++i) {
		    for(int j = 0; j < 10; ++j) {
//			if((i+nI)<10) {
			    i += nI;
//			    if((j+nJ)<10) {
				j += nJ;
				nContent = OtherPlayerHitField.GetContent(i,j);
				if((i+1)<9) nContentNext0 = OtherPlayerHitField.GetContent(i+1,j);
				if((j+1)<9) nContentNext1 = OtherPlayerHitField.GetContent(i,j+1);
				if((i-1)>0) nContentNext2 = OtherPlayerHitField.GetContent(i-1,j);
				if((j-1)>0) nContentNext3 = OtherPlayerHitField.GetContent(i,j-1);
				if((OtherPlayerHitField.GetContent(i,j) > 1) && (OtherPlayerHitField.GetContent(i,j) < 5)) {
//				    if((nContent != nContentNext0) || (nContent != nContentNext1)
//				       ||(nContent != nContentNext2) || (nContent != nContentNext3)) {
					xAdj = i;
					yAdj = j;
//				    }
				}
//			    }
//			}
		    }
		}
		    
		
		if(xAdj>=0 && yAdj>=0) {
		    int count[4] = {0, 1, 2, 3};
		    while(NDIROK) {
			if((count[0] == 0) || (count[1] == 1) || (count[2] == 2) || (count[3] == 3)) {
			    nDir = rand() % 4;
			    switch(nDir) {
			    case 0:
				count[0] = 5;
				break;
			    case 1:
				count[1] = 5;
				break;
			    case 2:
				count[2] = 5;
				break;
			    case 3:
				count[3] = 5;
				break;
			    }
			    if((nDir==0 && yAdj>=0) || (nDir==1 && yAdj<10) || (nDir==2 && xAdj>=0) || (nDir==3 && xAdj<10)) {
				switch(nDir) {
				case 0:
				    nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj-1);
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj-1);
				    if(nCheckShip==0) {
					if(nCheckShip2!=7)OtherPlayerHitField.SetLocation(xAdj,yAdj-1,OtherPlayerField.GetContent(xAdj,yAdj-1));
					else { OtherPlayerHitField.SetLocation(xAdj,yAdj-1,6); }
					TRY = false;
					NDIROK = false;
					ADJACENT = false;
					if((nCheckShip>=1) && (nCheckShip<5)) {
					    nGuess = 1;
					}
				    }
				    break;
				case 1:
				    nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj+1);
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj+1);
				    if(nCheckShip==0) {
					if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj,yAdj+1,OtherPlayerField.GetContent(xAdj,yAdj+1));
					else { OtherPlayerHitField.SetLocation(xAdj,yAdj+1,6); }
					TRY = false;
					NDIROK = false;
					ADJACENT = false;
					if((nCheckShip>=1) && (nCheckShip<5)) {
					    nGuess = 1;
					}
				    }
				    break;
				case 2:
				    nCheckShip = OtherPlayerHitField.GetContent(xAdj-1,yAdj);
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj-1,yAdj);
				    if(nCheckShip==0) {
					if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj-1,yAdj,OtherPlayerField.GetContent(xAdj-1,yAdj));
					else { OtherPlayerHitField.SetLocation(xAdj-1,yAdj,6); }
					TRY = false;
					NDIROK = false;
					ADJACENT = false;
					if((nCheckShip>=1) && (nCheckShip<5)) {
					    nGuess = 1;
					}
				    }
				    break;
				case 3:
				    nCheckShip = OtherPlayerHitField.GetContent(xAdj+1,yAdj);
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj+1,yAdj);
				    if(nCheckShip==0) {
					if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj+1,yAdj,OtherPlayerField.GetContent(xAdj+1,yAdj));
					else { OtherPlayerHitField.SetLocation(xAdj+1,yAdj,6); }
					TRY = false;
					NDIROK = false;
					ADJACENT = false;
					if((nCheckShip>=1) && (nCheckShip<5)) {
					    nGuess = 1;
					}
				    }
				    break;
				default:
				    break;
				}
			    }
			}
			NDIROK = false;
		    }
		}
//		ADJACENT = false;
		++nJ;
	    }
	    ++nI;
	    nJ = 0;
	} 
	if(nI==10) ADJACENT = false;	
    }
    
// Tot hier
    
    while(TRY) {
	while(RANDNUM) {
	    x = rand() % 10;
	    y = rand() % 10;
	    
	    if(OtherPlayerHitField.GetContent(x,y) == 0) {
		RANDNUM = false;
	    }
	}
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
