#ifndef JUDGE_H
#define JUDGE_H

#include <stdio.h>
#include "problem.h"

void parse_expected_output(FILE *ouput_file_ptr, Output *expected_output);
int compare_output(const Output *output_compute, const Output *output_expected);

#endif