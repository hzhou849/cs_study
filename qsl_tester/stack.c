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
	if (s->top == s->start + s->capacity) {
		return -1;
	}
	*(s->top) = element;
	printf("pushed: %d\n", *(s->top));
	s->top ++; 			//increment to pointer to next heap allocation

	return 0;
}
int stack_pop (stack_t *s, short *pe) {
	if (s->top == s->start) {
		printf("stack empty");
		return -1;
	}
	s->top --;
	*pe = *(s->top);
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
	short pe;

	stack_init(&s, 5);
	stack_push(&s, 31);
	stack_push(&s, 44);
	stack_push(&s, 44);
	stack_push(&s, 3);	
	// stack_pop(&s,&pe);
	print_stack(&s);
}



