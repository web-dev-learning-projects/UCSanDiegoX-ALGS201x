// solver.c
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void q_push(int *queue, int *right, int *size, int capacity, int val){
    if(*size == capacity) return;
    queue[*right] = val;
    *right = (*right+1)%capacity;
    (*size)++;
}

int q_pop(int *queue, int *left, int *size, int capacity){
    if(*size == 0) return -1;
    int val = queue[*left];
    *left = (*left+1)%capacity;
    (*size)--;
    return val;
}

int q_peek(int *queue, int left, int size){
    if(size==0) return -1;
    return queue[left];
}

int q_peek_back(int *queue, int right, int size, int capacity){
    if(size==0) return -1;
    int idx  = (right-1)%capacity;
    return queue[idx];
}
int *network_packet_sim(int buffer_size, int packet_count, int **packets, int *result_size) {
    int *res = malloc(sizeof(int) * packet_count);
    for (int i = 0; i < packet_count; i++)
        res[i] = -1;

    // Queue holds finish times
    int *queue = malloc(sizeof(int) * buffer_size);
    int left = 0, right = 0, size = 0;

    for (int i = 0; i < packet_count; i++) {
        int arrival = packets[i][0];
        int duration = packets[i][1];

        // 1. Remove all finished packets
        while (size > 0 && queue[left] <= arrival) {
            left = (left + 1) % buffer_size;
            size--;
        }

        // 2. Drop if full
        if (size == buffer_size) {
            res[i] = -1;
            continue;
        }

        // 3. Compute start time
        int start = arrival;
        if (size > 0) {
            int last_idx = (right - 1 + buffer_size) % buffer_size;
            int last_finish = queue[last_idx];
            if (last_finish > arrival)
                start = last_finish;
        }

        res[i] = start;

        // 4. Push finish time
        queue[right] = start + duration;
        right = (right + 1) % buffer_size;
        size++;
    }

    free(queue);
    *result_size = packet_count;
    return res;
}