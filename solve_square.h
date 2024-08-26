#ifndef SOLVE_SQUARE_H
#define SOLVE_SQUARE_H

enum N_ROOTS 
{ 
    NO_ROOT, 
    ONE_ROOT, 
    TWO_ROOT,
    INF_ROOTS
};

enum N_ROOTS solve_square(double a, double b, double c, double *x1, double *x2);

#endif