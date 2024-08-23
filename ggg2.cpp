#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h> 

  
#define CHAR_CONST 40

// Определяем константу для бесконечного числа корней
const double x_min = 1e-6;
const char *KEY_word1 = "test";
const char *KEY_WORD2 = "--test";
const char *KEY_WORD3 = "-t";
const char *HELP1 = "help";
const char *HELP2 = "HELP";
const char *PRINT1 = "-d";
const char *PRINT2 = "-D";


enum nRoots { 
    NO_ROOT, 
    ONE_ROOT, 
    TWO_ROOT,
    inf_roots
}; //NO_ROOTs, ONE_ROOTs, TWO_ROOTs --> именнованная константа, представляющей целочисленное значение 0, 1, 2 соотвественно 
struct str_test {
    double a, b, c;
    double x1_expect, x2_expect;
    enum nRoots number_roots_expected;

};

enum nRoots solve_square(double a, double b, double c, double *x1, double *x2);
int compare_doubles(double x1, double x2);
int unit_test(struct str_test data, int test_number);
int clean_bufer();
int offer_test(char word[CHAR_CONST], const struct str_test data [10]);
int key_word(int arg_c, const char *arg_v[], const struct str_test data[9], double a, double b, double c);
int check_input(double a, double  b, double c);

int proverka(const struct str_test data [9]);
//int candle()




int main(int arg_c, const char *arg_v[])
{
    printf("arg_c = %d, arg_v[0] = %s, arg_v[1] = %s\n", arg_c, arg_v[0], arg_v[1]);
    
    double a = NAN, b = NAN, c = NAN;

    const struct str_test data[9] =
    {
        {1, -5, 6, 3, 2, TWO_ROOT},
        {1, 2, 1, -1, -1, ONE_ROOT},
        {1, 0, -9, -3, 3, TWO_ROOT},
        {1, 0, 0, 0, 0, ONE_ROOT},
        {1, 4, 4, -2, -2, ONE_ROOT},
        {0, 2, -4, 2, 2, ONE_ROOT},
        {2, 4, 2, -1, -1, ONE_ROOT},
        {1, 0, -1, -1, 1, TWO_ROOT},
        {1, -6, 9, 3, 3, ONE_ROOT}
    };

    key_word(arg_c, arg_v, data, a, b, c);

    /*while (1) {
        printf("Enter coefficients a, b, c:\n");
        int result = scanf("%lf %lf %lf", &a, &b, &c);
        
        if (result == 3) {
            break; 
        } else 
        {
            printf("Invalid input, please enter numeric values.\n");
            clean_bufer();
            break;
        }
    }*/
    double x1 = NAN, x2 = NAN;
    enum nRoots findRoots = solve_square(a, b, c, &x1, &x2);

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

        case inf_roots: 
            printf("Any number\n");
            break;

        default: 
            printf("main(): ERROR: findRoots = %d\n", findRoots);
            return 1;
    }

   

    printf("Do you want to do another test? (Yes or No): ");
    char word[CHAR_CONST];
    offer_test(word, data);
    
}

int provekka(const struct str_test data [9])
{

    for (int i = 0; i < 10; i++)
    {
        unit_test(data[i], i);
    }
    return 0;
}

int offer_test( char word[CHAR_CONST], const struct str_test data [10])
{   
    
    scanf("%s", word);

    if (strcasecmp(word, "Yes") == 0 || strcasecmp(word, "yes") == 0)
    {
        provekka(data);
        return 0;

    }
    else if (strcasecmp(word, "No") == 0 || strcasecmp(word, "no") == 0) 
    {
        printf("Exiting the program.\n");
        return 0;
    }
    else printf("Invalid input, exiting.\n");
    return 0;
}

int clean_bufer()
{
    for (;;)
    {   
        
        int ch = getchar();
        if( ch != '\n' || ch != EOF)
        {
            return 0;
        }
    }
    return 0;
}

