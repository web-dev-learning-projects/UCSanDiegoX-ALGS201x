// solver.c
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int parentIndex(int idx){
    return (idx-1)/2;
}

int leftChild(int idx){
    return (idx*2)+1;
}

int rightChild(int idx){
    return (idx*2)+2;
}

void swap(void *a, void *b, const size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

void shiftdown(int **nums, int idx, int size, int (*comp)(const void *a, const void *b)){
    int minIdx = idx;
    int l_idx = leftChild(idx);
    if (l_idx < size && comp(nums[l_idx], nums[minIdx]))
        minIdx = l_idx;
    int r_idx = rightChild(idx);
    if (r_idx < size && comp(nums[r_idx], nums[minIdx]))
        minIdx = r_idx;
    if( idx != minIdx){
        swap(&nums[idx], &nums[minIdx], sizeof(nums[idx]));
        shiftdown(nums, minIdx, size, comp);
    }
}

void updateValue(int **nums, int idx, int size, int val, int (*comp)(const void *a, const void *b)){
    nums[idx][1] = val;
    shiftdown(nums, idx, size, comp); 
}

int comp(const void *a, const void *b){
    const int *x = (int *)a;
    const int *y = (int *)b;
    if(x[1] < y[1]) return 1;
    else if(x[1] == y[1] && x[0] < y[0]) return 1;
    return 0;
}

int **parallelProcessing(int thread_count, int job_count, int *jobs, int *resultSize) {
    *resultSize = 0;
    int **thread_pool = (int **)malloc(sizeof(int *)*thread_count);
    for(int i=0; i<thread_count; i++) thread_pool[i] = (int *)malloc(sizeof(int)*2);
    for(int i=0; i<thread_count; i++){
        thread_pool[i][0] = i;
        thread_pool[i][1] = 0;
    }
    int **res = (int **)malloc(sizeof(int *)*job_count);
    for(int i=0; i<job_count; i++) res[i] = (int *)malloc(sizeof(int)*2);
    
    for(int i=0; i<job_count; i++){
        int curr_thread = thread_pool[0][0];
        int curr_time = thread_pool[0][1];
        res[i][0] = curr_thread;
        res[i][1] = curr_time;
        updateValue(thread_pool, 0, thread_count, curr_time+jobs[i], comp);
    }
    *resultSize = job_count;
    return res;
}