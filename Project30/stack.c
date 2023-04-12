#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s)
{
    s->top = -1;
}

int is_empty(StackType* s)
{
    return (s->top == -1);
}

int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else {
        return s->data[(s->top)--];
    }
}

int is_digit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

int eval(char exp[])
{
    int op1, op2, value, i = 0;
    char ch;
    StackType s;
    init_stack(&s);
    while ((ch = exp[i++]) != '\0') {
        if (is_digit(ch)) {
            value = ch - '0';
            push(&s, value);
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            default: fprintf(stderr, "ERROR :다른 입력 발생.\n");
                return;
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    char exp[MAX_STACK_SIZE];
    int result;
    int c, i = 0;
    printf("postfix expression: ");
    while ((c = getchar()) != '\n' && i < MAX_STACK_SIZE - 1) {
        exp[i++] = c;
    }
    exp[i] = '\0';
    result = eval(exp);
    printf("result: %d\n", result);
    return 0;
}