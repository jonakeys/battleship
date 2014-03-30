#ifndef FIELD_H
#define FIELD_H

#include <iostream>
using namespace std;

class Field
{
public:
    Field();
    ~Field();
    void Create();
    void Draw();
    void SetLocation(int x, int y, int nSign);
    
private:
    int field[8][8];
};

Field::Field()
{

}

Field::~Field()
{

}

void Field::Create()
{
    for(int i=0; i<8; ++i){
	for(int j=0; j<8; ++j){
	    field[i][j] = 0;
	}
    }
}

void Field::Draw()
{
    cout << "\t    0  1  2  3  4  5  6  7  x" << endl << endl << endl;

    for(int i=0; i<8; ++i){
	cout << "\t" << i <<  "   ";
	for(int j=0; j<8; ++j){
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

#endif
