#include <iostream>
#include "Field.h"
using namespace std;

int LocUpFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	   (TestField.GetContent(x,y-2)==0) && (TestField.GetContent(x,y-3)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0) && 
	   (TestField.GetContent(x,y-2)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y)==0) && (TestField.GetContent(x,y-1)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y)==0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocDownFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0) && 
	   (TestField.GetContent(x,y+2)==0) && (TestField.GetContent(x,y+3)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0) && 
	   (TestField.GetContent(x,y+2)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x,y+1)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocLeftFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0) && 
	   (TestField.GetContent(x-2,y)==0) && (TestField.GetContent(x-3,y)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0) && 
	   (TestField.GetContent(x-2,y)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x-1,y)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}

int LocRightFree(int x, int y, int size, Field& TestField)
{
    int free = 0;

    switch(size) {
    case 4:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0) && 
	   (TestField.GetContent(x+2,y)==0) && (TestField.GetContent(x+3,y)==0)) {
	    free = 1;
	}
	break;
    case 3:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0) && 
	   (TestField.GetContent(x+2,y)==0)) {
	    free = 1;
	}
	break;
    case 2:
	if((TestField.GetContent(x,y) == 0) && (TestField.GetContent(x+1,y)==0)) {
	    free = 1;
	}
	break;
    case 1:
	if((TestField.GetContent(x,y) == 0)) {
	    free = 1;
	}
	break;
    }

    return free;
}
