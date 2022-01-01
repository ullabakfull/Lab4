#ifndef MYHEAD_H
#define MYHEAD_H
#include <stdio.h>

typedef struct Person
{
    char name[50];
    int count;
    int age;
}Person;
 
typedef struct Vehicle
{
    char type[50];
    char brand[50];
    char license_plate[50];
    Person owner;
}Vehicle;

extern void write_file(Vehicle *v, unsigned size);
extern void read_file(Vehicle *v, unsigned size);

#endif

