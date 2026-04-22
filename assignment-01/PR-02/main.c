#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../log.h"

typedef struct Node{
    int key;
    struct Node **children;
    int children_count;
} Node;



int solve_brute_force(Node *root){
    if(!root) return 0;
    if(root->children_count == 0) return 1;
    int height = 0;
    for(int i=0; i<root->children_count; i++){
        int child_height = solve_brute_force(root->children[i]);
        height = height > child_height?height:child_height;
    }
    return height + 1;
}

int solve_dp(int *parents_arr, int num_nodes){
    int max_height = 0;
    int *heights = (int *)calloc(num_nodes, sizeof(int));
    int loop_count = 0;
    for(int i=0; i<num_nodes; i++){
        loop_count++;
        int curr_height = 0;
        int j = i;
        while(j != -1 && heights[j] == 0){
            j = parents_arr[j];
            curr_height++;
            loop_count++;
        }

        if(j != -1) curr_height += heights[j];
        heights[i] = curr_height;
        if(heights[parents_arr[i]] == 0){
            heights[parents_arr[i]] = curr_height-1;
        }
        max_height = max_height>curr_height?max_height:curr_height;
    }
    printf("loop count: %d\n", loop_count);
    return max_height;
}


void usage_msg(const char *program_name){
    log_with_color(RED, "Usages: ");
    log_with_color(RESET, "%s <input.txt> <output.txt>\n", program_name);
    exit(-1);
}


void print_dot(Node *node, FILE *out) {
    if (node->children_count == 0) {
        fprintf(out, "    %d;\n", node->key);  // print leaf
        return;
    }

    for (int i = 0; i < node->children_count; i++) {
        fprintf(out, "    %d -> %d;\n",
                node->key,
                node->children[i]->key);
        print_dot(node->children[i], out);
    }
}

void parse_input_from_file(FILE *input_file, int num_line){
    char *input_line = NULL;
    size_t len = 0;
    
    if(getline(&input_line, &len, input_file) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
    
    int num_node=0; 
    sscanf(input_line, "%d", &num_node);
    
    
    if(getline(&input_line, &len, input_file) == -1){
        log_with_color(RED, "ERROR: Could not parse the input file properly\n");
        exit(-1);
    }
    
    int *nodes = (int *)malloc(sizeof(int)*num_node), idx=0;

    char *ptr = input_line;
    for(int i=0; i<num_node; i++){
        sscanf(ptr, "%d",  &nodes[i]);
        while(*ptr && *ptr != ' ') ptr++;
        while(*ptr == ' ') ptr++;
    }

    int *children = (int *)malloc(sizeof(int)*num_node);
    memset(children, 0, sizeof(children[0])*num_node);
    int root = 0;
    for(int i=0; i<num_node; i++){
        if(nodes[i] == -1){
            root = i;
        }else{
            children[nodes[i]]++;
        }
    }

    Node *root_node = NULL;
    Node **all_nodes = malloc(sizeof(Node *)*num_node);
    for(int i=0; i<num_node; i++){
        all_nodes[i] = (Node *)malloc(sizeof(Node));
        all_nodes[i]->key = i;
        all_nodes[i]->children = malloc(sizeof(Node *)*children[i]);
        all_nodes[i]->children_count = 0;
    }

    for(int i=0; i<num_node; i++){
        if(nodes[i] == -1){
            root_node = all_nodes[i];
        }else{
            int parent = nodes[i];
            all_nodes[parent]->children[all_nodes[parent]->children_count++] = all_nodes[i];
        }
    }

    FILE *dot = fopen("tree.dot", "w");
    fprintf(dot, "digraph G {\n");
    print_dot(root_node, dot);
    fprintf(dot, "}\n");
    fclose(dot);

    printf("\n");

    // int result = solve_brute_force(root_node);
    int result = solve_dp(nodes, num_node);
    printf("Inputs: %s", input_line);
    printf("Outputs: %d\n", result);
    for (int i = 0; i < num_node; i++) {
        free(all_nodes[i]->children);
        free(all_nodes[i]);
    }
    free(all_nodes);
    free(children);
    free(input_line);
    free(nodes);
}

void parse_output_from_file(FILE *output_file){
    char *string = NULL;
    size_t len = 0;
    if(getline(&string, &len, output_file) == -1){
        log_with_color(RED, "ERROR: Could not parse the output file properly\n");
        exit(-1);
    }
    printf("Expected outputs: %s", string);
    free(string);
}

int main(int argc, char **argv){
    (void)argc;
    assert(argc == 3);
    assert(*argv != NULL);

    const char *program = *argv++;
    int assignment_number, problem_number;
    if(sscanf(program, "./AS-%2d-PR-%2d", &assignment_number, &problem_number) != 2){
        log_with_color(RED, "ERROR: could not parse the program name correctly: %s\n", program);
        exit(-1);
    }

    log_with_color(GREEN, "Assignment Number %02d Problem Number %02d\n", assignment_number, problem_number);

    if(*argv == NULL) usage_msg(program);
    
    char *input_filepath = *argv++;
    printf("Input File: %s\n", input_filepath);
    
    FILE *input_file = fopen(input_filepath, "r");
    if (input_file == NULL)
    {
        log_with_color(RED, "ERROR: ");
        log_with_color(RESET, "Could not read input file: %s\n", input_filepath);
        exit(-1);
    }
    
    int problem_count = 0;
    fscanf(input_file, "%d\n", &problem_count);
    
    if(*argv == NULL) usage_msg(program);
    
    char *output_filepath = *argv++;
    printf("Output File: %s\n", output_filepath);
    
    FILE *output_file = fopen(output_filepath, "r");
    if (output_file == NULL)
    {
        log_with_color(RED, "ERROR: ");
        log_with_color(RESET, "Could not read output file: %s\n", output_filepath);
        exit(-1);
    }
    
    int result_count = 0;
    fscanf(output_file, "%d\n", &result_count);
    assert(problem_count==result_count);

    log_with_color(LIGHT_BLUE, "INFO: Total Test Cases: %d\n", problem_count);

    for(int i=0; i<problem_count; i++){
        printf(" Running Test: %02d\n", i+1);
        parse_input_from_file(input_file, 2);
        parse_output_from_file(output_file);
        printf("\n");
    }

    fclose(output_file);
    fclose(input_file);
    return 0;
}