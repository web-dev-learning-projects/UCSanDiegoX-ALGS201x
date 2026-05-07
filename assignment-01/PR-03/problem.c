#define _GNU_SOURCE
#include "problem.h"
#include "../../utils/log.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Print input and output
void print_input(const Input *input){
    printf("Buffer Size: %d, Number of packets: %d\n", input->buffer_size, input->packet_count);
    printf("Packets (Arrival Time, Processing Time): \n");
    for (int i = 0; i < input->packet_count; i++)
        printf("%d %d\n", input->packets[i][0], input->packets[i][1]);
    printf("\n");
}

void print_output(const Output *output){
    printf("Total Processed Packets: %d\n", output->processed_packet_count);
    printf("Pickup time:");
    for (int i = 0; i < output->processed_packet_count; i++)
        printf(" %d", output->pickup_time[i]);
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
    
    sscanf(input_line, "%d %d", &input->buffer_size, &input->packet_count);
    input->packets = (int **)malloc(sizeof(int *)*input->packet_count);
    for(int i=0; i<input->packet_count; i++){
        input_line = NULL;
        if (getline(&input_line, &len, input_file_ptr) == -1)
        {
            log_with_color(RED, "ERROR: Could not parse the input file properly\n");
            exit(-1);
        }
        input->packets[i] = (int *)malloc(sizeof(int)*2);
        sscanf(input_line, "%d %d", &input->packets[i][0], &input->packets[i][1]);
    }
    free(input_line);
}

void solve(const Input *input, Output *output){
    output->pickup_time = network_packet_sim(
        input->buffer_size,
        input->packet_count,
        input->packets,
        &output->processed_packet_count);
}

// resrouce allocate/deallocate
void free_input(Input *input){
    for (int i = 0; i < input->packet_count; i++)
        free(input->packets[i]);
    free(input->packets);
    free(input);
}

void free_output(Output *output){
    free(output->pickup_time);
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
        expected_output->processed_packet_count = 0;
        expected_output->pickup_time = NULL;
        free(line);
        return;
    }

    // Strip trailing newline/carriage return
    line[strcspn(line, "\r\n")] = '\0';

    // Empty line → empty output
    if (strlen(line) == 0) {
        expected_output->processed_packet_count = 0;
        expected_output->pickup_time = NULL;
        free(line);
        return;
    }

    // First pass: count tokens
    int count = 0;
    char *temp = strdup(line);
    char *tok = strtok(temp, " ");
    while (tok != NULL) {
        count++;
        tok = strtok(NULL, " ");
    }
    free(temp);

    // Allocate pickup_time array
    expected_output->processed_packet_count = count;
    expected_output->pickup_time = (int *)malloc(count * sizeof(int));
    if (expected_output->pickup_time == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed in parse_expected_output.\n");
        expected_output->processed_packet_count = 0;
        free(line);
        return;
    }

    // Second pass: parse values
    temp = strdup(line);
    tok = strtok(temp, " ");
    for (int i = 0; i < count; i++) {
        expected_output->pickup_time[i] = atoi(tok);
        tok = strtok(NULL, " ");
    }
    free(temp);
    free(line);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    if(output_compute->processed_packet_count != output_expected->processed_packet_count) return 0;
    for(int i=0; i<output_expected->processed_packet_count; i++){
        if(output_compute->pickup_time[i] != output_expected->pickup_time[i])
            return 0;
    }
    return 1;
}
