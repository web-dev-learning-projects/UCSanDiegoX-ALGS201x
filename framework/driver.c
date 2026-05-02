#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "framework.h"
#include "../utils/log.h"

void usage_msg(const char *program_name){
    log_with_color(RED, "Usages: ");
    log_with_color(RESET, "%s <input.txt> <output.txt>\n", program_name);
    exit(-1);
}

int main(int argc, char **argv){
    (void)argc;
    assert(argc == 3);
    assert(*argv != NULL);

    const char *program = *argv++;
    int assignment_number, problem_number;
    if(sscanf(program, "./tmp/bin/AS-%2d-PR-%2d", &assignment_number, &problem_number) != 2){
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
        printf(" Running Test: %02d\n", i+1);
        
        Input *input = create_input();
        Output *output = create_output();
        Output *output_expected = create_output();
        
        parse_input(input_file, input);
        
        printf("Inputs: \n");
        print_input(input);
        
        solve(input, output);
        
        printf("Outputs: \n");
        print_output(output);
        
        
        parse_expected_output(output_file, output_expected);
        int result = compare_output(output, output_expected);
        
        printf("Outputs Expected: \n");
        print_output(output_expected);

        if(result){
            printf("Test Passed\n");
        }else{
            printf("Test Failed\n");
        }

        // free memory
        free_input(input);
        free_output(output);
        printf("\n");
    }

    fclose(output_file);
    fclose(input_file);
    return 0;
}