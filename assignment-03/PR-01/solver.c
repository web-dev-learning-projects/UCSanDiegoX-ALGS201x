// solver.c
#define _GNU_SOURCE
#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 1000

// typedef struct Contact{
//     int number;
//     char *name;
// } Contact;

// typedef struct Contacts{
//     int size;
//     Contact **contacts;    
// }Contacts;

int hash(int number, int buff_size){
    int val = 0;
    for(int i=0; number > 0; i++){
        val = (val*i)+(number%10);
        number /= 10;
    }
    return val%buff_size;
}

Contacts *initTable(){
    Contacts *table = (Contacts *)malloc(sizeof(Contacts));
    table->size = N;
    table->contacts = (Contact **)malloc(sizeof(Contact*)*table->size);
    for(int i = 0; i < table->size; i++)
        table->contacts[i] = NULL;
    return table;
}

void addContact(Contacts *table, int number, char *name){
    int hash_val = hash(number, N);
    // linear probing
    for(int i=0; i<N; i++){
        hash_val = (i+hash_val)%N;
        if(table->contacts[hash_val] == NULL || table->contacts[hash_val]->number == -1 || table->contacts[hash_val]->number == number){
            if(table->contacts[hash_val] == NULL)
                table->contacts[hash_val] = (Contact *)malloc(sizeof(Contact));
            table->contacts[hash_val]->number = number;
            table->contacts[hash_val]->name = strdup(name);
            return;
        }
    }
    return;
}

char *findContact(Contacts *table, int number){
    int hash_val = hash(number, N);
    // linear probing
    for(int i=0; i<N; i++){
        hash_val = (i+hash_val)%N;
        if(table->contacts[hash_val] != NULL && table->contacts[hash_val]->number == number)
            return table->contacts[hash_val]->name;
    }
    return "not found";
}

void delContact(Contacts *table, int number){
    int hash_val = hash(number, N);
    // linear probing
    for(int i=0; i<N; i++){
        hash_val = (i+hash_val)%N;
        if(table->contacts[hash_val] != NULL && table->contacts[hash_val]->number == number){
            table->contacts[hash_val]->number = -1;
            return;
        }
    }
    return;
}