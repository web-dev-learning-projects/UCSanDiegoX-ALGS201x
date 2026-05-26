#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Print input and output
void print_input(const Input *input){
    printf("Number of threads: %d\n", input->thread_count);
    printf("Number of jobs: %d\n", input->job_count);
    printf("Jobs(processing time): \n");
    for (int i = 0; i < input->job_count; i++)
        printf("%d ", input->jobs[i]);
    printf("\n");
}

void print_output(const Output *output){
    printf("Total jobs: %d\n", output->job_count);
    printf("(Thread, Pickup Time): \n");
    for (int i = 0; i < output->job_count; i++)
        printf("(%d %d), ", output->jobs[i][0], output->jobs[i][1]);
    printf("\n");
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
    
    sscanf(input_line, "%d %d", &input->thread_count, &input->job_count);
    input->jobs = (int *)malloc(sizeof(int)*input->job_count);
    if (getline(&input_line, &len, input_file_ptr) == -1) {
        log_with_color(RED, "ERROR: Could not read array elements\n");
        free(input_line);
        exit(-1);
    }
    char *ptr = input_line;
    int num, bytes_read, j=0;
    while(sscanf(ptr, "%d%n", &num, &bytes_read) == 1){
        input->jobs[j] = num;
        j++;
        ptr += bytes_read;
    }
    free(input_line);
}

void solve(const Input *input, Output *output){
    output->jobs = parallelProcessing(
        input->thread_count,
        input->job_count,
        input->jobs,
        &output->job_count);
}

// resrouce allocate/deallocate
void free_input(Input *input){
    free(input->jobs);
    free(input);
}

void free_output(Output *output){
    for(int i=0; i<output->job_count; i++){
        free(output->jobs[i]);
    }
    free(output->jobs);
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
        expected_output->job_count = 0;
        expected_output->jobs = NULL;
        free(line);
        return;
    }
    
    sscanf(line, "%d", &expected_output->job_count);
    expected_output->jobs = (int **)malloc(sizeof(int *)*expected_output->job_count);
    for(int i=0; i<expected_output->job_count; i++){
        line = NULL;
        if(getline(&line, &len, output_file_ptr) == -1){
            fprintf(stderr, "ERROR: Could not parse the output file properly.\n");
            exit(-1);
        }
        expected_output->jobs[i] = (int *)malloc(sizeof(int)*2);
        sscanf(line, "%d %d", &expected_output->jobs[i][0], &expected_output->jobs[i][1]);
    }
    free(line);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    if(output_compute->job_count != output_expected->job_count) return 0;
    for(int i=0; i<output_expected->job_count; i++){
        if(output_compute->jobs[i][0] != output_expected->jobs[i][0] || output_compute->jobs[i][1] != output_expected->jobs[i][1])
            return 0;
    }
    return 1;
}
