#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../log.h"

void solve(const char *input_string, char *result){
    int len = strlen(input_string);
    char *stack = (char *)malloc(sizeof(char)*len);
    int idx = -1;
    for(int i=0; input_string[i] != '\0'; i++){
        if(input_string[i] == '(' || input_string[i] == '[' || input_string[i] == '{'){
            stack[++idx] = i;
        }
        else if(input_string[i] == ')' || input_string[i] == ']' || input_string[i] == '}'){
            if (idx < 0) {
                sprintf(result, "%d", i + 1);
                free(stack);
                return;
            }
            if((input_string[i] == ')' && input_string[stack[idx]] == '(') 
                ||(input_string[i] == '}' && input_string[stack[idx]] == '{') 
                ||(input_string[i] == ']' && input_string[stack[idx]] == '[')){
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

void usage_msg(const char *program_name){
    log_with_color(RED, "Usages: ");
    log_with_color(RESET, "%s <input.txt> <output.txt>\n", program_name);
    exit(-1);
}

void parse_input_from_file(FILE *input_file){
    char *string = NULL;
    size_t len = 0;
    if(getline(&string, &len, input_file) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
    char *result = malloc(sizeof(char)*100);
    solve(string, result);
    printf("%s", string);
    printf("%s\n", result);
    free(string);
    free(result);
}



int main(int argc, char **argv){
    (void)argc;
    assert(argc == 3);
    assert(*argv != NULL);

    const char *program = *argv++;
    int assignment_number, problem_number;
    if(sscanf(program, "./AS-%2d-PR-%2d", &assignment_number, &problem_number) != 2){
        log_with_color(RED, "ERROR: could not parse the program name correctly: %s\n", program);
        exit(-1);
    }

    log_with_color(GREEN, "Assignment Number %02d Problem Number %02d\n", assignment_number, problem_number);

    if(*argv == NULL) usage_msg(program);
    
    char *input_filepath = *argv++;
    printf("Input File: %s\n", input_filepath);
    
    FILE *input_file = fopen(input_filepath, "r");
    if (input_file == NULL)
    {
        log_with_color(RED, "ERROR: ");
        log_with_color(RESET, "Could not read input file: %s\n", input_filepath);
        exit(-1);
    }
    
    int problem_count = 0;
    fscanf(input_file, "%d\n", &problem_count);
    
    if(*argv == NULL) usage_msg(program);
    
    char *output_filepath = *argv++;
    printf("Output File: %s\n", output_filepath);
    
    FILE *output_file = fopen(output_filepath, "r");
    if (output_file == NULL)
    {
        log_with_color(RED, "ERROR: ");
        log_with_color(RESET, "Could not read output file: %s\n", output_filepath);
        exit(-1);
    }
    
    int result_count = 0;
    fscanf(output_file, "%d\n", &result_count);
    assert(problem_count==result_count);

    log_with_color(LIGHT_BLUE, "INFO: Total Test Cases: %d\n", problem_count);

    for(int i=0; i<problem_count; i++){
        parse_input_from_file(input_file);
    }

    fclose(output_file);
    fclose(input_file);
    return 0;
}