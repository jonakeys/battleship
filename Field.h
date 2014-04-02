#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <vector>
using namespace std;

class Field
{
public:
    Field();
    ~Field();
    void Create();
    void Draw(int row);
    void SetLocation(int x, int y, int nSign);
    int GetContent(int x, int y);
    
private:
    int field[10][10];
};

#endif
