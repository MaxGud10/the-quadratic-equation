#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void findRoots(double a, double b, double c);
int main()
{
    double a, b,c;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);
    findRoots(a, b, c); 
    return 0; 
} 
void findRoots(double a, double b, double c)
{
   if (a == 0) 
   {
        printf("invalid\n");
        return;
   }
    double d = b * b - 4 * a * c;

   if (d > 0)
   {
        double sqrt_d = sqrt(d);
        printf("%f\n%f", (double)(-b+sqrt_d)/(2*a), (double)(-b-sqrt_d)/(2*a));
   }
    else if (d == 0)
    {
        printf("%f", -(double)b/(2*a));
    }
    else // d < 0
    {
        double sqrt_d_minus = sqrt(-d);
        printf("%f+i%f\n%f-i%f", -(double)b/(2*a), sqrt_d_minus/(2*a), -(double)b/(2*a), sqrt_d_minus/(2*a));

    }
}

