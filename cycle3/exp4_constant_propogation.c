#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "common.h"
struct _map{
    char lhs;
    char value[100];
};
struct _map map[100];
int top=0;
char statements[10][100];
int statement_length;
bool is_delimiter(char letter){
    if(letter=='+' || letter=='=' || letter =='-' || letter=='*' || letter=='/' || letter=='(' || letter==')'){
        return true;
    }
    return false;
}
char *find_from_map(char *lhs){
    for(int i=0;i<top;i++){

        if(map[i].lhs == lhs[0]){
            return map[i].value;
        }
    }
    return lhs;
}
int main(){
    statement_length=4;
    strcpy(statements[0],"a=30");
    strcpy(statements[1],"b=20-a/2");
    strcpy(statements[2],"c=b*(30/a+2)-a");
    strcpy(statements[3],"d=10+c");
    char resultant[100];
    for(int i=0;i<statement_length;i++){
        strcpy(resultant,"");
        char lhs = statements[i][0];
        map[top].lhs = lhs;

        int j=2,k=2;

        while(k<=strlen(statements[i])){
            if(is_delimiter(statements[i][k]) || k== strlen(statements[i])){
                char *temp = find_from_map(split(statements[i],j,k));


                if(k< strlen(statements[i]))
                    sprintf(resultant,"%s%s%c",resultant,temp ,statements[i][k]);
                else{
                    sprintf(resultant,"%s%s",resultant,temp);
                }
                j=k+1;
            }
            k++;
        }
        strcpy(map[top].value,resultant);
        top++;
    }
    for(int i=0;i<top;i++){
        printf("\n %c = %s",map[i].lhs,map[i].value);
    }
    printf("\n");

}