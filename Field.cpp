#include "Field.h"

Field::Field()
{

}

Field::~Field()
{

}

// Create an empty field (filled with 0's)
void Field::Create()
{
    for(int i=0; i<10; ++i){
	for(int j=0; j<10; ++j){
	    field[i][j] = 0;
	}
    }
}

// Draw the contents of the field
void Field::Draw(int row)
{
    for(int i=0; i<10; ++i){
	if(field[i][row]==0){
	    cout << ".  ";
	}
	else if(field[i][row]==6){
	    cout << "M  ";
	}
	else if(field[i][row]==7){
	    cout << "   ";
	}
	else {
	    cout << field[i][row] << "  ";
	}
    }
}

// Set a location
// @param nSign Item to put on the place (0=empty, 1-4=ship, 6=miss, 7=besides ship)
void Field::SetLocation(int x, int y, int nSign)
{
    field[x][y] = nSign;
}

// Get the content of a location
// @return Returns the int of the location
int Field::GetContent(int x, int y)
{
    return field[x][y];
}
