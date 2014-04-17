#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>
#include "Field.h"
#include "Loc.h"

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

void CreateShip(Ship& PlayerShip, int size, Field& PutField, Field& RemainField);
void ShipsToVector(vector <Ship>& PutVector, Ship& Battleship, Ship& Cruiser1, Ship& Cruiser2,
		   Ship& TorpedoBoat1, Ship& TorpedoBoat2, Ship& TorpedoBoat3, Ship& Submarine1,
		   Ship& Submarine2, Ship& Submarine3, Ship& Submarine4);

#endif
