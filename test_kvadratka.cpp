#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <math.h>

#include "test_kvadratka.h"
#include "utils_kvadratka.h"
#include "color.h"

int run_test(const struct StrTest data [DATA_NUMBER])
{
    assert(data != nullptr);
    for (int i = 0; i < DATA_NUMBER; i++)
    {
        unit_test(data[i], i);
        return 0;
    }
    return 0;
}

int unit_test(struct StrTest data, int test_number)
{
    double x1 = NAN , x2 = NAN;
    enum NRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
    {
            if (compare_doubles(x1, data.x2_expect) == 0 ||
                compare_doubles(x2, data.x1_expect) == 0) // проверка на совпадающие корни 
            { 
            printf(DRAW_TEXT(YELLOW,"All right\n"));
            }
            else
            {
                printf("Error %d: a = %lf b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf\n"
                       "Expected %d: number_roots = %d: x1 = %lf, x2 = %lf\n", 
                        test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                        test_number, data.number_roots_expected, data.x1_expect, data.x2_expect);
                    return 1;
            }
    }
    return 0;
}

int offer_test(char *word, const struct StrTest data [DATA_NUMBER])
{   
    assert(data != nullptr);
    scanf("%s", word); 

    if (strcmp (word, "Yes") == 0 || 
        strcmp (word, "yes") == 0)
    {
        run_test(data);
        return 0;
    }
    else if (strcmp (word, "No") == 0 || 
             strcmp (word, "no") == 0) 
    {
        printf(DRAW_TEXT(RED,"Exiting the program.\n"));
        return 0;
    }
    else printf(DRAW_TEXT(RED,"Invalid input, exiting.\n"));
    return 0;
}