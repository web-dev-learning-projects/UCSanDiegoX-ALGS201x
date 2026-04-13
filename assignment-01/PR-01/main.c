#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../log.h"

int main(int argc, char **argv){
    (void)argc;
    assert(*argv != NULL);

    char *program = *argv++;
    int assignment_number, problem_number;
    if(sscanf(program, "./AS-%2d-PR-%2d", &assignment_number, &problem_number) != 2){
        log_with_color(RED, "ERROR: could not parse the program name correctly: %s\n", program);
        exit(-1);
    }

    log_with_color(GREEN, "Assignment Number %02d Problem Number %02d\n", assignment_number, problem_number);

    if(*argv == NULL){
        log_with_color(RED, "Usages: ");
        log_with_color(RESET, "%s <input.txt> <test.c>\n", program);
        exit(-1);
    }

    char *input_filepath = *argv++;
    printf("Input File: %s\n", input_filepath);
    
    FILE *input_file = fopen(input_filepath, 'r');
    if (input_file == NULL)
    {
        log_with_color(RED, "ERROR: ");
        log_with_color(RESET, "Could not read input file: %s\n", input_filepath);
        exit(-1);
    }

    close(input_file);
    return 0;
}