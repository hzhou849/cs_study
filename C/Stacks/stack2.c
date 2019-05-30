
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t {
	short *start;
	int capacity;
	short *top;
} stack_t;

int stack_init (stack_t *s, int capacity) {
	if (capacity == 0)
		return -1;
	if (s == 0)
		return -2;

	s->capacity = capacity;
	s->start = (short*)malloc(capacity *sizeof(short));
	s->top = s->start;
	return 0;
}

int stack_push (stack_t *s, short element) {
	// check if stack is at full capacity s->top = s->start + s->capacity
	if (s->top == s->start + s->capacity) {
		return -1;
	}
	*(s->top) = element; // deref s.top and place the element in that address 
	printf("pushed: %d\n", *(s->top));
	s->top++;
	return 0;
}

int stack_pop (stack_t *s, short *element) {
	// nothing to pop
	if (s->top == s->start) {
		printf("stack is empty");
		return -1;
	}
	s->top -- ; // decrement top to last entry
	*element = *(s->top); // assign the contents of address at s->top's 
	printf("Popped: *(s->top):%d \n*element: %d\n", *(s->top), *element);
	return 0;
}


void kill_s(stack_t *s) {
	free(s->start);
	s->capacity = 0;
	s->top = 0;
	printf("memory freed.\n");
}


int main() {
	short element;
	stack_t mstack;
	stack_init(&mstack, 5);
	stack_push(&mstack, 31);
	stack_push(&mstack, 45);
	stack_pop(&mstack, &element);
	kill_s(&mstack);


}