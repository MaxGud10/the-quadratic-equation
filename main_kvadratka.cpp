#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "color.h"
#include "utils_kvadratka.h"
#include "test_kvadratka.h"
#include "solve_kvadratka.h" // TODO: README
#include "main.h"


const char *UNIT_TEST1 = "test";
const char *UNIT_TEST2 = "--test";
const char *UNIT_TEST3 = "-t";
const char *HELP1      = "help";
const char *HELP2      = "HELP";
const char *FIND_ROOT1 = "-d";
const char *FIND_ROOT2 = "-D";


int main(int arg_c, const char *arg_v[])
{  
    printf("arg_c = %d, arg_v[0] = %s, arg_v[1] = %s\n", arg_c, arg_v[0], arg_v[1]);
    
    double a  = NAN, b  = NAN, c = NAN;
    double x1 = NAN, x2 = NAN; 

    const struct StrTest data[DATA_NUMBER] = // TODO: где константа?
    {
        {1, -5,  6,  3,  2, TWO_ROOT}, // 0
        {1,  2,  1, -1, -1, ONE_ROOT}, // 1
        {1,  0, -9, -3,  3, TWO_ROOT}, // 2 
        {1,  0,  0,  0,  0, ONE_ROOT}, // 3
        {1,  4,  4, -2, -2, ONE_ROOT}, // 4
        {0,  2, -4,  2,  2, ONE_ROOT}, // 5
        {2,  4,  2, -1, -1, ONE_ROOT}, // 6
        {1,  0, -1, -1,  1, TWO_ROOT}, // 7 
        {1, -6,  9,  3,  3, ONE_ROOT}  // 8 
    };

    enum Mode mode = process_arguments(arg_c, arg_v);

    switch (mode)
    {
        case TEST_MODE:
            run_test(data);
            return 0;

        case HELP_MODE:
            printf(DRAW_TEXT(RED,"Hello. This program solves the quadratic equation\n"
                                 "if you enter it .\\do --test or .\\do -t or .\\do test, then"
                                 "the tests with the already set parameters will be displayed"
                                 "if you enter it simply .\\do, then enter the coefficients a and b and c"
                                 "if you write -d or -D, you can enter your parameters a, b, c and then you "
                                 "will be offered unit tests\n"));
            return 0;
        
        case SOLVE_MODE:
            general_solution(a, b, c, &x1, &x2, data);
            break;

        case NONE: 
            printf(DRAW_TEXT(CYAN,"Write the word ./do help and you will get a hint on how to use the program\n" WHITE)); 
            return 0;

        default:
            printf("ERROR\n"); // TODO: прочитай в интернете про цветной вывод. Сделай библиотеку (.h файл), где через define цвета
            return 1;
    }
    return 0;
}

static enum Mode process_arguments(int arg_c, const char *arg_v[])
{
    if (arg_c > 1 && (strcmp (arg_v[1], UNIT_TEST1) == 0 || 
                      strcmp (arg_v[1], UNIT_TEST2) == 0 || 
                      strcmp (arg_v[1], UNIT_TEST3) == 0))
    {
        return TEST_MODE;
    }
    if (arg_c > 1 && (strcmp (arg_v[1], HELP1) == 0 || 
                      strcmp (arg_v[1], HELP2) == 0)) 
    {
        return HELP_MODE;
    }
    if (arg_c > 1 && (strcmp (arg_v[1], FIND_ROOT1) == 0 ||
                      strcmp (arg_v[1], FIND_ROOT2) == 0))
    {
        return SOLVE_MODE;
    }
    else 
    {
        printf(DRAW_TEXT(RED,"ERROR: process_arguments %s is wrong\n"), FIND_ROOT1);
    } 
    return NONE;
}