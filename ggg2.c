#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SS_INF_ROOTS 3  // Определяем константу для бесконечного числа корней
const double x_min = 1e-6;

int solve_square(double a, double b, double c, double *x1, double *x2);
int compare_doubles(double x1, double x2);


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

    return 0;  // Возвращаем 0, чтобы указать на успешное завершение
} // TODO: enum читать в Прате

int compare_doubles(double x1, double x2) 
{
    if (fabs(x1 - x2) < x_min) {
        return 0;  
    }
    return (x1 < x2) ? -1 : 1; 
}

int solve_square(double a, double b, double c, double *x1, double *x2)
{
    if (compare_doubles(a, 0) == 0)
    {
        if (compare_doubles(b,0) == 0)
        {
            return (compare_doubles(c,0) == 0) ? SS_INF_ROOTS : 0;
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

        if (compare_doubles(discriminant,0) == 0)
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

int all_test (double a, double b, double c, double x1_expect, double x2_expect, int number_roots_expected)
{
    double x1 = 0, x2 = 0;
    int number_roots = solve_square( a, b, c, &x1, &x2);
    if (number_roots != number_roots_expected || x1 !=x1_expect || x2 != x2_expect ) // TODO: findRoots -> number_roots
    {
        printf("ErrorTest 1: a = %lf, b = %lf, c =%lf,  number_roots = %d: x1 = %lf, x2 = %lf"
               "Expected number_roots = %d: x1 = %lf, x2 = %lf\n", a, b, c, number_roots, x1, x2, number_roots_expected, x1_expect, x2_expect);
        return 1; 

    }
}

/*int fist_test (void)
{
    double x1 = 0, x2 = 0;

    int findRoots = solve_square(1, 2, -3, &x1, &x2); 
    if (findRoots != findRoods_expect || x1 != x1_expect
}*/