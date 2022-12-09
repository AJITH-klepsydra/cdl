#include<stdio.h>
#include<stdlib.h>
#include "common.h"
#include<string.h>
#include <stdbool.h>

char input_buffer[10];
char stack[20];
int top = 0;
int b_ptr;
char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}
char *get_stack_value() {
    int k = 0;
    char *ret = malloc(sizeof(char) * top);
    for (int i = 1; i < top; i++) {
        ret[k] = stack[i];
        k++;
    }
    return ret;
}

void add_to_stack(char symb) {
    stack[top] = symb;
    top++;

}



void shift() {
    printf("\n# input: %s: stack:%s: it: %c: st: %c\n",input_buffer,stack,input_buffer[b_ptr],stack[top-1]);
    add_to_stack(input_buffer[b_ptr]);
    b_ptr++;

}
bool error(){
    if(!strlen(input_buffer) && strlen(stack)){
        printf("\nERROR");
        return true;
    }
    return  false;
}
bool accept() {
    bool flag = true;
    if(strlen(stack)<2){
        return false;
    }
    if(!strcmp("$S$",stack)){
        printf("\nACCEPTED\n");
        printf("%s",stack);
        return true;
    }
    return false;
}

void reduce(char nonter) {
    top--;
    add_to_stack(nonter);

}

void reduce_complex(char *repl,char nonter) {
    char *with = malloc(sizeof(char)*1);
    sprintf(with,"%c",nonter);
    strcpy(stack,str_replace(stack,repl,with));
    printf("\n New Stack: %s",stack);
    top = strlen(stack);
    //printf("\nstack top: %c",stack[top]);

}

int main() {
    grammar_length = 3;
    strcpy(grammar[0], "S=S+S");
    strcpy(grammar[1], "S=S*S");
    strcpy(grammar[2], "S=i");
    strcpy(input_buffer, "i*$");
    add_to_stack('$');
    b_ptr = 0;
    while (!accept()) {
        printf("\ninput buffer: %c,stack top: %s", input_buffer[b_ptr], get_stack_value());
        char *stack_top = get_stack_value();

        bool flag = false, no_shift = false;
        for (int i = 0; i < grammar_length; i++) {
            char *rhs = split(grammar[i], 2, strlen(grammar[i]));
            if (!strcmp(rhs, stack_top)) {
                printf("\nMatch found %s(%s)[%s]", rhs, stack_top, grammar[i]);
                reduce(grammar[i][0]);


            } else if (rhs[0] == stack_top[strlen(stack_top) - 1]) {
                printf("\nUnique Match %s(%c)", rhs, stack_top[strlen(stack_top) - 1]);
                reduce(grammar[i][0]);


            } else if (!strcmp(rhs, split(stack_top, 0, strlen(stack_top) - 1))) {
                printf("\nNew match found :%s", split(stack_top, 0, strlen(stack_top) - 1));
                reduce_complex(split(stack_top, 0, strlen(stack_top) - 1),grammar[i][0]);
            } else {
                //printf("\n:::%s:::%c",rhs,stack_top[strlen(stack_top)-1]);
                flag = true;
            }

        }
        if (flag) {
            shift();
        }

    }


}

