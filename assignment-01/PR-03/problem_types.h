#ifndef PROBLEM_TYPES_H
#define PROBLEM_TYPES_H

typedef struct{
    int buffer_size;
    int packet_count;
    int **packets;
} Input;

typedef struct{
    int *pickup_time;
    int processed_packet_count;
} Output;

#endif