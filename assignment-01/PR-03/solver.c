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

int *network_packet_sim(int buffer_size, int packet_count, int **packets, int *result_size) {
    int *res = malloc(sizeof(int)*packet_count);
    for(int i=0; i<packet_count; i++) res[i] = -1;
    int *queue = (int *)malloc(sizeof(int)*buffer_size);
    int queue_size = 0, q_left_idx=0, q_right_idx=0;
    int curr_idx = 0;
    int curr_time = 0;
    for(; curr_idx < packet_count; curr_idx++){
        if(curr_time <= packets[curr_idx][0]) q_push(queue, &q_right_idx, &queue_size, buffer_size, curr_idx);
        int pop_idx = q_pop(queue, &q_left_idx, &queue_size, buffer_size);
        if(pop_idx == -1) continue;
        res[pop_idx] = fmax(curr_time, packets[pop_idx][0]);
        curr_time += packets[pop_idx][1];
    }
   
    *result_size = packet_count;
    return res;
}