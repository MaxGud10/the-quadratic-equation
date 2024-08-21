#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SS_INF_ROOTS 3  // Определяем константу для бесконечного числа корней
const double x_min = 1e-6;
enum nRoots {number ,number1, number2, number3, number4, number5, number6 }; // именнованная константа, для 

int solve_square(double a, double b, double c, double *x1, double *x2);
int compare_doubles(double x1, double x2);
int all_test(double a, double b, double c, double x1_expect, double x2_expect, int number_roots_expected);

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

    double x1 = NAN, x2 = NAN;
    int findRoots = solve_square(a, b, c, &x1, &x2);

    switch(findRoots)
    {
        case 0: 
            printf("No roots\n");
            break;

        case 1: 
            printf("x = %lf\n", x1);
            break;
    
        case 2: 
            printf("x1 = %lf and x2 = %lf\n", x1, x2);
            break;

        case SS_INF_ROOTS: 
            printf("Any number\n");
            break;

        default: 
            printf("main(): ERROR: findRoots = %d\n", findRoots);
            return 1;
    }

    //тесты
    all_test(1, -3, 2, 2, 1, 2);  // (x - 2)(x - 1) = 0 --> корни 1,2
    all_test(1, -5, 6, 3, 3, 2);   // (x - 3)(x - 2) = 0 -> корни 2, 3
    all_test(1, 2, 1, -1, -1, 0);  // (x + 1)^2 = 0 -> корень -1
    all_test(1, 0, -1, -1, 1, 2);  // (x - 1)(x + 1) = 0 -> корни -1, 1
    all_test(1, 0, 0, 0, 0, 1);    // x = 0 -> корень 0
    all_test(1, 4, 4, -2, -2, 1);   // (x + 2)^2 = 0 -> корень -2
    all_test(0, 2, -4, 2, 2, 0);    // 2x = 4 -> корень 2

    return 0;
}

int compare_doubles(double x1, double x2) 
{
    return (fabs(x1 - x2) < x_min) ? 0 : (x1 < x2) ? -1 : 1; 
}

int solve_square(double a, double b, double c, double *x1, double *x2)
{
    if (compare_doubles(a, 0) == 0)
    {
        if (compare_doubles(b, 0) == 0)
        {
            return (compare_doubles(c, 0) == 0) ? SS_INF_ROOTS : 0;
        }
        else 
        {
            *x1 = -c / b;
            return 1;
        }
    }
    else 
    {
        double discriminant = b * b - 4 * a * c;

        if (compare_doubles(discriminant, 0) == 0)
        {
            *x1 = *x2 = -b / (2 * a);
            return 1;
        }
        else if (discriminant > 0)
        {
            double sqrt_discriminant = sqrt(discriminant);
            *x1 = (-b - sqrt_discriminant) / (2 * a);
            *x2 = (-b + sqrt_discriminant) / (2 * a);
            return 2;
        }
        else
        {
            return 0; // Нет действительных корней
        }
    }
}

int all_test(double a, double b, double c, double x1_expect, double x2_expect, int number_roots_expected)
{
    double x1 = 0, x2 = 0;
    int number_roots = solve_square(a, b, c, &x1, &x2);
    
    if (compare_doubles(number_roots, number_roots_expected) != 0 || 
        compare_doubles(x1, x1_expect) != 0 || 
        compare_doubles(x2, x2_expect) != 0)
        {
            printf("ErrorTest: a = %lf, b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf "
               "Expected number_roots = %d: x1 = %lf, x2 = %lf\n", 
               a, b, c, number_roots, x1, x2, number_roots_expected, x1_expect, x2_expect);
        return 1;
        }
    return 0;
}