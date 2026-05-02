#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#include <stdio.h>

// opaque type
typedef struct Input Input;
typedef struct Output Output;

// resources lifecycle
Input *create_input(void);
Output *create_output(void);
void free_input(Input *);
void free_output(Output *);

// Problem API
void parse_input(FILE *, Input *);
void solve(const Input *, Output *);
void print_input(const Input *);
void print_output(const Output *);

// judging hooks
void parse_expected_output(FILE *, Output *);
int compare_output(const Output *, const Output *);

#endif