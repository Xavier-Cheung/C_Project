#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
#include<ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    double data[MAX_STACK_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, double value) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = value;
    }
}

double pop(Stack* s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return 0.0;  // Stack is empty
}

double calculate(double operand1, double operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        default:
            return 0.0;
    }
}

int main() {
    Stack s;
    initStack(&s);

    char input[100];
    printf("Enter the reverse Polish expression: ");
    fgets(input, sizeof(input), stdin);

    char* token = strtok(input, " \t\n");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            // Token is a number
            double operand = atof(token);
            push(&s, operand);
        } else if (token[0] == 's' && token[1] == 'i' && token[2] == 'n') {
            // Token is sin function
            double operand = pop(&s);
            push(&s, sin(operand));
        } else if (token[0] == 'c' && token[1] == 'o' && token[2] == 's') {
            // Token is cos function
            double operand = pop(&s);
            push(&s, cos(operand));
        } else if (token[0] == 'e' && token[1] == 'x' && token[2] == 'p') {
            // Token is exp function
            double operand = pop(&s);
            push(&s, exp(operand));
        } else if (token[0] == 'p' && token[1] == 'o' && token[2] == 'w') {
            // Token is pow function
            double operand2 = pop(&s);
            double operand1 = pop(&s);
            push(&s, pow(operand1, operand2));
        } else {
            // Token is an operator
            double operand2 = pop(&s);
            double operand1 = pop(&s);
            push(&s, calculate(operand1, operand2, token[0]));
        }

        token = strtok(NULL, " \t\n");
    }

    double result = pop(&s);
    printf("Result: %f\n", result);

    return 0;
}
