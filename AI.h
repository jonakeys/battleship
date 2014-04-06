#ifndef AI_H
#define AI_H

#include <iostream>
#include "Field.h"
#include "Ship.h"
#include "Draw.h"

using namespace std;

int AIGuess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName);
void AIPlaceShips(Field& PutField, vector <Ship>& vShips);
void AICreateShip(Ship& PlayerShip, int size, Field& PutField);
int CheckReady(Field& OtherPlayerHitField, int x, int y, int size);

#endif
