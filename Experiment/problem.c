#define _GNU_SOURCE
#include "problem.h"
#include <stdlib.h>
#include "log.h"
#include "solver.h"
#include "problem_types.h"


void print_input(Input *input){
    printf("Number of Node: %d\n", input->num_nodes);
    printf("Parents: ");
    for(int i=0; i<input->num_nodes; i++){
        printf("%d ", input->parents[i]);
    }
    printf("\n");
}

void print_output(Output *output){
    printf("Max Height: %d\n", output->height);
}

void parse_input(FILE *input_file_ptr, Input *input){
    char *input_line = NULL;
    size_t len = 0;
    
    if(getline(&input_line, &len, input_file_ptr) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }

    sscanf(input_line, "%d", &input->num_nodes);
        
    if(getline(&input_line, &len, input_file_ptr) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
    
    char *ptr = input_line;
    input->parents = malloc(sizeof(int) * input->num_nodes);
    for(int i=0; i<input->num_nodes; i++){
        input->parents[i] = (int)strtol(ptr, &ptr, 10);
    }
}

void solve(const Input *input, Output *output){
    output->height = findMaxHeight(input->parents, input->num_nodes);
}

void free_input(Input *input){
    free(input->parents);
    free(input);
}

void free_output(Output *output){
    free(output);
}
