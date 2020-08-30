#include <stdio.h>
#include <stdlib.h>
#include "state.h"
#include "stack.h"

int main(){
    state *s;
    int e;
    s = state_new();
    e = state_set(s, 5);
    printf("e = %d\n", e);
    return 0;
}
