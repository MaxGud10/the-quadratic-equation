#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double x_max = 1e-6;

int compare_doubles(double x, double y);


void findRoots(double a, double b, double c);

int main()
{
    double a = 0, b = 0, c = 0;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);
    findRoots(a, b, c); 
    return 0; 
} 

int compare_doubles(double x, double y) 
{
    if (fabs(x - y) < x_max) {
        return 0;  
    }
    return (x < y) ? -1 : 1; 
}

void findRoots(const double a, const double b, const double c)
{
   if (compare_doubles(a, 0) == 0)
   {
        printf("A linear equation is a special case of a quadratic equation\n");
        return;
   }
    double discriminant = b * b - 4 * a * c;

   if (discriminant > 0)
   {
        double sqrt_discriminant = sqrt(discriminant);

        printf("%f\n%f", (-b+sqrt_discriminant)/(2*a), 
        (-b-sqrt_discriminant)/(2*a));
   }

    else if (compare_doubles(discriminant, 0) == 0) 
    {
        printf("%f\n", -(b) / (2 * a));
    } 

    else // discriminant < 0
    {
        double sqrt_discriminant_minus = sqrt(-discriminant);
        double actual_part = -b / (2 * a);
        double imaginary_part = sqrt_discriminant_minus / (2 * a);
        printf("%f+i%f\n%f-i%f\n", actual_part, imaginary_part, actual_part, imaginary_part);

    }
}

