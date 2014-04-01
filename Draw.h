#ifndef DRAW_H
#define DRAW_H

#include "Field.h"

void DrawScreen(Field& Player1Field, Field& Player2Field);
void DrawTitle();
void DrawField(Field& DrawField, int row);

#endif
