#ifndef DATA_STRUCTURES__STACK_H
#define DATA_STRUCTURES__STACK_H

#include "linked_list.h"
#include <stdio.h>

struct _stack {
    linked_list *ll;
    int length;
};

typedef struct _stack stack;

stack stack_new();
void stack_push(stack* s, int element);
int stack_pop(stack* s);
int stack_len(stack s);

#endif //DATA_STRUCTURES__STACK_H
