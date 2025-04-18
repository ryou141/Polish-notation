#include "stack.h"

#include <stdlib.h>

// upgrades array with new size by allocate new memory and free old array
double *update_array(double *old_arr, int new_size) {
    double *new_arr = (double *)malloc(new_size * sizeof(double));
    for (int i = 0; i < new_size; i++) {
        new_arr[i] = old_arr[i];
    }
    free(old_arr);

    return new_arr;
}

// init empty stack
struct stack *init_stack() {
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    double *items = (double *)malloc(0 * sizeof(double));
    stack->items = items;
    stack->top = -1;
    return stack;
}

// add one element to top of stack
void add_element(double number, struct stack *stack) {
    double *new_items = update_array(stack->items, stack->top + 2);
    stack->items = new_items;
    stack->items[++stack->top] = number;
}

// get top from stack and downgrade size of it
double get_top(struct stack *stack) {
    double number = -1.0;
    if (stack->top >= 0) {
        number = stack->items[stack->top];
        double *new_items = update_array(stack->items, stack->top);
        stack->items = new_items;
        stack->top--;
    }
    return number;
}
int isEmpty_s(struct stack *stack) { return stack->top == -1.0; }
double peek_s(struct stack *stack) {
    double res;
    if (stack->top == -1.0) {
        res = -1.0;
    } else
        res = stack->items[stack->top];
    return res;
}

void destroy(struct stack *stack) {
    free(stack->items);
    free(stack);
}