// solver.c
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int find(int x, int *dsu){
    if(dsu[x] != x) {
        dsu[x] = find(dsu[x], dsu);
    }
    return dsu[x];
}

int *mergeTableQueries(int table_count, int queries_count, int *tables, int **merge_queries, int *resultSize){
    *resultSize = queries_count;
    int *max_table_size = (int *)malloc(sizeof(int)*(*resultSize));
    int *parents = (int *)malloc(sizeof(int) * table_count);
    for(int i=0; i<table_count; i++) parents[i] = i;

    int curr_max = tables[0];
    for(int i=0; i<table_count; i++){
        curr_max = curr_max > tables[i] ? curr_max : tables[i];
    }
    
    for(int i=0; i<queries_count; i++){
        int dest = merge_queries[i][1]-1;   // destination table
        int source = merge_queries[i][0]-1; // source table

        dest = find(dest, parents);
        source = find(source, parents);

        if (source != dest){
            tables[dest] += tables[source];
            tables[source] = 0;
            parents[source] = dest;
        }
        curr_max = tables[dest] > curr_max ? tables[dest] : curr_max;
        max_table_size[i] = curr_max;
    }
    free(parents);
    return max_table_size;
}