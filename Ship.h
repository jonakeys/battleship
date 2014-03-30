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

#endif
