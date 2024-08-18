#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void findRoots(int a, int b, int c) 
{
   if (a == 0) 
   {
        printf("invalid");
        return;
   }
        int d = b*b - 4*a*c;
        double sqrt_d = sqrt(d);

   if (d > 0)
   {
        printf("%f\n%f", (double)(-b+sqrt_d)/(2*a), (double)(-b-sqrt_d)/(2*a));
   }
    else if (d == 0)
    {
        printf("%f", -(double)b/(2*a));
    }
    else // d < 0
    {
        printf("%f+i%f\n%f-i%f", -(double)b/(2*a), sqrt_d/(2*a), -(double)b/(2*a), sqrt_d/(2*a));

    }
}

int main()
{
    double a, b,c;
    scanf("%lf", &a);
    scanf("%lf", &b);
    scanf("%lf", &c);
    findRoots(a, b, c); 
    return 0; 
}