#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

class Ship
{
public:
Ship(int nCx, int nCy, char direction, int size);
    void PrintChar();
    int GetSize();
    int GetX();
    int GetY();
    char GetDirection();
private:
    int nCx, nCy;
    int nSize;
    char cShip;
    char cDirection;
};

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
#endif
