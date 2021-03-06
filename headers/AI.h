#ifndef AI_H
#define AI_H

#include <iostream>
#include "Field.h"
#include "Ship.h"
#include "Draw.h"

using namespace std;

int AIGuess(int turn, Field& OtherPlayerField, Field& OtherPlayerHitField, string playerName, Field& OtherPlayerRemainField);
void AIPlaceShips(Field& PutField, vector <Ship>& vShips, Field& RemainField);
void AICreateShip(Ship& PlayerShip, int size, Field& PutField, Field& RemainField, int nCount);
int CheckReady(Field& OtherPlayerHitField, int x, int y, int size);
int CheckRow(int size, int x, int y, Field& OtherPlayerHitField);

#endif
