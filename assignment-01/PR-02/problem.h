#ifndef PROBLEM_H
#define PROBLEM_H
#include <stdio.h>
#include "problem_types.h"

void parse_input(FILE *, Input *);
void print_input(const Input *);

void solve(const Input *, Output *);
void print_output(const Output *);

void free_input(Input *);
void free_output(Output *);
Input *create_input(void);
Output *create_output(void);

void parse_expected_output(FILE *, Output *);
int compare_output(const Output *, const Output *);

#endif