int key_word(int arg_c, const char *arg_v[], const struct str_test data [9], double a, double b, double c)
{
    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_word1) == 0)
    {
        provekka(data);
            return 0;   
    }
    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_WORD2) == 0)
    {
        provekka(data);
        return 0;   
    }

    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_WORD3) == 0)
    {
        provekka(data);
        return 0; 
    }
    else if (strcasecmp(arg_v[1], "No") == 0 ) 
    {
        printf("There is no such word.\n");
        return 0;
    }

    if (arg_c > 1 && strcasecmp(arg_v[1], HELP1) == 0 )
    {
        printf("Hello. THis program solves the quadratic equation\n");
        printf("if you enter it .\\do --test or .\\do -t or .\\do test, then the tests with the already set parameters will be displayed "
                "if you enter it simply .\\do, then enter the coefficients a and b and c");
        return 0;
    }

    if (arg_c > 1 && strcasecmp(arg_v[1], HELP2) == 0 )
    {
        printf("Hello. THis program solves the quadratic equation\n");
        printf("\nif you enter it .\\do --test or .\\do -t or .\\do test, then the tests with the already set parameters will be displayed "
                "if you enter it simply .\\do, then enter the coefficients a and b and c");
        return 0;
    }

    if (arg_c > 1 && strcasecmp(arg_v[1], PRINT1) == 0 && strcasecmp(arg_v[1], PRINT2) == 0 )
    {
        printf("\n -----\n");
        
        printf("Enter coefficients a, b, c:\n");

        printf("\n>>>>>>>\n");
        check_input(a, b, c);
        return 0;
    }
    else {
        printf("ERROR: Key_word %s is wrong\n", PRINT1);
    }


    return 0;
}

int check_input(double a, double b, double c)
{
    while (1) {
        printf("Enter coefficients a, b, c:\n");
        int result = scanf("%lf %lf %lf", &a, &b, &c);
        
        if (result == 3) {
            break; 
        } else 
        {
            printf("Invalid input, please enter numeric values.\n");
            clean_bufer();
            break;
        }
    }
    return 0;
}

int compare_doubles(double x1, double x2) 
{
    if (fabs(x1 - x2) < x_min) {
        return 0;  
    }
    return (x1 < x2) ? -1 : 1; 
}

enum nRoots solve_square(double a, double b, double c, double *x1, double *x2)
{
    if (compare_doubles(a, 0) == 0)
    {
        if (compare_doubles(b, 0) == 0)
        {
            return (compare_doubles(c, 0) == 0) ? inf_roots : NO_ROOT;
        }
        else 
        {
            *x1 = -c / b;
            return ONE_ROOT;
        }
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

/*int candle() 
{

}*/


int unit_test( struct str_test data, int test_number)
{
    double x1 =NAN, x2 = NAN;
    enum nRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
        {
            printf("Error %d: a = %lf b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf\n"
                    "Expected %d: number_roots = %d: x1 = %lf, x2 = %lf\n", 
                    test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                    test_number, data.number_roots_expected, data.x1_expect, data.x2_expect);
            return 1;
        }
    return 0;
}

void all_test( struct str_test data)
{
    const int nTest = 11;
    struct str_test test [nTest] = {{1, -3, 2, 2, 1, TWO_ROOT},
                                    {1, -5, 6, 3, 2, TWO_ROOT},
                                    {1, 2, 1, -1, -1, ONE_ROOT},
                                    {1, 0, -9, -3, 3, TWO_ROOT},
                                    {1, 0, 0, 0, 0, ONE_ROOT},
                                    {1, 4, 4, -2, -2, ONE_ROOT},
                                    {0, 2, -4, 2, 2, ONE_ROOT},
                                    {2, 4, 2, -1, -1, ONE_ROOT},
                                    {1, 0, -1, -1, 1, NO_ROOT},
                                    {1, -6, 9, 3, 3, ONE_ROOT}};

    for (int i = 0; i < nTest; i++)
    {
        unit_test(test[i], i);
    }
}

/*
*/