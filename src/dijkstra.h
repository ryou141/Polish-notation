#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int is_operator(char *token);
int precedence(double token);
int is_function(char *token);
int is_digit(char c);
char *doubleToOperator(double value);
double operatorToDouble(char *token);
char *dijkstra_alg(char *str, char rpn[]);
int validate_expression(char *str);

#endif