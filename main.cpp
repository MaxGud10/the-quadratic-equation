#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "solve_square.h"
#include "utils.h"
#include "test.h"

static const char *UNIT_TEST11 = "test"; // TODO сделать с 1 
static const char *UNIT_TEST2 = "--test";  
static const char *UNIT_TEST3 = "-t";
static const char *HELP1 = "help";
static const char *HELP2 = "HELP";
static const char *FIND_ROOT1 = "-d"; // TODO: KEY приставку
static const char *FIND_ROOT2 = "-D";


enum Mode
{
    TEST_MODE,
    HELP_MODE, 
    SOLVE_MODE,
    NONE
};

static const int ARRAY_LENGTH = 40; 

static enum Mode process_arguments(int arg_c, const char *arg_v[])
{
    if (arg_c > 1 && (strcmp (arg_v[1], UNIT_TEST11) == 0 || 
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
        printf("ERROR: process_arguments %s is wrong\n", FIND_ROOT1);
    } 
    return NONE;
}

static int check_input(double *a, double *b, double *c)
{   
    while (1) 
    {
        printf("Enter coefficients a, b, c:\n");

        int result = scanf("%lf %lf %lf", a, b, c);
        
        if (result == 3)
        {
            break; 
        } 
        else 
        {
            printf("Invalid input, please enter numeric values.\n");
            clean_bufer();
        }
    }
    return 0;
}

int main(int arg_c, const char *arg_v[])
{  
    printf("arg_c = %d, arg_v[0] = %s, arg_v[1] = %s\n", arg_c, arg_v[0], arg_v[1]);
    
    double a = NAN, b = NAN, c = NAN;

    const struct str_test data[DATA_NUMBER] =
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
            printf("Hello. This program solves the quadratic equation\n"
                    "if you enter it .\\do --test or .\\do -t or .\\do test, then"
                    "the tests with the already set parameters will be displayed "
                    "if you enter it simply .\\do, then enter the coefficients a and b and c"
                    "if you write -d or -D, you can enter your parameters a, b, c and then you will be offered unit tests");
            return 0;
        
        case SOLVE_MODE:
            check_input(&a, &b, &c);
            break;
        case NONE: 
            printf("NONE keyword\n");
            return 0;
        default:
            printf("___ERROR___");
            return 1;
    }

    double x1 = NAN, x2 = NAN; 
    enum N_ROOTS findRoots = solve_square(a, b, c, &x1, &x2); 

    switch(findRoots) // в функцию
    {
        case NO_ROOT: 
            printf("No roots\n");
            break;

        case ONE_ROOT: 
            printf("x = %lf\n", x1);
            break;
    
        case TWO_ROOT: 
            printf("x1 = %lf and x2 = %lf\n", x1, x2);
            break;

        case INF_ROOTS: 
            printf("Any number\n");
            break;

        default: 
            printf("main(): ERROR: findRoots = %d\n", findRoots);
            return 1;
    }

    printf("Do you want to do another test? (Yes or No): ");
    char word[ARRAY_LENGTH];
    offer_test(word, data);
    return 0;
}

