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
