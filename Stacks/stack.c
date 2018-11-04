#include <stdio.h>
#include <stdlib.h>
#include "opt_stack.h"

// moved to stack.h header file
// typedef struct stack_t {
// 	short * start;
// 	int capacity;
// 	short * top;
// }stack_t;

int stack_init (stack_t *s, int capacity) {
	if (s == 0){ //if null
		return -1;
	}
	if (capacity == 0) {
		return -2;
	}
	s->capacity = capacity;
	s->start = (short*)malloc(capacity * sizeof(short));
	s->top = s->start;
	return 0;
}

int stack_push( stack_t *s, short element) {
	// check if stack if at full capacity start address + capcity
	if (s->top == s->start + s->capacity) {
		return -1;
	}

	*(s->top) = element;
	printf("pushed: %d\n", *(s->top));
	s->top ++;
	return 0;
}
int stack_pop(stack_t *s, short *element) {
	if (s->top == s->start) {//nothing to pop
		printf("nothing to pop\n");
		return -1;
	}
	s->top --; //decrement first bc s->top is always empty.
	*element = *(s->top);
	printf("popped: *(s->top): %d \n*element: %d\n", *(s->top), *element);
	return 0;
}

//moved to header file for testing
// void kill_stack(stack_t *s){

// }

int main (int argc, char **argv) {
	short element;
	stack_t myStack;
	stack_init(&myStack, 5);
	stack_push(&myStack, 31);
	stack_push(&myStack, 42);
	stack_pop(&myStack, &element);
	printf("element: %d\n", element );
	kill_s(&myStack);
}