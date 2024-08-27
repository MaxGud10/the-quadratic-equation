#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

#include "solve_kvadratka.h"
#include <string.h>
#include "utils_kvadratka.h"
#include "color.h"
#include "test_kvadratka.h"

enum NRoots solve_square(double a, double b, double c, double *x1, double *x2)
{   
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (compare_doubles(a, 0) == 0)
    {   
        linear_equation(b, c, x1);
        return ONE_ROOT;
    }
    else 
    {
        double discriminant = b * b - 4 * a * c;

        if (compare_doubles(discriminant, 0) == 0)
        {
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOT;
        }
        else if (discriminant > 0)
        {
            double sqrt_discriminant = sqrt(discriminant);
            *x1 = (-b - sqrt_discriminant) / (2 * a);
            *x2 = (-b + sqrt_discriminant) / (2 * a);
            return TWO_ROOT;
        }
        else
        {
            return NO_ROOT; // Нет действительных корней
        }
    }
}

int check_input(double *a, double *b, double *c)
{   
    while (1) 
    { // TODO: коды для цветов для них дефайн в отдельный .h файл #define RED "jgf" printf (RED "" RESET);


        printf(DRAW_TEXT(GREEN,"Enter coefficients a, b, c:\n"));

        int result = scanf("%lf %lf %lf", a, b, c);
        
        if (result == 3)
        {
            break; 
        } 
        else 
        {
            printf(DRAW_TEXT(CYAN,"Invalid input, please enter numeric values.\n"));
            clean_bufer();
        }
    }
    return 0;
}

int general_solution(double a, double b, double c, double *x1, double *x2,const StrTest data [DATA_NUMBER])
{
    check_input(&a, &b, &c);
 
    enum NRoots findRoots = solve_square(a, b, c, x1, x2); 

    root_printing(findRoots, x1, x2);

    printf(DRAW_TEXT(GREEN,"Do you want to do another test? (Yes or No): "));
    char word[ARRAY_LENGTH];
    offer_test(word, data);
    return 0;
}

int linear_equation(double b, double c, double *x1)
{
    if (compare_doubles(b, 0) == 0)
    {
        return (compare_doubles(c, 0) == 0) ? INF_ROOTS : NO_ROOT; 
    }
    else 
    {
        *x1 = -c / b;
        return ONE_ROOT;
    }
    return 0;
}

int root_printing(int findRoots, double* x1, double* x2)
{
    switch(findRoots) 
    {
        case NO_ROOT: 
            printf(DRAW_TEXT(YELLOW,"No roots\n"));
            break;

        case ONE_ROOT: 
            if (compare_doubles(*x1, 0) == 0 )
            {
                printf("x = 0\n"); 
                break;
            }
            printf("x = %lf\n", *x1);
            break;
    
        case TWO_ROOT: 
            printf("x1 = %lf and x2 = %lf\n", *x1, *x2);
            break;

        case INF_ROOTS: 
            printf(DRAW_TEXT(RED,"Any number\n"));
            break;

        default: 
            printf(DRAW_TEXT(RED,"main(): ERROR: findRoots = %d\n"), findRoots);
            return 1;
    }
    return 0;
}