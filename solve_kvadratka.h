#ifndef SOLVE_KVADRATKA_H
#define SOLVE_KVADRATKA_H

static const int ARRAY_LENGTH = 40;
static const int DATA_NUMBER = 9; 

enum NRoots 
{ 
    NO_ROOT, 
    ONE_ROOT, 
    TWO_ROOT,
    INF_ROOTS
};

struct StrTest 
{ 
    double a, b, c;
    double x1_expect, x2_expect;
    enum NRoots number_roots_expected; 
};

enum NRoots solve_square(double a, double b, double c, double *x1, double *x2);

int check_input(double *a, double *b, double *c);

int general_solution(double a, double b, double c, double *x1, double *x2, const StrTest data [DATA_NUMBER]);

int linear_equation(double b, double c, double *x1);

int root_printing(int findRoots, double* x1, double* x2);

#endif