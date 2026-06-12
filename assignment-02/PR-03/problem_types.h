#ifndef PROBLEM_TYPES_H
#define PROBLEM_TYPES_H

typedef struct{
    int table_count;
    int queries_count;
    int *tables;
    int **merge_queries;
} Input;

typedef struct{
    int query_count; // total query_count
    int *max_table_size; // maximum size of all tables
} Output;

#endif