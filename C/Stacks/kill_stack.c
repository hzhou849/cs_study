#include <stdio.h>
#include <stdlib.h>
#include "opt_stack.h"

void kill_s (stack_t *s){
	printf("memory NOT freed. s->start: %p\n",(s->start));
	free(s->start);
	s->capacity = 0;
	s->top = 0;
	printf("memory freed. s->start: %p\n",(s->start));
}
