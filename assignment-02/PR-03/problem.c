#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Print input and output
void print_input(const Input *input){
    printf("Number of tables: %d\n", input->table_count);
    printf("Number of queries: %d\n", input->queries_count);
    printf("Tables row count: ");
    for (int i = 0; i < input->table_count; i++)
        printf("%d ", input->tables[i]);
    
    printf("\nMerge queries:\n");
    for (int i = 0; i < input->queries_count; i++)
        printf("%d %d\n", input->merge_queries[i][0], input->merge_queries[i][1]);
    printf("\n");
}

void print_output(const Output *output){
    printf("Total queries: %d\n", output->query_count);
    printf("Maximum table size: ");
    for (int i = 0; i < output->query_count; i++)
        printf("%d ", output->max_table_size[i]);
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
    
    sscanf(input_line, "%d %d", &input->table_count, &input->queries_count);
    input->tables = (int *)malloc(sizeof(int)*input->table_count);
    if (getline(&input_line, &len, input_file_ptr) == -1) {
        log_with_color(RED, "ERROR: Could not read array elements\n");
        free(input_line);
        exit(-1);
    }
    char *ptr = input_line;
    int num, bytes_read, j=0;
    while(sscanf(ptr, "%d%n", &num, &bytes_read) == 1){
        input->tables[j] = num;
        j++;
        ptr += bytes_read;
    }
    
    input->merge_queries = (int **)malloc(sizeof(int *)*input->queries_count);
    for(int i=0; i<input->queries_count; i++){
        input_line = NULL;
        if(getline(&input_line, &len, input_file_ptr) == -1){
            fprintf(stderr, "ERROR: Could not parse the output file properly.\n");
            exit(-1);
        }
        input->merge_queries[i] = (int *)malloc(sizeof(int)*2);
        sscanf(input_line, "%d %d", &input->merge_queries[i][0], &input->merge_queries[i][1]);
    }

    free(input_line);
}

void solve(const Input *input, Output *output){
    output->max_table_size = mergeTableQueries(
        input->table_count,
        input->queries_count,
        input->tables,
        input->merge_queries,
        &output->query_count);
}

// resrouce allocate/deallocate
void free_input(Input *input){
    free(input->tables);
    for(int i=0; i<input->queries_count; i++)
        free(input->merge_queries[i]);
    free(input);
}

void free_output(Output *output){
    free(output->max_table_size);
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
        expected_output->query_count = 0;
        expected_output->max_table_size = NULL;
        free(line);
        return;
    }
    
    sscanf(line, "%d", &expected_output->query_count);
    expected_output->max_table_size = (int *)malloc(sizeof(int)*expected_output->query_count);
    for(int i=0; i<expected_output->query_count; i++){
        line = NULL;
        if(getline(&line, &len, output_file_ptr) == -1){
            fprintf(stderr, "ERROR: Could not parse the output file properly.\n");
            exit(-1);
        }
        sscanf(line, "%d", &expected_output->max_table_size[i]);
    }
    free(line);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    if(output_compute->query_count != output_expected->query_count) return 0;
    for(int i=0; i<output_expected->query_count; i++){
        if(output_compute->max_table_size[i] != output_expected->max_table_size[i])
            return 0;
    }
    return 1;
}
