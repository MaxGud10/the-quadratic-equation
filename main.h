#ifndef MAIN_H
#define MAIN_H

enum Mode
{
    NONE       = 0,
    TEST_MODE  = 1,
    HELP_MODE  = 2, 
    SOLVE_MODE = 3
};

static enum Mode process_arguments(int arg_c, const char *arg_v[]);

#endif // MAIN_H