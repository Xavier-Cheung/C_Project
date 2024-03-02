#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 80

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

void push(Stack* s, char value) {
    if (s->top < MAX_SIZE - 1) {
        s->data[++(s->top)] = value;
    }
}

char pop(Stack* s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    }
    return '\0';  // Stack is empty
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initStack(&s);

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        char token = infix[i];
        if (isdigit(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (s.top >= 0 && s.data[s.top] != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s);  // Pop '('
        } else if (isOperator(token)) {
            while (s.top >= 0 && precedence(s.data[s.top]) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }

        i++;
    }

    while (s.top >= 0) {
        postfix[j++] = pop(&s);
    }

    postfix[j] = '\0';  // Null-terminate the postfix expression
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
