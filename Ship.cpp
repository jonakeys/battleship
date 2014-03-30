#include "Ship.h"

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

int Ship::GetSize()
{
    return nSize;
}

int Ship::GetX()
{
    return nCx;
}

int Ship::GetY()
{
    return nCy;
}

char Ship::GetDirection()
{
    return cDirection;
}
