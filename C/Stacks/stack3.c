
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t {
	short *start;
	int capacity;
	short *top;
}stack_t;

int stack_init (stack_t *s, int capacity) {
	if (capacity == 0) {
		return -1;
	}
	if (s == 0 ) {
		return -2;
	}

	s->capacity = capacity;
	s->start = (short*)malloc(capacity * sizeof(short));
	s->top = s->start;
	return 0;
}

int stack_push (stack_t *s, short element) {
	// if top meets last address
	if (s->top == s->start + s->capacity) {
		return -1;
	}
	*(s->top) = element;
	printf("pushed: %d\n", *(s->top));
	s->top ++; // increment pointer address.
	printf("s->start: %p\n", s->start);
}

int stack_pop (stack_t *s, short *element) {
	if (s->top == s->start) {
		return -1;
	}
	s->top --; // decrement to last entry.
	printf("Element popped: %d\n", *(s->top));
	*element = *(s->top);
	printf("s->start: %p\n", s->start);
	return 0;
}

int free_mem (stack_t *s) {
	free(s->start);
	s->top = 0;
	s->capacity= 0;
	printf("memory freed\n");
}

// METHOD 1
// void print_s(stack_t *s) {
// 	short *temp = s->start;
// 	printf("%p -> %p\n",s->start, s->top);
	
// 	// while (temp->top != (s->start+ s->capacity)) {
// 	while (temp != s->top){
// 		printf("address: %p - %d\n", temp,*temp );
// 		temp++;
// 	}
	
// }

// INvalid reference
// void print_s(stack_t *s) {
// 	stack_t *temp;
// 	temp->start = s->start;
// 	temp->top = s->top;
// 	printf("%p -> %p\n",s->start, s->top);
	
// 	// while (temp->top != (s->start+ s->capacity)) {
// 	while (temp->start != temp->top){
// 		printf("address: %p - %d\n", temp->start,*temp->start );
// 		temp->start++;
// 	}
	
// }

void print_s(stack_t *s) {
	short *temp_addr = s->start; // create a pointer to increment so it does not alter the s->start
	short data;
	while (temp_addr != s->top) {
		data = *temp_addr;
		printf("%p -> %d\n", temp_addr, data);
		temp_addr++;
	}
}



int main() {
	stack_t mstack;
	short element;
	stack_init(&mstack, 5);
	stack_push(&mstack, 31);
	stack_push(&mstack, 45);
	stack_push(&mstack, 58);
	print_s(&mstack);
	stack_pop(&mstack, &element);
	stack_push(&mstack, 99);
	print_s(&mstack);

}
