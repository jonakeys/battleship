#include <iostream>
#include "../headers/Field.h"
using namespace std;

// Test if location and up are free
// @return Returns 1 if location is free
int LocUpFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((y-3)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	       (TestField.GetContent(x,y-2)==0) && (TestField.GetContent(x,y-3)==0)) {
		free = 1;
	    }
	}
	break;
    case 3:
	if((y-2)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	       (TestField.GetContent(x,y-2)==0)) {
		free = 1;
	    }
	}
	break;
    case 2:
	if((y-1)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0)) {
		free = 1;
	    }
	}
	break;
    case 1:
	if((y)>=0) {
	    if((TestField.GetContent(x,y)==0)) {
		free = 1;
	    }
	}
	break;
    }

    return free;
}

// Test if location and down are free
// @return Returns 1 if location is free
int LocDownFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((y+3)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y+1)==0) && 
	       (TestField.GetContent(x,y+2)==0) && (TestField.GetContent(x,y+3)==0)) {
		free = 1;
	    }
	}
	break;
    case 3:
	if((y+2)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y+1)==0) && 
	       (TestField.GetContent(x,y+2)==0)) {
		free = 1;
	    }
	}
	break;
    case 2:
	if((y+1)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y+1)==0)) {
		free = 1;
	    }
	}
	break;
    case 1:
	if((y)<=9) {
	    if((TestField.GetContent(x,y)==0)) {
		free = 1;
	    }
	}
	break;
    }

    return free;
}

// Test if location and left are free
// @return Returns 1 if location is free
int LocLeftFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((x-3)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x-1,y)==0) && 
	       (TestField.GetContent(x-2,y)==0) && (TestField.GetContent(x-3,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 3:
	if((x-2)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x-1,y)==0) && 
	       (TestField.GetContent(x-2,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 2:
	if((x-1)>=0) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x-1,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 1:
	if((x)>=0) {
	    if((TestField.GetContent(x,y)==0)) {
		free = 1;
	    }
	}
	break;
    }

    return free;
}

// Test if location and right are free
// @return Returns 1 if location is free
int LocRightFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((x+3)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x+1,y)==0) && 
	       (TestField.GetContent(x+2,y)==0) && (TestField.GetContent(x+3,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 3:
	if((x+2)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x+1,y)==0) && 
	       (TestField.GetContent(x+2,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 2:
	if((x+1)<=9) {
	    if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x+1,y)==0)) {
		free = 1;
	    }
	}
	break;
    case 1:
	if((x)<=9) {
	    if((TestField.GetContent(x,y)==0)) {
		free = 1;
	    }
	}
	break;
    }

    return free;
}
