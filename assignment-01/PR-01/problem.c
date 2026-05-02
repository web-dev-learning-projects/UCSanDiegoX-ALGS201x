#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>


// Print input and output
void print_input(const Input *input){
    printf("String: %s\n", input->string);
}

void print_output(const Output *output){
    printf("Result: %s\n", output->is_palindrome);
}


// parse, solve, free resources
void parse_input(FILE *input_file_ptr, Input *input){
    input->string = NULL;
    size_t len = 0;    
    if(getline(&input->string, &len, input_file_ptr) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
}

void solve(const Input *input, Output *output){
    output->is_palindrome = malloc(sizeof(char)*32);
    is_string_palindrome(input->string, output->is_palindrome);
}


// resrouce allocate/deallocate
void free_input(Input *input){
    free(input->string);
    free(input);
}

void free_output(Output *output){
    free(output->is_palindrome);
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
void parse_expected_output(FILE *output_file_ptr, Output *expected_output){
    size_t len = 0;
    if(getline(&(expected_output->is_palindrome), &len, output_file_ptr) == -1){
        log_with_color(RED, "ERROR: Could not parse the output file properly\n");
        exit(-1);
    }
}

int compare_output(const Output *output_compute, const Output *output_expected){
    return strcmp(output_compute->is_palindrome, output_expected->is_palindrome) == 0;
}

