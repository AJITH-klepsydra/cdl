#include<stdio.h>
#include<stdlib.h>
#include "common.h"
#include<string.h>
#include <stdbool.h>

char input_buffer[10];
char stack[20];
int top = -1;
int b_ptr = 0;

char pop() {
    if (top >= 0) {
        char ret = stack[top];
        top--;
        return ret;
    }
    return -1;
}
void push(char symb) {
    top++;
    stack[top] = symb;

}
void empty(){
    while(pop() !=-1){
    }
}
void reduce(char symbol, bool all) {
    if(!all) {
        pop();
        push(symbol);
    }
    else{
        empty();
        push(symbol);
    }

}
char *stacktop(int j) {
    int k = 0;
    char *ret = malloc(sizeof(char) * top + 1);
    for (int i = j; i < top + 1; i++) {
        ret[k] = stack[i];
        k++;
    }
    return ret;
}

bool accept() {
    if (!strcmp(stacktop(1), "S") && input_buffer[b_ptr] == '$' && strlen(stack)==2) {
        return true;
    }
    return false;
}

bool error() {
    if (stack[top] == '$') {
        return true;
    }
    return false;
}

void shift() {
    push(input_buffer[b_ptr]);
    b_ptr++;
}

int main() {
    grammar_length = 3;
    strcpy(grammar[0], "S=S+S");
    strcpy(grammar[1], "S=S*S");
    strcpy(grammar[2], "S=i");
    strcpy(input_buffer, "i+i*i$");
    push('$');

    b_ptr = 0;
    bool flag = true;
    while (flag || (!accept() && !error())) {
        flag = false;
        printf("\nstack top: %s(%c), input top: %c", stacktop(1),stack[top], input_buffer[b_ptr]);
        if (stack[top]=='S'   && input_buffer[b_ptr]=='$') {
            printf("\n\nInput Accepted\n");
            exit(0);
        }
        bool reduce_var = false;
        for (int i = 0; i < grammar_length; i++) {
            char *rhs = split(grammar[i], 2, strlen(grammar[i]));
            char *top_stack = malloc(sizeof(char)*1);
            sprintf(top_stack,"%c",stack[top]);

            if (!strcmp(rhs, top_stack)) {
                printf("\nReducing with [%s]", grammar[i]);
                reduce(grammar[i][0],false);
                reduce_var = true;
            }
            else{
                if (!strcmp(rhs, stacktop(1))) {
                    printf("\nReducing with [%s]", grammar[i]);
                    reduce(grammar[i][0],true);
                    reduce_var = true;
                }
            }
        }
        if (!reduce_var) {
            shift();
        }
    }
    printf("\n\nInput Rejected\n");


}
