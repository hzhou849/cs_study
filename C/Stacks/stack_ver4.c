#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct stack_t 
{
	short* start;
	short* top;
	int capacity;

}stack_t;

int stack_init (stack_t *s, int capacity) 
{
	if (capacity == 0){
		return -1;
	}
	if (s == 0) {
		return -1;
	}

	s->start = (short*)malloc(sizeof(short) * capacity);
	s->top = s->start;
	s->capacity = capacity;

	return 0;
}

int push(stack_t *s, int element)
{
	//input validation
	//if *s == 0; return -1
	//if element < 0; return -1

	if (s->top < (s->start + s->capacity) ) {
		*(s->top) = element;
		s->top++;	
		return 0;
	} else {
		printf("size exceeded\n");
		return -1;
	}

}

int pop (stack_t *s, int *pop_value) {
	if (s->top != s->start) {
		s->top--; // go back a element to pop
		*pop_value = *(s->top);
		return 0;
	} else {
		return -1;
	}
}

void dump_s(stack_t *s){
	short* temp = s->start;
	
	while (temp < (s->start + s->capacity)){
		printf("address: %p  value: %d\n", temp, *temp);
		temp++;
	}
}


int main() 
{
	int last_popped = 0;
	stack_t s;
	stack_init(&s, 5);

	push(&s, 31);
	push(&s, 42);
	push(&s, 57);
	pop(&s, &last_popped);
	push(&s, 66);
	push(&s, 78);
	push(&s, 83);
	push(&s, 95);
	dump_s(&s);


	
	
	// printf("last_popped: %d\n", last_popped);

	return 0;
}