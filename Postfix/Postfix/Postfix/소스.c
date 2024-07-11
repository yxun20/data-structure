#pragma warning(disable:4996) 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1000 

struct stack {
    int top;
    char data[LEN];
};

void init_stack(struct stack* s) {
    s->top = -1;
}
int is_empty(struct stack* s) {
    return (s->top == -1);
}

int is_full(struct stack* s) {
    return (s->top == (LEN - 1));
}
void push(struct stack* s, char c) {
    if (is_full(s)) {
        printf("Stack saturation error\n");
        exit(1);
    }
    else s->data[++s->top] = c;
}

char pop(struct stack* s) {
    if (is_empty(s)) {
        printf("Stack Blank Error\n");
        exit(1);
    }
    else return s->data[s->top--];
}

int is_operator(char c) {
    return (c == 43 || c == 45 || c == 42 || c == 47);
}

int priority(char c) {
    if (c == 43 || c == 45) return 1;
    else if (c == 42 || c == 47) return 2;
    else return 0;
}

void conversion(char* infix, char* postfix) {
    struct stack s;
    init_stack(&s);
    int len = strlen(infix);
    int p = 0;

    for (int i = 0; i < len; i++) {
        if (infix[i] == 40) {
            push(&s, infix[i]);
        }
        else if (infix[i] == 41) {
            while (s.data[s.top] != 40) {
                postfix[p++] = pop(&s);
            }
            pop(&s);
        }
        else if (is_operator(infix[i])) {
            while (s.top != -1 && s.data[s.top] != 40 && priority(s.data[s.top]) >= priority(infix[i])) {
                postfix[p++] = pop(&s);
            }
            push(&s, infix[i]);
        }
        else {
            postfix[p++] = infix[i];
        }
    }
    while (s.top != -1) {
        postfix[p++] = pop(&s);
    }
    postfix[p] = '\0';
}

int main() {
    FILE* inputFile = fopen("input_hw2.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");
    if (inputFile == NULL) {
        printf("Failed to open input_hw2.txt input file.\n");
        return 0;
    }
    if (outputFile == NULL) {
        printf("Failed to create output.txt output file.\n");
        fclose(inputFile);
        return 0;
    }

    int caseNum;
    fscanf(inputFile, "%d", &caseNum);
    for (int i = 0; i < caseNum; i++) {
        char infix[LEN], postfix[LEN];
        int operandNum;
        fscanf(inputFile, "%d", &operandNum);
        fscanf(inputFile, "%s", infix);
        conversion(infix, postfix);
        fprintf(outputFile, "%s\n", postfix);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}