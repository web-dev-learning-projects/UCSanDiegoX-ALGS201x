// solver.c
#include "solver.h"
#include <stdlib.h>

int findMaxHeight(const int *parents, int num_nodes) {
    int max_height = 0;
    int *heights = (int *)calloc(num_nodes, sizeof(int));
    for(int i=0; i<num_nodes; i++){
        int curr_height = 0;
        int j = i;
        while(j != -1 && heights[j] == 0){
            j = parents[j];
            curr_height++;
        }

        if(j != -1) curr_height += heights[j];
        heights[i] = curr_height;
        if(heights[parents[i]] == 0){
            heights[parents[i]] = curr_height-1;
        }
        max_height = max_height>curr_height?max_height:curr_height;
    }
    return max_height;
}