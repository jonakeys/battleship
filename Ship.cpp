#include "Ship.h"

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

void Ship::SetSize(int size)
{
    nSize = size;
}

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

char Ship::GetDirection()
{
    return cDirection;
}

void CreateShip(Ship& PlayerShip, int size, Field& PutField)
{
    int x, y;
    char cX;
    char direction;
    int nUp = 0, nDown = 0, nLeft = 0, nRight = 0;
    bool DirOk = false;
    bool DONE = false;
    
    while(!DONE) {
	cout << "\nKies startcoordinaat (bijvoorbeeld: 'c 6'): ";
	cin >> cX  >> y;
	if(size > 1) {
	    cout << "Richting ('b'oven, 'o'nder, 'l'inks, 'r'echts): ";
	    cin >> direction;
	}
	else {
	    direction = 'r';
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
	}
	break;
    case 'o':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x,y+i,size);
	}
	break;
    case 'l':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x-i,y,size);
	}
	break;
    case 'r':
	for(int i=0; i<size; ++i) {
	    PutField.SetLocation(x+i,y,size);
	}
	break;
    }
}

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

