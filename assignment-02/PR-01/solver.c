// solver.c
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int parentIndex(int idx){
    return (idx-1)/2;
}

int leftChild(int idx){
    return (idx*2)+1;
}

int rightChild(int idx){
    return (idx*2)+2;
}

void swap(int *a, int *b){
    if(a==b) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void shiftdown(int *nums, int idx, int size, int *resultSize, int **ans){
    int minIdx = idx;
    int l_idx = leftChild(idx);
    if (l_idx < size && nums[l_idx] < nums[minIdx])
        minIdx = l_idx;
    int r_idx = rightChild(idx);
    if (r_idx < size && nums[r_idx] < nums[minIdx])
        minIdx = r_idx;
    if( idx != minIdx){
        swap(&nums[idx], &nums[minIdx]);
        ans[*resultSize] = (int *)malloc(sizeof(int)*2);
        ans[*resultSize][0] = idx;
        ans[*resultSize][1] = minIdx;
        (*resultSize)++;
        shiftdown(nums, minIdx, size, resultSize, ans);
    }
}

int **buildMinHeap(int *nums, int size, int *resultSize) {
    int **ans = (int**)malloc(sizeof(int *)*(size*4));
    *resultSize = 0;
    for(int i=(size/2)-1; i>=0; i--)
        shiftdown(nums, i, size, resultSize, ans);
    return ans;
}