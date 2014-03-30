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

void Field::Draw()
{
    cout << "\t    0  1  2  3  4  5  6  7  8  9  x" << endl << endl << endl;

    for(int i=0; i<10; ++i){
	cout << "\t" << i <<  "   ";
	for(int j=0; j<10; ++j){
	    if(field[i][j]==0){
		cout << ".  ";
	    }
	    else {
		cout << field[i][j] << "  ";
	    }
	}
	cout << endl << endl;
    }
    cout << "\ty" << endl << endl;
}

void Field::SetLocation(int x, int y, int nSign)
{
    field[x][y] = nSign;
}
