#include <stdio.h>
#include <stdlib.h>


typedef struct stack_t {
	short *start;
	short *top;
	int capacity;
}stack_t;

int stack_init(stack_t *s, int capacity) {
	s->capacity = capacity;
	s->start = (short*)malloc(capacity * sizeof(short));
	s->top = s->start;
	return 0;
}

int stack_push(stack_t *s, int element){
	*(s->top) = element;
	printf("pushed: %d\n", *(s->top));
	s->top ++; 			//increment to pointer to next heap allocation

	return 0;
}

void print_stack(stack_t *s) {
	// stack_t *temp;
	// temp = s;
	int *element;

	while (s->top > (s->start) ) {
		s->top --;
		printf("address: %p, data: %d, start: %p\n", (s->top),*(s->top), s->start);
		// *element = *(s->top); //optional
	}
}
int main(){
	stack_t s;
	stack_init(&s, 5);
	stack_push(&s, 31);
	stack_push(&s, 44);
	stack_push(&s, 44);
	print_stack(&s);
}



