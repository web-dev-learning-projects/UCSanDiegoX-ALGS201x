#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Print input and output
void print_input(const Input *input){
    printf("Number of Element: %d\n", input->size);
    printf("Array:\n");
    for (int i = 0; i < input->size; i++)
        printf("%d ", input->nums[i]);
    printf("\n");
}

void print_output(const Output *output){
    printf("Total swaps: %d\n", output->swap_count);
    printf("Swaps: \n");
    for (int i = 0; i < output->swap_count; i++)
        printf("%d %d\n", output->swaps[i][0], output->swaps[i][1]);
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
    
    sscanf(input_line, "%d", &input->size);
    input->nums = (int *)malloc(sizeof(int)*input->size);
    if (getline(&input_line, &len, input_file_ptr) == -1) {
        log_with_color(RED, "ERROR: Could not read array elements\n");
        free(input_line);
        exit(-1);
    }
    char *ptr = input_line;
    int num, bytes_read, j=0;
    while(sscanf(ptr, "%d%n", &num, &bytes_read) == 1){
        input->nums[j] = num;
        j++;
        ptr += bytes_read;
    }
    free(input_line);
}

void solve(const Input *input, Output *output){
    output->swaps = buildMinHeap(
        input->nums,
        input->size,
        &output->swap_count);
}

// resrouce allocate/deallocate
void free_input(Input *input){
    free(input->nums);
    free(input);
}

void free_output(Output *output){
    for(int i=0; i<output->swap_count; i++){
        free(output->swaps[i]);
    }
    free(output->swaps);
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
    ssize_t nread;

    nread = getline(&line, &len, output_file_ptr);

    if (nread == -1) {
        fprintf(stderr, "ERROR: Expected data but reached end of output file prematurely.\n");
        expected_output->swap_count = 0;
        expected_output->swaps = NULL;
        free(line);
        return;
    }
    
    sscanf(line, "%d", &expected_output->swap_count);
    expected_output->swaps = (int **)malloc(sizeof(int *)*expected_output->swap_count);
    for(int i=0; i<expected_output->swap_count; i++){
        line = NULL;
        if(getline(&line, &len, output_file_ptr) == -1){
            fprintf(stderr, "ERROR: Could not parse the output file properly.\n");
            exit(-1);
        }
        expected_output->swaps[i] = (int *)malloc(sizeof(int)*2);
        sscanf(line, "%d %d", &expected_output->swaps[i][0], &expected_output->swaps[i][1]);
    }
    free(line);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    if(output_compute->swap_count != output_expected->swap_count) return 0;
    for(int i=0; i<output_expected->swap_count; i++){
        if(output_compute->swaps[i][0] != output_expected->swaps[i][0] || output_compute->swaps[i][1] != output_expected->swaps[i][1])
            return 0;
    }
    return 1;
}
