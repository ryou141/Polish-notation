#include <stdio.h>
#include <string.h>

#include "calculation.h"
#include "dijkstra.h"
#include "draw_graph.h"
/*
 gcc -Wall -Wextra -Werror graph.c stack.c calculation.c draw_graph.c -o \
 graph.out && leaks -atExit \
 -- ./test_calc.out && rm -rf graph.out
 */

void input(char* expression);

int main() {
    char expression[150];
    input(expression);
    char input_copy[150];
    strcpy(input_copy, expression);
    if (validate_expression(input_copy) != 0) {
        printf("Input: %s\n", expression);
        char rpn[100] = "";
        dijkstra_alg(expression, rpn);
        draw_graph(calculate_prosfix, rpn);
    } else
        printf("n/a");
    return 0;
}

void input(char* expression) {
    char c = ' ';
    scanf("%c", &c);
    int i = 0;
    for (; c != '\n' && c != '\0'; i++) {
        expression[i] = c;
        scanf("%c", &c);
    }
    expression[i] = '\0';
}