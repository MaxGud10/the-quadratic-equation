#ifndef TEST_H
#define TEST_H

#include "solve_square.h"
static const int DATA_NUMBER = 9;

struct str_test 
{ 
    double a, b, c;
    double x1_expect, x2_expect;
    enum N_ROOTS number_roots_expected; 
};

int run_test(const struct str_test data [DATA_NUMBER]);

int offer_test(char *word, const struct str_test data [DATA_NUMBER]);

int unit_test(struct str_test data, int test_number);

#endif