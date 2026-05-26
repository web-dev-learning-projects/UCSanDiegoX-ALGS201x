#ifndef PROBLEM_TYPES_H
#define PROBLEM_TYPES_H

typedef struct{
    int thread_count;
    int job_count;
    int *jobs;
} Input;

typedef struct{
    int job_count; // total processed job
    int **jobs; // 2d array <thread, pickup_time>
} Output;

#endif