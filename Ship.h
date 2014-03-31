#ifndef SHIP_H
#define SHIP_H

#include <iostream>
using namespace std;

class Ship
{
public:
    Ship();
    Ship(int nCx, int nCy, char direction, int size);
    void PrintChar();
    void SetSize(int size);
    int GetSize();
    void SetX(int x);
    int GetX();
    void SetY(int y);
    int GetY();
    void SetDirection(char direction);
    char GetDirection();
private:
    int nCx, nCy;
    int nSize;
    char cShip;
    char cDirection;
};

#endif
