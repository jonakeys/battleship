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
	while(nI < 10) {
	    while(nJ < 10) {
		for(int i = 0; i < 10; ++i) {
		    for(int j = 0; j < 10; ++j) {
			if((i+nI)<10) {
			    i += nI;
			    if((j+nJ)<10) {
				j += nJ;
				if(((OtherPlayerHitField.GetContent(i,j) > 1) && (OtherPlayerHitField.GetContent(i,j) < 5)) ) {
				    if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 0) {
					nContent = OtherPlayerHitField.GetContent(i,j);
					if((i+1)<10) { nContentNext0 = OtherPlayerHitField.GetContent(i+1,j); }
					else nContentNext0 = OtherPlayerHitField.GetContent(i,j);
					if((j+1)<10) { nContentNext1 = OtherPlayerHitField.GetContent(i,j+1);  }
					else nContentNext1 = OtherPlayerHitField.GetContent(i,j);
					if((i-1)>=0) {nContentNext2 = OtherPlayerHitField.GetContent(i-1,j); }
					else nContentNext2 = OtherPlayerHitField.GetContent(i,j);
					if((j-1)>=0) {nContentNext3 = OtherPlayerHitField.GetContent(i,j-1); }
					else nContentNext3 = OtherPlayerHitField.GetContent(i,j);
					if( ( CheckReady(OtherPlayerHitField,i,j,OtherPlayerHitField.GetContent(i,j)) == 0 ) ) {
					    if( (nContentNext0 == 0) || (nContentNext1 == 0)
						||(nContentNext2 == 0) || (nContentNext3 == 0) ) {
						xAdj = i;
						yAdj = j;
					    }
					}
				    }
				    // Up
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 1) {
					xAdj = i;
					yAdj = j-2;
				    }
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 2) {
					xAdj = i;
					yAdj = j-3;
				    }
				    // Down
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 3) {
					xAdj = i;
					yAdj = j+2;
				    }
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 4) {
					xAdj = i;
					yAdj = j+3;
				    }
				    // Left
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 5) {
					xAdj = i-2;
					yAdj = j;
				    }
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 6) {
					xAdj = i-3;
					yAdj = j;
				    }
				    // Right
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 7) {
					xAdj = i+2;
					yAdj = j;
				    }
				    else if(CheckRow(OtherPlayerHitField.GetContent(i,j),i,j,OtherPlayerHitField) == 8) {
					xAdj = i+3;
					yAdj = j;
				    }
				}
			    }
			}
		    }
		}
		    
		if(xAdj>=0 && yAdj>=0) {
		    int count[4] = {0, 0, 0, 0};
		    while(NDIROK) {
			if((count[0] == 0) || (count[1] == 0) || (count[2] == 0) || (count[3] == 0)) {
			    nDir = rand() % 4;
			    if((nDir==0 && yAdj>=0) || (nDir==1 && yAdj<=9) || (nDir==2 && xAdj>=0) || (nDir==3 && xAdj<=9)) {
				switch(nDir) {
				case 0:
				    if((yAdj-1)>=0) { nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj-1); }
				    else { nCheckShip = 1; }
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj-1);
				    if(nCheckShip==0) {
					if((yAdj-1)>=0) {
					    if(nCheckShip2!=7)OtherPlayerHitField.SetLocation(xAdj,yAdj-1,OtherPlayerField.GetContent(xAdj,yAdj-1));
					    else { OtherPlayerHitField.SetLocation(xAdj,yAdj-1,6); }
					    TRY = false;
					    NDIROK = false;
					    ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) {
						nGuess = 1;
					    }
					}
				    }
				    count[0] = 1;
				    break;
				case 1:
				    if((yAdj+1)<10) nCheckShip = OtherPlayerHitField.GetContent(xAdj,yAdj+1);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj,yAdj+1);
				    if(nCheckShip==0) {
					if((yAdj+1)<10) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj,yAdj+1,OtherPlayerField.GetContent(xAdj,yAdj+1));
					    else { OtherPlayerHitField.SetLocation(xAdj,yAdj+1,6); }
					    TRY = false;
					    NDIROK = false;
					    ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) {
						nGuess = 1;
					    }
					}
				    }
				    count[1] = 1;
				    break;
				case 2:
				    if((xAdj-1)>=0) nCheckShip = OtherPlayerHitField.GetContent(xAdj-1,yAdj);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj-1,yAdj);
				    if(nCheckShip==0) {
					if((xAdj-1)>=0) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj-1,yAdj,OtherPlayerField.GetContent(xAdj-1,yAdj));
					    else { OtherPlayerHitField.SetLocation(xAdj-1,yAdj,6); }
					    TRY = false;
					    NDIROK = false;
					    ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) {
						nGuess = 1;
					    }
					}
				    }
				    count[2] = 1;
				    break;
				case 3:
				    if((xAdj+1)<10) nCheckShip = OtherPlayerHitField.GetContent(xAdj+1,yAdj);
				    else nCheckShip = 1;
				    nCheckShip2 = OtherPlayerField.GetContent(xAdj+1,yAdj);
				    if(nCheckShip==0) {
					if((xAdj+1)<10) {
					    if(nCheckShip2!=7) OtherPlayerHitField.SetLocation(xAdj+1,yAdj,OtherPlayerField.GetContent(xAdj+1,yAdj));
					    else { OtherPlayerHitField.SetLocation(xAdj+1,yAdj,6); }
					    TRY = false;
					    NDIROK = false;
					    ADJACENT = false;
					    if((nCheckShip>=1) && (nCheckShip<5)) {
						nGuess = 1;
					    }
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
	if(nI==10) ADJACENT = false;
    }

    
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

int CheckReady(Field& OtherPlayerHitField, int x, int y, int size)
{
    int nReady = 0;
    int i = x;
    int j = y;

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
    else if(size==2) {
	if((OtherPlayerHitField.GetContent(i+1,j)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i-1,j)==size)) { nReady = 1; }

	else if((OtherPlayerHitField.GetContent(i,j+1)==size)) { nReady = 1; }
	else if((OtherPlayerHitField.GetContent(i,j-1)==size)) { nReady = 1; }
    }

    return nReady;
}

