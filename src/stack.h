#ifndef STACK_H
#define STACK_H

struct stack {
    double *items;
    int top;
    char *val;
};

double *update_array(double *old_arr, int new_size);
struct stack *init_stack();
void add_element(double number, struct stack *stack);
double get_top(struct stack *stack);
int isEmpty_s(struct stack *stack);
void destroy(struct stack *stack);
double peek_s(struct stack *stack);
#endif