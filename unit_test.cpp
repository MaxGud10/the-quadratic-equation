int unit_test( struct str_test data, int test_number)
{
    double x1 =0 , x2 = 0;
    enum nRoots number_roots = solve_square(data.a, data.b, data.c, &x1, &x2);

    if (compare_doubles(number_roots, data.number_roots_expected) != 0 || 
        compare_doubles(x1, data.x1_expect) != 0 || 
        compare_doubles(x2, data.x2_expect) != 0)
        {
            printf("Error %d: a = %lf b = %lf, c = %lf,  number_roots = %d: x1 = %lf, x2 = %lf\n"
                    "Expected %d: number_roots = %d: x1 = %lf, x2 = %lf\n", 
                    test_number, data.a, data.b, data.c, number_roots, x1, x2, 
                    test_number, data.number_roots_expected, data.x1_expect, data.x2_expect);
            return 1;
        }
    return 0;
}
