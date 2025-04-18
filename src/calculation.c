#include "calculation.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 0 - ok, 1 - error
int calculate_prosfix(double *result_val, double x, const char *expression) {
    struct stack *stack = init_stack();
    int f = 0;
    char *token;
    char *expr_copy = strdup(expression);  // copy string to use tokens
    token = strtok(expr_copy, " ");

    while (token != NULL && !f) {
        // if token is a num -> convert & put to stack
        char *endptr;
        double value = strtod(token, &endptr);  // convert symbol to double
        if (*endptr == '\0') {                  // if its a number
            add_element(value, stack);
            // printf("got value '%lf'\n", value);
        } else {  // if its an operaiton
            double result;
            double b, a;

            // printf("got not value '%s'\n", token);

            if (strcmp(token, "x") == 0) {
                // printf("got x=%lf\n", x);
                add_element(x, stack);
            } else if (strcmp(token, "+") == 0) {
                b = get_top(stack);
                a = get_top(stack);
                result = a + b;
            } else if (strcmp(token, "-") == 0) {
                b = get_top(stack);
                a = get_top(stack);
                result = a - b;
            } else if (strcmp(token, "*") == 0) {
                b = get_top(stack);
                a = get_top(stack);
                result = a * b;
            } else if (strcmp(token, "/") == 0) {
                b = get_top(stack);
                a = get_top(stack);
                result = a / b;
            } else if (strcmp(token, "sin") == 0) {
                a = get_top(stack);
                result = sin(a);
            } else if (strcmp(token, "cos") == 0) {
                a = get_top(stack);
                result = cos(a);
            } else if (strcmp(token, "tan") == 0) {
                a = get_top(stack);
                result = tan(a);
            } else if (strcmp(token, "ctg") == 0) {
                a = get_top(stack);
                result = 1.0 / tan(a);
            } else if (strcmp(token, "sqrt") == 0) {
                a = get_top(stack);
                result = sqrt(a);
            } else if (strcmp(token, "ln") == 0) {
                a = get_top(stack);
                result = log(a);
            } else {
                // printf("Unknown operation: %s\n", token);
                f = 1;
            }
            if (!f && strcmp(token, "x") != 0) {
                // printf("added element:%lf\n", result);
                add_element(result, stack);
            }
        }
        if (!f) token = strtok(NULL, " ");
    }

    if (!f) {
        double final_result = get_top(stack);
        *result_val = final_result;
    }

    free(expr_copy);
    destroy(stack);

    return f;
}