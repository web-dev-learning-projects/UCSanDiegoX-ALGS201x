// solver.h
#ifndef SOLVER_H
#define SOLVER_H

typedef struct Contact{
    int number;
    char *name;
} Contact;

typedef struct Contacts{
    int size;
    Contact **contacts;    
}Contacts;

Contacts *initTable();
void addContact(Contacts *table, int number, char *name);
void delContact(Contacts *table, int number);
char *findContact(Contacts *table, int number);

#endif