#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Print input and output
void print_input(const Input *input){
    printf("Number of operations: %d\n", input->operation_count);
    printf("Operations:\n");
    for (int i = 0; i < input->operation_count; i++)
        printf("%s\n", input->operations[i]);
    printf("\n");
}

void print_output(const Output *output){
    printf("Result Size: %d\n", output->size);
    printf("Results: \n");
    for (int i = 0; i < output->size; i++)
        printf("%s\n", output->find_results[i]);
}

// parse, solve, free resources
void parse_input(FILE *input_file_ptr, Input *input){
    char *input_line = NULL;
    size_t len = 0;
    
    if (getline(&input_line, &len, input_file_ptr) == -1)
    {
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
    
    sscanf(input_line, "%d", &input->operation_count);
    input->operations = (char **)malloc(sizeof(char *)*input->operation_count);
    input_line = NULL;
    for(int i=0; i<input->operation_count; i++){
        if (getline(&input_line, &len, input_file_ptr) == -1) {
            log_with_color(RED, "ERROR: Could not read operation\n");
            free(input_line);
            exit(-1);
        }
        input_line[strcspn(input_line, "\r\n")] = '\0';

        input->operations[i] = strdup(input_line);
    }
    free(input_line);
}

char **split_string_by_space(char *string){
    char **strList = (char **)malloc(sizeof(char *)*4);
    int i=0;
    char *copy = strdup(string);
    char *token;
    token = strtok(copy, " ");
    while(token != NULL && i<3){
        strList[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    strList[i] = NULL;
    return strList;
}

void solve(const Input *input, Output *output){
    Contacts *table = initTable();
    output->find_results = (char **)malloc(sizeof(char *)*input->operation_count);
    int j=0;
    for(int i=0; i<input->operation_count; i++){
        char **operation_parsed = split_string_by_space(input->operations[i]);
        if(strcmp(operation_parsed[0], "add") == 0){
            int number = atoi(operation_parsed[1]);
            char *name = operation_parsed[2];
            addContact(table, number, name);
        }
        else if(strcmp(operation_parsed[0], "del") == 0){
            int number = atoi(operation_parsed[1]);
            delContact(table, number);
        }
        else if(strcmp(operation_parsed[0], "find") == 0){
            int number = atoi(operation_parsed[1]);
            output->find_results[j++] = strdup(findContact(table, number));
        }else{
            log_with_color(RED, "Error: Invalid operation");
            exit(1);
        }
    }
    output->size = j;
}

// resrouce allocate/deallocate
void free_input(Input *input){
    for(int i=0; i<input->operation_count; i++)
        free(input->operations[i]);
    free(input->operations);
    free(input);
}

void free_output(Output *output){
    for(int i=0; i<output->size; i++){
        free(output->find_results[i]);
    }
    free(output->find_results);
    free(output);
}

Input *create_input(void){
    Input *input = (Input *)malloc(sizeof(Input));
    return input;
}

Output *create_output(void){
    Output *output = (Output *)malloc(sizeof(Output));
    return output;
}

// judge code parse output and compare
void parse_expected_output(FILE *output_file_ptr, Output *expected_output) {
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, output_file_ptr) == -1) {
        fprintf(stderr, "ERROR: Expected data but reached end of output file prematurely.\n");
        expected_output->size = 0;
        expected_output->find_results = NULL;
        free(line);
        return;
    }
    
    sscanf(line, "%d", &expected_output->size);
    expected_output->find_results = (char **)malloc(sizeof(char *)*expected_output->size);
    for(int i=0; i<expected_output->size; i++){
        line = NULL;
        if(getline(&line, &len, output_file_ptr) == -1){
            fprintf(stderr, "ERROR: Could not parse the output file properly.\n");
            exit(-1);
        }
        line[strcspn(line, "\r\n")] = '\0';
        expected_output->find_results[i] = strdup(line);
    }
    free(line);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    if(output_compute->size != output_expected->size) return 0;
    for(int i=0; i<output_expected->size; i++){
        if(strcmp(output_compute->find_results[i], output_expected->find_results[i]) != 0)
            return 0;
    }
    return 1;
}
