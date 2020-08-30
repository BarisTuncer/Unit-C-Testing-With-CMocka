#include <stdlib.h>     
#include "stack.h"

struct stack { 
    int top;    /* first unused slot in data */
    int size;   /* number of slots in data */
    int *data;  /* stack contents */
};

#define INITIAL_STACK_SIZE (1)
#define STACK_SIZE_MULTIPLIER (2)

Stack 
stack_create(void)
{
    struct stack *s;

    s = malloc(sizeof(*s));
    if(s == 0) return 0;
    
    s->top = 0;
    s->size = INITIAL_STACK_SIZE;
    s->data = malloc(s->size * sizeof(*(s->data)));
    if(s->data == 0) return 0;

    /* else everything is ok */
    return s;
}

void
stack_destroy(Stack s)
{
    free(s->data);
    free(s);
}

void
stack_push(Stack s, int elem)
{
    if(s->top == s->size) {
        /* need more space */
        s->size *= STACK_SIZE_MULTIPLIER;
        s->data = realloc(s->data, s->size * sizeof(*(s->data)));
        if(s->data == 0) {
            abort();    /* we have no other way to signal failure :-( */
        }
    }
    /* now there is enough room */
    s->data[s->top++] = elem;
}

int
stack_pop(Stack s)
{
    if(stack_isempty(s)) {
        return STACK_EMPTY;
    } else {
        return s->data[--(s->top)];
    }
}

int
stack_isempty(Stack s)
{
    return s->top == 0;
}