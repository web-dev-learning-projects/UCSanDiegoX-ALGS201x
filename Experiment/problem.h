#ifndef PROBLEM_H
#define PROBLEM_H

#include <stdio.h>
#include "problem_types.h"

void print_input(Input *input);
void print_output(Output *output);
void parse_input(FILE *input_file_ptr, Input *input);
void solve(const Input *input, Output *out);
void free_input(Input *input);
void free_output(Output *output);

#endif