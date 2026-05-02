#include <assert.h>
#include <stdio.h>
#include "../../log.h"

int main(int argc, char **argv){
    (void)argc;
    assert(*argv != NULL);
    char *program = *argv++;
    printf("Problem number: %s\n", program);
    return 0;
}