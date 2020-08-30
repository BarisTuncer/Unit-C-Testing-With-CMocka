/*
 * This is an "opaque struct"; it discourages people from looking at
 * the inside of our structure.  The actual definiton of struct stack
 * is contained in stack.c.
 */
typedef struct stack *Stack;

/* constructor and destructor */
Stack stack_create(void);              /* returns 0 on allocation error */
void stack_destroy(Stack);

/* push a new element onto the stack */
void stack_push(Stack , int new_element);

/* return 1 if the stack is empty, 0 otherwise */
int stack_isempty(Stack);

/* remove and return top element of stack */
/* returns STACK_EMPTY if stack is empty */
#define STACK_EMPTY (-1)
int stack_pop(Stack);