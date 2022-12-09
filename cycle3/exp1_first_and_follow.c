#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "common.h"
#define and &&
#define OFFSET 20
void remove_left_recursion(){
    for(int i=0;i<grammar_length;i++){
        if(grammar[i][0] == grammar[i][2]){
            printf("\nLeft recursive grammar found: %s",grammar[i]);
            for(int j=0;j<grammar_length;j++){
                if(j!=i and grammar[j][0]==grammar[i][0]){
                    printf("\nFinding the other grammers: %s",grammar[j]);
                    sprintf(grammar[j],"%c=%s%c",grammar[j][0],split(grammar[j],2, strlen(grammar[j])),grammar[j][0]+OFFSET);
                  //  printf("\n new grammer: %s",grammar[j]);

                }
            }
            grammar_length++;
            sprintf(grammar[grammar_length-1],"%c=e",grammar[i][0]+OFFSET);
            sprintf(grammar[i],"%c=%s%c",grammar[i][0]+OFFSET, split(grammar[i],3, strlen(grammar[i])),grammar[i][0]+OFFSET);
            printf("\nNEW GRAMMAR:");
            for(int k=0;k<grammar_length;k++){
                printf("\n[%d]%s",k,grammar[k]);
            }

        }
    }}
int main(){
    grammar_length = 9;
    strcpy(grammar[0], "E=TX");
    strcpy(grammar[1], "X=+TX+");
    strcpy(grammar[2], "X=e");
    strcpy(grammar[3], "T=TY");
    strcpy(grammar[4], "Y=*FY");
    strcpy(grammar[5], "Y=e");
    strcpy(grammar[6], "F=(E)");
    strcpy(grammar[7], "F=i");
    strcpy(grammar[8], "T=+");
//    remove_left_recursion();
    char symbols[5] = "ETXF";
	for(int i=0;i< strlen(symbols);i++){
        printf("\n First of(%c): [",symbols[i]);
        firstof(symbols[i],false,'E');
        printf("]");
    }
    for(int i=0;i< strlen(symbols);i++){
        printf("\n Follow of(%c): [", symbols[i]);
        followof(symbols[i]);
        printf(" ]");
    }



	
}
