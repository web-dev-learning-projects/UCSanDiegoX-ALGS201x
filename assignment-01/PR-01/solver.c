// solver.c
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void is_string_palindrome(const char *str, char *result){
    int len = strlen(str);
    int *stack = (int *)malloc(sizeof(int)*len);
    int idx = -1;
    for(int i=0; str[i] != '\0'; i++){
        if(str[i] == '(' || str[i] == '[' || str[i] == '{'){
            stack[++idx] = i;
        }
        else if(str[i] == ')' || str[i] == ']' || str[i] == '}'){
            if (idx < 0) {
                sprintf(result, "%d", i + 1);
                free(stack);
                return;
            }
            if((str[i] == ')' && str[stack[idx]] == '(') 
                ||(str[i] == '}' && str[stack[idx]] == '{') 
                ||(str[i] == ']' && str[stack[idx]] == '[')){
                    idx--;
            }
            else{
                sprintf(result, "%d", i+1);
                return;
            }
        }
    }
    if(idx != -1){
        sprintf(result, "%d", stack[idx]+1);
        return;
    }
    sprintf(result, "%s", "Success");
    return;
}