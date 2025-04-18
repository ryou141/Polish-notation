#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

char *dijkstra_alg(char *str, char rpn[]) {
    struct stack *operatorStack = init_stack();
    Queue outputQueue;
    init_queue(&outputQueue);

    char *token = strtok(str, " ");
    char *prevToken = NULL;

    while (token != NULL) {
        if (is_digit(token[0]) || (token[0] == '-' && (is_digit(token[1]) || token[1] == '.'))) {
            enqueue(&outputQueue, atof(token));
        } else if (strcmp(token, "x") == 0) {
            double op = operatorToDouble(token);
            enqueue(&outputQueue, op);
        } else if (is_function(token)) {
            double op = operatorToDouble(token);
            add_element(op, operatorStack);
            add_element(0, operatorStack);
        } else if (is_operator(token)) {
            if (strcmp(token, "-") == 0 &&
                (prevToken == NULL || (is_operator(prevToken) && strcmp(prevToken, ")") != 0))) {
                add_element(-11.0, operatorStack);
            } else {
                double op = operatorToDouble(token);
                while (!isEmpty_s(operatorStack) && precedence(peek_s(operatorStack)) >= precedence(op)) {
                    enqueue(&outputQueue, get_top(operatorStack));
                }
                add_element(op, operatorStack);
            }
        } else if (strcmp(token, "(") == 0) {
            add_element(0, operatorStack);
        } else if (strcmp(token, ")") == 0) {
            while (!isEmpty_s(operatorStack) && peek_s(operatorStack) != 0) {
                enqueue(&outputQueue, get_top(operatorStack));
            }
            get_top(operatorStack);
            if (!isEmpty_s(operatorStack) && is_function(doubleToOperator(peek_s(operatorStack)))) {
                enqueue(&outputQueue, get_top(operatorStack));
            }
        }

        prevToken = token;
        token = strtok(NULL, " ");
    }

    while (!isEmpty_s(operatorStack)) {
        enqueue(&outputQueue, get_top(operatorStack));
    }

    while (!isEmpty(&outputQueue)) {
        double val = dequeue(&outputQueue);
        if (val < 0) {
            strcat(rpn, doubleToOperator(val));
            strcat(rpn, " ");
        } else if (val != 0) {
            char str_temp[50];
            sprintf(str_temp, "%.2f", val);
            strcat(rpn, str_temp);
            strcat(rpn, " ");
        }
    }

    destroy(operatorStack);

    return rpn;
}

int is_operator(char *token) {
    return (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 ||
            strcmp(token, "/") == 0);
}

int precedence(double token) {
    int flag = 0;
    switch ((int)token) {
        case -1:  // +
        case -2:  // -
            flag = 1;
            break;
        case -3:  // *
        case -4:  // /
            flag = 2;
            break;
        case -5:   // sin
        case -6:   // cos
        case -7:   // sqrt
        case -8:   // tan
        case -9:   // ctg
        case -10:  // ln
        case -11:  // minus
            flag = 3;
            break;
        default:
            flag = 0;
    }
    return flag;
}

int is_function(char *token) {
    return (strcmp(token, "sin") == 0 || strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0 ||
            strcmp(token, "ctg") == 0 || strcmp(token, "sqrt") == 0 || strcmp(token, "ln") == 0);
}

int is_digit(char c) { return c >= '0' && c <= '9'; }

char *doubleToOperator(double value) {
    static char str[50];
    const char *result;
    if ((int)value < 0) {
        switch ((int)value) {
            case -1:
                result = "+";
                break;
            case -2:
                result = "-";
                break;
            case -3:
                result = "*";
                break;
            case -4:
                result = "/";
                break;
            case -5:
                result = "sin";
                break;
            case -6:
                result = "cos";
                break;
            case -7:
                result = "sqrt";
                break;
            case -8:
                result = "tan";
                break;
            case -9:
                result = "ctg";
                break;
            case -10:
                result = "ln";
                break;
            case -11:
                result = "-";
                break;
            case -16:
                result = "x";
                break;
            default:
                result = "?";
                break;
        }
    } else {
        sprintf(str, "%.2f", value);
        result = str;
    }
    return (char *)result;
}

double operatorToDouble(char *token) {
    double res;
    if (strcmp(token, "+") == 0)
        res = -1.0;
    else if (strcmp(token, "-") == 0)
        res = -2.0;
    else if (strcmp(token, "*") == 0)
        res = -3.0;
    else if (strcmp(token, "/") == 0)
        res = -4.0;
    else if (strcmp(token, "sin") == 0)
        res = -5.0;
    else if (strcmp(token, "cos") == 0)
        res = -6.0;
    else if (strcmp(token, "sqrt") == 0)
        res = -7.0;
    else if (strcmp(token, "tan") == 0)
        res = -8.0;
    else if (strcmp(token, "ctg") == 0)
        res = -9.0;
    else if (strcmp(token, "ln") == 0)
        res = -10.0;
    else if (strcmp(token, "x") == 0)
        res = -16.0;
    else
        res = atof(token);
    return res;
}

int validate_expression(char *str) {
    int openBrackets = 0;
    char *token = strtok(str, " ");
    char *prevToken = NULL;
    int valid = 1;

    while (token != NULL && valid == 1) {
        if (is_digit(token[0]) || (token[0] == '-' && (is_digit(token[1]) || token[1] == '.')) ||
            strcmp(token, "x") == 0) {
            if (prevToken != NULL && (is_digit(prevToken[0]) || strcmp(prevToken, "x") == 0)) {
                valid = 0;
            }
        } else if (is_operator(token)) {
            if (prevToken == NULL || is_operator(prevToken) || strcmp(prevToken, "(") == 0) {
                valid = 0;
            }
        } else if (is_function(token)) {
            if (prevToken != NULL && !is_operator(prevToken) && strcmp(prevToken, "(") != 0) {
                valid = 0;
            }
        } else if (strcmp(token, "(") == 0) {
            openBrackets++;
            if (prevToken != NULL && (is_digit(prevToken[0]) || strcmp(prevToken, "x") == 0)) {
                valid = 0;
            }
        } else if (strcmp(token, ")") == 0) {
            openBrackets--;
            if (openBrackets < 0 || prevToken == NULL || is_operator(prevToken) ||
                strcmp(prevToken, "(") == 0) {
                valid = 0;
            }
        } else {
            valid = 0;
        }
        prevToken = token;
        token = strtok(NULL, " ");
    }
    if (openBrackets != 0 || (prevToken != NULL && is_operator(prevToken))) {
        valid = 0;
    }

    return valid;
}
