#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

void followof(char symb);

int grammar_length;
char grammar[10][100];

char is_terminal(char symb) {
    if (symb == '+' || symb == '#' || symb == '-' || symb == '(' || symb == ')' || symb == 'i' || symb == '*' ||
        symb == 'e')
        return true;
    return false;
}

void firstof(char symb, bool follow, char parent) {

    if (is_terminal(symb)) {
        if (follow) {
            if (symb != 'e')
                printf("%c, ", symb);
            else {
//                printf("\n: Parent: %c \n",parent);
                followof(parent);
            }
        } else {
            printf("%c, ", symb);
        }

    } else {

        for (int i = 0; i < grammar_length; i++) {
            //printf("\n:%c",grammar[i][0]);
            if (grammar[i][0] == symb)
                for (int j = 0; j < strlen(grammar[i]); j++) {
                    if (grammar[i][j] == '=') {
                        if (grammar[i][j + 1] != symb)
                            firstof(grammar[i][j + 1], follow, 'X');

                        //printf("\nDone");
                    }
                }
        }
        //printf("\n #Non terminal %c detected",symb);
    }
}

void followof(char symb) {
    if (symb == 'E') printf("$,");
    if (!is_terminal(symb)) {
        for (int i = 0; i < grammar_length; i++) {

            for (int j = 2; j < strlen(grammar[i]); j++) {
                if (grammar[i][j] == symb) {
                    if (j + 1 < strlen(grammar[i])) {
                        if (is_terminal(grammar[i][j + 1]))
                            printf("%c, ", grammar[i][j + 1]);
                        else {
                            // printf("\n#First of: %c\n",grammar[i][j + 1]);
                            firstof(grammar[i][j + 1], true, grammar[i][j + 1]);
                        }
                    } else {
                        followof(grammar[i][0]);

                    }
                }
            }

        }
    }
}

void get_data() {
    printf("\nProductions(Count)");
    scanf("%d", &grammar_length);
    for (int i = 0; i < grammar_length; i++) scanf(" %s", grammar[i]);



}


char *split(char *string, int i, int j) {
    char *ret = malloc(sizeof(char) * (j - i) + 1);
    int m = 0;
    for (int k = i; k < j; k++) {
        ret[m] = string[k];
        m++;
    }
    return ret;
}
void get_data3() {
    grammar_length = 8;
    strcpy(grammar[0], "E=TX");
    strcpy(grammar[1], "X=+TX");
    strcpy(grammar[2], "X=e");
    strcpy(grammar[3], "T=FY");
    strcpy(grammar[4], "Y=*FY");
    strcpy(grammar[5], "Y=e");
    strcpy(grammar[6], "F=(E)");
    strcpy(grammar[7], "F=i");

}