int CheckRow(int size, int x, int y, Field& OtherPlayerHitField)
{
    int nCheck = 0;
    int nUp = OtherPlayerHitField.GetContent(x,y-1);
    int nUp2 = OtherPlayerHitField.GetContent(x,y-2);
    int nDown = OtherPlayerHitField.GetContent(x,y+1);
    int nDown2 = OtherPlayerHitField.GetContent(x,y+2);
    int nLeft = OtherPlayerHitField.GetContent(x-1,y);
    int nLeft2 = OtherPlayerHitField.GetContent(x-2,y);
    int nRight = OtherPlayerHitField.GetContent(x+1,y);
    int nRight2 = OtherPlayerHitField.GetContent(x+2,y);

    if(size==4) {
/*	if(nUp==4) nCheck = 1;
	else if((nUp==4) && (nUp2==4)) nCheck = 2;
	else if(nDown==4) nCheck = 3;
	else if((nDown==4) && (nDown2==4)) nCheck = 4;
	else if(nLeft==4) nCheck = 5;
	else if((nLeft==4) && (nLeft2==4)) nCheck = 6;
	else if(nRight==4) nCheck = 7;
	else if((nRight==4) && (nRight2==4)) nCheck = 8;*/
	
    }
    else if(size==3) {
	if(nUp==3) {
	    if(OtherPlayerHitField.GetContent(x,y-2)>=0) {
		nCheck = 1; }
	    else nCheck = 3;
	}
	else if(nDown==3) {
	    if(OtherPlayerHitField.GetContent(x,y+2)<10) {
		nCheck = 3; }
	    else nCheck = 1;
	}
	else if(nLeft==3) {
	    if(OtherPlayerHitField.GetContent(x,y-2)>=0) {
		nCheck = 5; }
	    else nCheck = 7;
	}
	else if(nRight==3) {
	    if(OtherPlayerHitField.GetContent(x,y-2)<10) {
		nCheck = 7; }
	    else nCheck = 5;
	}
    }
    else { }

    return nCheck;
}
