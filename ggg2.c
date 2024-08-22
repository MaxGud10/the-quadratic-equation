#include <stdio.h>
#include <stdlib.h>
#include <math.h>

  // Определяем константу для бесконечного числа корней
const double x_min = 1e-6;

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
int all_test(struct str_test data, int test_number);// TODO сделать  numtintest_number

int main(void)
{
    printf("Square equation solver\n");
    printf("Enter a, b, c:\n");

    double a = NAN, b = NAN, c = NAN;
    if(scanf("%lf%lf%lf", &a, &b, &c) != 3)
    { 
        printf("Error\n");
        return 0;
    }
    // TODO сделать цикл, чтобы он защищал от неправильного ввода

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

    struct str_test data1 = {1, -3, 2, 1, 2, TWO_ROOT};  // (x - 2)(x - 1) = 0 --> корни 1, 2
    all_test(data1, 1);

    struct str_test data2 = {1, -5, 6, 2, 3, TWO_ROOT};   // (x - 3)(x - 2) = 0 -> корни 2, 3
    all_test(data2, 2);

    struct str_test data3 = {1, 2, -1, -1, -1, ONE_ROOT};  // (x + 1)^2 = 0 -> корень -1
    all_test(data3, 3);

    struct str_test data4 = {1, 0, -1, -1, 1, TWO_ROOT};  // (x - 1)(x + 1) = 0 -> корни -1, 1
    all_test(data4, 4);
 
    struct str_test data5 = {1, 0, 0, 0, 0, ONE_ROOT};    // x = 0 -> корень 0
    all_test(data5, 5);

    struct str_test data6 = {1, 4, 4, -2, -2, ONE_ROOT};   // (x + 2)^2 = 0 -> корень -2
    all_test(data6, 6);

    struct str_test data7 = {2, -4, 2, 2, 2, ONE_ROOT};    // 2x = 4 -> корень 2
    all_test(data7, 7);
   


    //тесты
    /*all_test(1 ,1, -3, 2, 2, 1, TWO_ROOT);  // (x - 2)(x - 1) = 0 --> корни 1, 2
    all_test(2 ,1, -5, 6, 3, 2, TWO_ROOT);   // (x - 3)(x - 2) = 0 -> корни 2, 3
    all_test(3 ,1, 2, 1, -1, -1, ONE_ROOT);  // (x + 1)^2 = 0 -> корень -1
    all_test(4, 1, 0, -1, -1, 1, TWO_ROOT);  // (x - 1)(x + 1) = 0 -> корни -1, 1
    all_test(5 ,1, 0, 0, 0, 0, ONE_ROOT);    // x = 0 -> корень 0
    all_test(6 ,1, 4, 4, -2, -2, ONE_ROOT);   // (x + 2)^2 = 0 -> корень -2
    all_test(7 ,0, 2, -4, 2, 2, ONE_ROOT);    // 2x = 4 -> корень 2*/

    

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

/*int all_test(int test_number, double a, double b, double c, double x1_expect, double x2_expect, int number_roots_expected)
{
    double x1 = NAN, x2 = NAN;
    enum nRoots number_roots = solve_square(a, b, c, &x1, &x2);
    
    if (compare_doubles(number_roots, number_roots_expected) != 0 || 
        compare_doubles(x1, x1_expect) != 0 || 
        compare_doubles(x2, x2_expect) != 0)
        {
            printf("ErrorTest %d: a = %lf, b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf "
                   "Expected number_roots = %d: x1 = %lf, x2 = %lf\n", 
                    test_number, a, b, c, number_roots, x1, x2, number_roots_expected, x1_expect, x2_expect);
        return 1;
        }
    return 0;
}*/

int all_test( struct str_test data, int test_number )
{
    double x1 =NAN, x2 = NAN;
    enum nRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
        {
            printf("Error %d: a = %lf, b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf\n"
                    "Expected number_roots = %d: x1 = %lf, x2 = %lf\n", 
                    test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                    data.number_roots_expected, data.x1_expect, data.x2_expect);
            return 1;
        }
    return 0;
}
