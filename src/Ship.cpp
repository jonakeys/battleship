#include <iostream>
#include "../headers/Ship.h"

Ship::Ship()
{
    nCx = 0;
    nCy = 0;
    nSize = 0;
    cDirection = 0;
}

Ship::Ship(int x, int y, char direction, int size)
{
    cShip = (char) size+'0';
    nCx = x;
    nCy = y;
    nSize = size;
    cDirection = direction;
}

void Ship::PrintChar()
{
cout << "Teken van schip is: " << cShip << endl;
}

// Set the size of the ship
void Ship::SetSize(int size)
{
    nSize = size;
}

// Get the size of the ship
int Ship::GetSize()
{
    return nSize;
}

void Ship::SetX(int x)
{
    nCx = x;
}

int Ship::GetX()
{
    return nCx;
}

void Ship::SetY(int y)
{
    nCy = y;
}

int Ship::GetY()
{
    return nCy;
}

void Ship::SetDirection(char direction)
{
    cDirection = direction;
}

// Get direction
// @return Returns location in char (b=up, o=down, l=left, r=right)
char Ship::GetDirection()
{
    return cDirection;
}

// Create a ship
// @param PlayerShip Choose ship to place
// @param PutField Field to place the ship
void CreateShip(Ship& PlayerShip, int size, Field& PutField)
{
    int x, y;
    char cX;
    char direction;
    int nUp = 0, nDown = 0, nLeft = 0, nRight = 0;
    bool DirOk = false;
    bool DONE = false;
    bool VALIDINPUT = true;
    bool VALIDINPUTDIR = true;
    
    while(!DONE) {
	while(VALIDINPUT) {
	    cout << "\nKies startcoordinaat (bijvoorbeeld: 'c 6'): ";
	    cin >> cX  >> y;

	    if(cX != 'a' && cX != 'b' && cX != 'c' && cX != 'd' && cX != 'e' &&
	       cX != 'f' && cX != 'g' && cX != 'h' && cX != 'i' && cX != 'j') {
		cout << "Ongeldig x-coordinaat. Probeer het opnieuw (a-j).\n";
		cin.ignore(10000,'\n');
		cin.clear();
	    }
	    else if(y < 0 || y > 9) {
		cout << "Ongeldig y-coordinaat. Probeer het opnieuw (0-9).\n";
		cin.ignore(10000,'\n');
		cin.clear();
	    }
	    else {
		VALIDINPUT = false;
	    }
	}

	while(VALIDINPUTDIR) {
	    if(size > 1) {
		cout << "Richting ('b'oven, 'o'nder, 'l'inks, 'r'echts): ";
		cin >> direction;
	    }
	    else {
		direction = 'r';
	    }
	
	    if(direction != 'b' && direction != 'o' && direction != 'l' && direction != 'r') {
		cout << "Ongeldige richting. Probeer het opnieuw ('b', 'o', 'l', 'r').\n";
		cin.ignore(10000,'\n');
		cin.clear();
	    }
	    else {
		VALIDINPUTDIR = false;
	    }
	}
	
	// Convert the char-input of x coordinate to int
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

	nUp = LocUpFree(x,y,size,PutField);
	nDown = LocDownFree(x,y,size,PutField);
	nLeft = LocLeftFree(x,y,size,PutField);
	nRight = LocRightFree(x,y,size,PutField);

	if((nUp == 0) && (nUp == 0) && (nLeft == 0) && (nRight == 0)) {
	    cout << "Deze locatie is niet beschikbaar. Probeer het opnieuw.\n";
	}
	
	if(direction == 'b' && nUp==1) {
	    DirOk = true;
	}
	if(direction == 'o' && nDown==1) {
	    DirOk = true;
	}
	if(direction == 'l' && nLeft==1) {
	    DirOk = true;
	}
	if(direction == 'r' && nRight==1) {
	    DirOk = true;
	}

	if(DirOk == false) {
	    cout << "Deze richting is niet mogelijk. Probeer het opnieuw.\n";
	}
	
	if((nUp==1||nDown==1||nLeft==1||nRight==1) && (DirOk==true)) {
	    DONE = true;
	}
    }
    
    PlayerShip.SetX(x);
    PlayerShip.SetY(y);
    PlayerShip.SetDirection(direction);
    PlayerShip.SetSize(size);

    switch(direction) {
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

// Put ships in a vector
void ShipsToVector(vector <Ship>& PutVector, Ship& Battleship, Ship& Cruiser1, Ship& Cruiser2,
		   Ship& TorpedoBoat1, Ship& TorpedoBoat2, Ship& TorpedoBoat3, Ship& Submarine1,
		   Ship& Submarine2, Ship& Submarine3, Ship& Submarine4)
{
    PutVector.push_back(Battleship);
    PutVector.push_back(Cruiser1);
    PutVector.push_back(Cruiser2);
    PutVector.push_back(TorpedoBoat1);
    PutVector.push_back(TorpedoBoat2);
    PutVector.push_back(TorpedoBoat3);
    PutVector.push_back(Submarine1);
    PutVector.push_back(Submarine2);
    PutVector.push_back(Submarine3);
    PutVector.push_back(Submarine4);
}

