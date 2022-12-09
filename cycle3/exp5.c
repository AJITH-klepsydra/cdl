#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "common.h"
struct _map{
    char lhs;
    char value[100];
};
int top=0;
char stack[10];
struct _map map[100];
int main(){
    strcpy(stack,"a+b*c");

    char n = 5;
    char operators[2]="*+";
    for(int i=0;i< strlen(operators);i++){
        for(int j=0;j<n;j++){
            if(stack[j]==operators[i]){

                printf("\n%c=%s\n",stack[j-1]+15, split(stack,j-1,j+2));
            }
            //printf("\n%s\n",stack;
        }
    }
}


