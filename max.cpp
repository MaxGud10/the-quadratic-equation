//! @file 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <TXLib.h>
#include <assert.h>

#include "color.h"

static const double ERROR_RATE = 1e-6; // погрешность
static const int DATA_NUMBER   = 9;
static const int ARRAY_LENGTH  = 40; 

const char *UNIT_TEST1 = "test";
const char *UNIT_TEST2 = "--test";
const char *UNIT_TEST3 = "-t";
const char *HELP1      = "help";
const char *HELP2      = "HELP";
const char *FIND_ROOT1 = "-d";
const char *FIND_ROOT2 = "-D";

enum Mode
{
    NONE       = 0,
    TEST_MODE  = 1,
    HELP_MODE  = 2, 
    SOLVE_MODE = 3
};

enum NRoots 
{ 
    NO_ROOT   = 0, 
    ONE_ROOT  = 1, 
    TWO_ROOT  = 2,
    INF_ROOTS = 3
}; //NO_ROOTs, ONE_ROOTs, TWO_ROOTs --> именнованная константа, представляющей целочисленное значение 0, 1, 2 соотвественно 

struct StrTest 
{ 
    double a, b, c;
    double x1_expect, x2_expect;
    enum NRoots number_roots_expected; 
};

enum NRoots solve_square(double a, double b, double c, double *x1, double *x2);
int compare_doubles(double x1, double x2);
int unit_test(struct StrTest data, int test_number);
int clean_bufer();
int offer_test(char *word, const struct StrTest data [DATA_NUMBER]);
enum Mode process_arguments(int arg_c, const char *arg_v[]);
int check_input(double *a, double  *b, double *c);
int general_solution(double a, double b, double c, double *x1, double *x2,  const StrTest data [DATA_NUMBER]);
int linear_equation(double b, double c, double *x1);
int run_test(const struct StrTest data [DATA_NUMBER]);
int root_printing(int findRoots, double* x1, double* x2);

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

int run_test(const struct StrTest data [DATA_NUMBER])
{
    assert(data != nullptr);
    for (int i = 0; i < DATA_NUMBER; i++)
    {
        unit_test(data[i], i);
        return 0;
    }
    return 0;
}

//#include "offer_test.cpp"
int offer_test(char *word, const struct StrTest data [DATA_NUMBER])
{   
    assert(data != nullptr);
    scanf("%s", word); 

    if (strcmp (word, "Yes") == 0 || 
        strcmp (word, "yes") == 0)
    {
        run_test(data);// TODO: переимновать
        return 0;
    }
    else if (strcmp (word, "No") == 0 || 
             strcmp (word, "no") == 0) 
    {
        printf(DRAW_TEXT(RED,"Exiting the program.\n"));
        return 0;
    }
    else printf(DRAW_TEXT(RED,"Invalid input, exiting.\n"));
    return 0;
}

//#include "process_arguments.cpp"
enum Mode process_arguments(int arg_c, const char *arg_v[])
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

int root_printing(int findRoots, double* x1, double* x2)
{
    switch(findRoots) 
    {
        case NO_ROOT: 
            printf(DRAW_TEXT(YELLOW,"No roots\n"));
            break;

        case ONE_ROOT: 
            if (compare_doubles(*x1, 0) == 0 )// TODO: можно проверять только один корень
            {
                printf("x = 0\n"); // TODO: правильно ли я сделал ? Пока нет(
                break;
            }
            printf("x = %lf\n", *x1); // TODO: проверка на -0 (если около нуля значение, ты печатай пользователю ноль)
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

//#include "check_input.cpp"
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
    if (fabs(x1 - x2) < ERROR_RATE) 
    {
        return 0;  
    }
    return (x1 < x2) ? -1 : 1; 
}

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

//#include "unit_test.cpp"
int unit_test(struct StrTest data, int test_number)
{
    double x1 = NAN , x2 = NAN;
    enum NRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
    {
            if (compare_doubles(x1, data.x2_expect) == 0 ||
                compare_doubles(x2, data.x1_expect) == 0) // проверка на совпадающие корни 
            { // TODO: кодстайд
            printf(DRAW_TEXT(YELLOW,"All right\n"));
            }
            else
            {
                printf("Error %d: a = %lf b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf\n"
                       "Expected %d: number_roots = %d: x1 = %lf, x2 = %lf\n", 
                        test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                        test_number, data.number_roots_expected, data.x1_expect, data.x2_expect);
                    return 1;
            }
    }
    return 0;
}
