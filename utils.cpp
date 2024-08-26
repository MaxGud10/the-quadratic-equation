#include <math.h>
#include <stdio.h>

#include "utils.h"

int clean_bufer()
{
    for (;;)
    {   
        int ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            return 0;
        }
    }
    return 0;
}


//#include "compare_doubles.cpp"
int compare_doubles(double x1, double x2) 
{   
    if (fabs(x1 - x2) < MIN_CONST) 
    {
        return 0;  
    }
    return (x1 < x2) ? -1 : 1; 
}