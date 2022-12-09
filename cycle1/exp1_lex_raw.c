#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool LITERAL;
bool COMMENT;
bool M_COMMENT;

char *get_info(char i, char next, int *r);

char *get_info_str(char *substr);

bool is_delimeter(char ltr) {
    if (LITERAL)return false;
    if (ltr == ' ' || ltr == ';' || ltr == '+' || ltr == '=' || ltr == ',' || ltr == '(' || ltr == ')' ||
        ltr == '!')
        return true;
    else return false;
}

char *substr(char *string, int start, int end) {
    char *result = malloc(sizeof(char) * (end - start) + 2);
    int k = 0;
    for (int i = start + 1; i < end; i++) {
        result[k] = string[i];
        k++;
    }
    return result;
}

int main() {
    LITERAL = false;
    COMMENT = false;
    M_COMMENT = false;
    printf("Lexical analyser!\n");
    /* char *input = "//printf(\"%d is a\",&a)";
    char *input = "//printf(\"%d is a\",&a)";*/

    FILE *fptr = fopen("lex_raw.c", "r");
    char *input = malloc(sizeof(char) * 60);
    while (fgets(input, 60, fptr) != NULL) {
        //printf("%s\n",input);
        int length = strlen(input);
        int l = 0, r = 0;
        if (input[0] == '/' && input[1] == '*') {
            printf("\nMULTI LINE COMMENT \n");
            M_COMMENT = !M_COMMENT;
            continue;
        }
        if (input[0] == '/' && input[1] == '/') {
            printf("\nCOMMENT LINE\n");
            COMMENT = !COMMENT;
            continue;
        }

        if (input[0] == '#') {
            printf("PRE-PROCESSOR DIRECTIVES\n");
            continue;
        }
        while (r <= length && l <= r) {
            if (input[r] == '\"') {
                LITERAL = !LITERAL;
            }
            if (!is_delimeter(input[r])) r++;
            else if (is_delimeter(input[r]) && l == r) {
                if (input[r] != ' ')
                    printf("<%c,'%s'>\n", input[r], get_info(input[r], input[r + 1], &r));
                l = r;
                l++;
                r++;
            } else {

                if (r - l != 1)
                    printf("<%s,'%s'>\n", substr(input, l - 1, r), get_info_str(substr(input, l - 1, r)));
                l = r;
            }
        }
    }
    return 0;
}

char *get_info_str(char *substr) {
    if (substr[0] == '*') return "Pointer";
    if (substr[0] == '\"') {
        return "LITERAL";
    }
    if (substr[0] == '|' || substr[0] == '<' || substr[0] == '>' || substr[0] == '=' || substr[0] == '&') {
        for (int i = 0; i <= strlen(substr); i++) {
            if (!(substr[i] == '|' || substr[i] == '<' || substr[i] == '>' || substr[i] == '=' ||
                  substr[0] == '&'))
                return "ERROR";
        }
        return "Operator";
    }
    if (substr[0] == '\'') {
        return "CHARECTER";
    }
    if ((substr[0] >= 65 && substr[0] <= 90) || (substr[0] >= 97 && substr[0] <= 122)) {
        if (!strcmp(substr, "int") || !strcmp(substr, "float") || !strcmp(substr, "char") || !strcmp(substr, "for") ||
            !strcmp(substr, "return") || !strcmp(substr, "continue") || !strcmp(substr, "FILE") ||
            !strcmp(substr, "char") || !strcmp(substr, "bool") || !strcmp(substr, "if") || !strcmp(substr, "else")) {
            return "KeyWord";
        }
        for (int i = 0; i <= strlen(substr); i++) {
            if ((substr[i] >= 65 && substr[i] <= 90) || (substr[i] >= 97 && substr[i] <= 122) ||
                (substr[i] >= 48 && substr[i] <= 57)) {
                return "Identifier";
            }
        }
        return "ERROR";

    } else {
        for (int i = 0; i <= strlen(substr); i++) {

            if (!(substr[i] >= 48 && substr[i] <= 57)) return "ERROR";
        }
        return "NUMBER";

    }
}

char *get_info(char i, char next, int *r) {
    if (i == '+' || i == '-' || i == '*' || i == '/' || i == '%' || i == '=' || i == '|' || i == '&' || i == '<' ||
        i == '>') {
        if (i == '=' && next == '=') {
            r++;
            return "Equality";
        }
        if (i == '<' && next == '=') {
            r++;
            return "LE";
        }
        if (i == '>' && next == '=') {
            r++;
            return "GE";
        }
        return "Operator";
    } else
        return "Separator";
}
