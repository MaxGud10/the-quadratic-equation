#include <stddef.h>
#include <assert.h>
#include <math.h>

#include "utils.h"

#include "solve_square.h"

enum N_ROOTS solve_square(double a, double b, double c, double *x1, double *x2)
{   
    assert(isfinite (a));
    assert(isfinite (b));
    assert(isfinite (c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);
    if (compare_doubles(a, 0) == 0)
    {   
        if (compare_doubles(b, 0) == 0)
        {
            return (compare_doubles(c, 0) == 0) ? INF_ROOTS : NO_ROOT; // TODO: в отдельную функцию 
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