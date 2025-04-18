#include <math.h>
#include <stdio.h>

#include "calculation.h"
#include "draw_graph.h"
#include "stack.h"

void print_test(int num, double expected, char* input, int status, double result) {
    if (!status && expected == result)
        printf("[TEST %d] SUCCESS\n\tinput='%s'\n\tresult='%lf'\n", num, input, result);
    else
        printf("[TEST %d] FAILED\n\tinput='%s'\n\tresult='%lf'\n\tExpected='%lf'\n", num, input, result,
               expected);
}

int main() {
    double res;
    int status;
    char* str;

    str = "2 x * cos sin";
    status = calculate_prosfix(&res, 7, str);
    print_test(1, 0.136312, str, status, res);
    if (!status) draw_graph(calculate_prosfix, str);
    printf("\n");

    status = calculate_prosfix(&res, 9, "8 x + 1 -");
    print_test(2, 16, "8 x + 1 -", status, res);

    status = calculate_prosfix(&res, 7, "8 9 + 1 x - *");
    print_test(3, -102, "8 9 + 1 x - *", status, res);

    status = calculate_prosfix(&res, 7, "4 5 *");
    print_test(4, 20, "4 5 *", status, res);

    status = calculate_prosfix(&res, 7, "10 2 /");
    print_test(5, 5, "10 2 /", status, res);

    status = calculate_prosfix(&res, 7, "3 7 + 8 +");
    print_test(6, 18, "3 7 + 8 +", status, res);

    status = calculate_prosfix(&res, 7, "9 3 - 1 +");
    print_test(7, 7, "9 3 - 1 +", status, res);

    status = calculate_prosfix(&res, 7, "2 3 + 5 *");
    print_test(8, 25, "2 3 + 5 *", status, res);

    status = calculate_prosfix(&res, 7, "2 3 + 5 /");
    print_test(9, 1, "2 3 + 5 /", status, res);

    status = calculate_prosfix(&res, 2, "1 2 3 + +");
    print_test(10, 6, "1 2 3 + +", status, res);

    status = calculate_prosfix(&res, 0, "2 sin");
    print_test(11, sin(2.0) * 100, "2 sin", status, res * 100);

    status = calculate_prosfix(&res, 0, "0 cos");
    print_test(12, 1, "0 cos", status, res);

    status = calculate_prosfix(&res, 0, "0 tan");
    print_test(13, 0, "0 tan", status, res);

    status = calculate_prosfix(&res, 0, "1 ln");
    print_test(14, 0, "1 ln", status, res);

    status = calculate_prosfix(&res, 0, "4 sqrt");
    print_test(15, 2, "4 sqrt", status, res);

    status = calculate_prosfix(&res, 2, "1 x ctg");
    print_test(16, 1.0 / tan(2.0), "1 x ctg", status, res);

    status = calculate_prosfix(&res, 7, "8 2 3 + *");
    print_test(17, 8 * (2 + 3), "8 2 3 + *", status, res);

    status = calculate_prosfix(&res, 7, "10 5 2 + -");
    print_test(18, 3, "10 5 2 + -", status, res);

    status = calculate_prosfix(&res, 7, "5 3 4 * +");
    print_test(19, 5 + (3 * 4), "5 3 4 * +", status, res);

    status = calculate_prosfix(&res, 7, "1 2 3 + 4 + *");
    print_test(20, 1 * (2 + 3 + 4), "1 2 3 + 4 + *", status, res);

    return 0;
}