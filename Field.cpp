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
    cout << "\t     a  b  c  d  e  f  g  h  i  j" << endl << endl;

    for(int i=0; i<10; ++i){
	cout << "\t " << i <<  "   ";
	for(int j=0; j<10; ++j){
	    if(field[i][j]==0){
		cout << ".  ";
	    }
	    else {
		cout << field[i][j] << "  ";
	    }
	}
	cout << " " << i << endl << endl;
    }
    cout << "\t     a  b  c  d  e  f  g  h  i  j" << endl << endl;
}

void Field::SetLocation(int x, int y, int nSign)
{
    field[x][y] = nSign;
}

int Field::GetContent(int x, int y)
{
    return field[x][y];
}
