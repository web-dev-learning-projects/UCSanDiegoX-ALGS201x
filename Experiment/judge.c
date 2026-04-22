#define _GNU_SOURCE
#include "judge.h"

#include <stdio.h>
#include <stdlib.h>
#include "problem_types.h"
#include "log.h"

void parse_expected_output(FILE *output_file_ptr, Output *expected_output){
    char *string = NULL;
    size_t len = 0;
    if(getline(&string, &len, output_file_ptr) == -1){
        log_with_color(RED, "ERROR: Could not parse the output file properly\n");
        exit(-1);
    }
    sscanf(string, "%d", &(expected_output->height));
    free(string);
}

int compare_output(const Output *output_compute, const Output *output_expected){
    return output_compute->height == output_expected->height;
}
