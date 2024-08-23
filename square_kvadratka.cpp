#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h> 
#include <TXLib.h>

  
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

const int Data_number = 9;


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
int offer_test(char word[CHAR_CONST], const struct str_test data [Data_number]);
int key_word(int arg_c, const char *arg_v[], const struct str_test data[Data_number], double *a, double *b, double *c);
int check_input(double *a, double  *b, double *c);
void all_test( struct str_test data);

int proverka(const struct str_test data [Data_number]);
//int candle()




int main(int arg_c, const char *arg_v[])
{   
    printf("\nhahahaha\n");
    printf("arg_c = %d, arg_v[0] = %s, arg_v[1] = %s\n", arg_c, arg_v[0], arg_v[1]);
    
    double a = 0, b = 0, c = 0;

    const struct str_test data[Data_number] =
    {
        {1, -5,  6,  3,  2, TWO_ROOT}, // 0
        {1,  2,  1, -1, -1, ONE_ROOT}, // 1
        {1,  0, -9, -3,  3, TWO_ROOT}, // 2 
        {1,  0,  0,  0,  0, ONE_ROOT}, // 3
        {1,  4,  4, -2, -2, ONE_ROOT}, // 4
        {0,  2, -4,  2,  2, ONE_ROOT}, // 5
        {2,  4,  2, -1, -1, ONE_ROOT}, // 6
        {1,  0, -1, -1,  1, TWO_ROOT}, // 7
        {1, -6,  9,  1,  3, ONE_ROOT}  // 8
    };
    $(a), $(b),$(c);

    key_word(arg_c, arg_v, data, &a, &b, &c);
    $(a), $(b),$(c);

    while (1) {

    double x1 = 0, x2 = 0;
    printf("\nwhy tam oshibka\n");
    $(a), $(b), $(c);
    enum nRoots findRoots = solve_square(a, b, c, &x1, &x2);

    switch(findRoots) // в функцию
    {
        case NO_ROOT: 
            printf("\n why no roots\n");
            printf("No roots\n");
            break;

        case ONE_ROOT: 
            printf("\n<<why one root>>\n");
            printf("x= %lf\n", x1);
            break;
    
        case TWO_ROOT: 
            printf("\n----why two roots---\n");
            printf("x1 = %lf and x2 = %lf\n", x1, x2);
            break;

        case inf_roots: 
            printf("\n<<<<<<<<   >>>>>>>\n");
            printf("Any number\n");
            break;

        default: 
            printf("main(): ERROR: findRoots = %d\n", findRoots);
            return 1;
    }
}
   

    printf("Do you want to do another test? (Yes or No): ");
    char word[CHAR_CONST];
    $(a, "znachenie a");
    offer_test(word, data);
    
}

int proverka(const struct str_test data [Data_number])
{

    for (int i = 0; i < Data_number; i++)
    {
        unit_test(data[i], i);
    }
    return 0;
}

#include "offer_test.cpp"



#include "key_word.cpp"

#include "check_input.cpp"

#include "compare_doubles.cpp"

enum nRoots solve_square(double a, double b, double c, double *x1, double *x2)
{   
    printf("\n___solve_square_____\n");
    $(a); $(b), $(c);
    if (compare_doubles(a, 0) == 0)
    {   
        printf("----b = 0----");
        if (compare_doubles(b, 0) == 0)
        {
            printf("\n>>>>>>\n");
            return (compare_doubles(c, 0) == 0) ? inf_roots : NO_ROOT;
        }
        else 
        {
            printf("-----a = 0 ------");
            *x1 = -c / b;
            return ONE_ROOT;
        }
    }
    else 
    {
        double discriminant = b * b - 4 * a * c;
        printf("__reshka__discriminant___");

        if (compare_doubles(discriminant, 0) == 0)
        {
            $(x1),$(x2);
            printf("----discriminant = 0---");
            *x1 = *x2 = -b / (2 * a);
            return ONE_ROOT;
        }
        else if (discriminant > 0)
        {
            double sqrt_discriminant = sqrt(discriminant);
            *x1 = (-b - sqrt_discriminant) / (2 * a);
            *x2 = (-b + sqrt_discriminant) / (2 * a);
            printf("____discriminant > 0___");
            return TWO_ROOT;
        }
        else
        {
            printf("___no roots___fuck__");
            return NO_ROOT; // Нет действительных корней
        }
    }
}


#include "unit_test.cpp"
// test, цикл 
