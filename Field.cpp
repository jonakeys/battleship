#include "Field.h"

Field::Field()
{

}

Field::~Field()
{

}

void Field::Create()
{
    for(int i=0; i<10; ++i){
	for(int j=0; j<10; ++j){
	    field[i][j] = 0;
	}
    }
}

void Field::Draw(int row)
{
    for(int i=0; i<10; ++i){
	if(field[i][row]==0){
	    cout << ".  ";
	}
	else if(field[i][row]==6){
	    cout << "M  ";
	}
	else {
	    cout << field[i][row] << "  ";
	}
    }
}

void Field::SetLocation(int x, int y, int nSign)
{
    field[x][y] = nSign;
}

int Field::GetContent(int x, int y)
{
    return field[x][y];
}
