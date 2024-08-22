#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h> 

  
#define CHAR_CONSR 40

// Определяем константу для бесконечного числа корней
const double x_min = 1e-6;
const char *KEY_word1 = "test";
const char *KEY_WORD2 = "--test";
const char *KEY_WORD3 = "-t";
const char *HELP1 = "help";
const char *HELP2 = "HELP"; 


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
//

enum nRoots solve_square(double a, double b, double c, double *x1, double *x2);
int compare_doubles(double x1, double x2);
int all_test(struct str_test data, int test_number);
int clean_bufer();

struct str_test data1 = {1, -3, 2, 2, 1, TWO_ROOT};
struct str_test data2 = {1, -5, 6, 3, 2, TWO_ROOT};
struct str_test data3 = {1, 2, 1, -1, -1, ONE_ROOT};
struct str_test data4 = {1, 0, -9, -3, 3, TWO_ROOT};
struct str_test data5 = {1, 0, 0, 0, 0, ONE_ROOT};
struct str_test data6 = {1, 4, 4, -2, -2, ONE_ROOT};
struct str_test data7 = {0, 2, -4, 2, 2, ONE_ROOT};
struct str_test data8 = {2, 4, 2, -1, -1, ONE_ROOT}; 
struct str_test data9 = {1, 0, 1, NAN, NAN, NO_ROOT};
struct str_test data10 = {1, -6, 9, 3, 3, ONE_ROOT};

int main(int arg_c, const char *arg_v[])
{
    printf("arg_c = %d, arg_v[0] = %s, arg_v[1] = %s\n", arg_c, arg_v[0], arg_v[1]);
    char word[CHAR_CONSR];
    double a = NAN, b = NAN, c = NAN;

    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_word1) == 0)
    {
        all_test(data1, 1);
        all_test(data2, 2);
        all_test(data3, 3);
        all_test(data4, 4);
        all_test(data5, 5);
        all_test(data6, 6);
        all_test(data7, 7);
        all_test(data8, 8);
        all_test(data9, 9);
        all_test(data10, 10);
        return 0;   
    }
    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_WORD2) == 0)
    {
        all_test(data1, 1);
        all_test(data2, 2);
        all_test(data3, 3);
        all_test(data4, 4);
        all_test(data5, 5);
        all_test(data6, 6);
        all_test(data7, 7);
        all_test(data8, 8);
        all_test(data9, 9);
        all_test(data10, 10);
        return 0;   
    }
    if (arg_c > 1 && strcasecmp(arg_v[1], KEY_WORD3) == 0)
    {
        all_test(data1, 1);
        all_test(data2, 2);
        all_test(data3, 3);
        all_test(data4, 4);
        all_test(data5, 5);
        all_test(data6, 6);
        all_test(data7, 7);
        all_test(data8, 8);
        all_test(data9, 9);
        all_test(data10, 10);
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


    while (1) {
        printf("Enter coefficients a, b, c:\n");
        int result = scanf("%lf %lf %lf", &a, &b, &c);
        
        if (result == 3) {
            break; 
        } else {
            printf("Invalid input, please enter numeric values.\n");
            clean_bufer();
            break;
        }
    }
    double x1 = NAN, x2 = NAN;
    enum nRoots findRoots = solve_square(a, b, c, &x1, &x2);

    switch(findRoots)
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

   struct str_test data1 = {1, -3, 2, 2, 1, TWO_ROOT};  // (x - 2)(x - 1) = 0 --> корни 1, 2
    //all_test(data1, 1);

    struct str_test data2 = {1, -5, 6, 3, 2, TWO_ROOT};   // (x - 3)(x - 2) = 0 -> корни 2, 3
    //all_test(data2, 2);

    struct str_test data3 = {1, 2, 1, -1, -1, ONE_ROOT};  // (x + 1)^2 = 0 -> корень -1
    //all_test(data3, 3);

    struct str_test data4 = {1, 0, -9, -3, 3, TWO_ROOT};  // (x - 3)(x + 3) = 0 -> корни -3, 3
    //all_test(data4, 4);

    struct str_test data5 = {1, 0, 0, 0, 0, ONE_ROOT};    // x = 0 -> корень 0
    //all_test(data5, 5);

    struct str_test data6 = {1, 4, 4, -2, -2, ONE_ROOT};   // (x + 2)^2 = 0 -> корень -2
    //all_test(data6, 6);

    struct str_test data7 = {0, 2, -4, 2, 2, ONE_ROOT};    // 2x = 4 -> корень 2
    //all_test(data7, 7);

    struct str_test data8 = {2, 4, 2, -1, -1, ONE_ROOT};   // 2(x + 1)^2 = 0 -> корень -1
   // all_test(data8, 8);

    struct str_test data9 = {1, 0, 1, NAN, NAN, NO_ROOT}; // x^2 + 1 = 0 -> нет действительных корней
    //all_test(data9, 9);

    struct str_test data10 = {1, -6, 9, 3, 3, ONE_ROOT};   // (x - 3)^2 = 0 -> корень 3
    //all_test(data10, 10);

    printf("Do you want to do another test? (Yes or No): ");
    scanf("%s", &word);
    if (strcasecmp(word, "Yes") == 0 || strcasecmp(word, "yes") == 0)
    {
        all_test(data1, 1);
        all_test(data2, 2);
        all_test(data3, 3);
        all_test(data4, 4);
        all_test(data5, 5);
        all_test(data6, 6);
        all_test(data7, 7);
        all_test(data8, 8);
        all_test(data9, 9);
        all_test(data10, 10);
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



int all_test( struct str_test data, int test_number)
{
    double x1 =NAN, x2 = NAN;
    enum nRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
        {
            printf("Error %d: a = %lg, b = %lg, c = %lg,  number_roots = %d: x1 = %lg, x2 = %lg\n"
                    "Expected %d: number_roots = %d: x1 = %lg, x2 = %lg\n", 
                    test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                    test_number, data.number_roots_expected, data.x1_expect, data.x2_expect);
            return 1;
        }
    return 0;
}

/*if you enter it .\do --test or .\do -t or .\do test, then the tests with the already set parameters will be displayed 
if you just type it in .\do, then*/

/*если ты введешь .\do --test или .\do -t или .\do test, то выведется тесты с уже заданными параметрами 
если ты введешь просто .\do, то */