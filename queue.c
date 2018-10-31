#include <stdio.h>
#include <stdlib.h>

typedef struct queue_td {
	short *start;
	int capacity;
	short *eq;
	short *dq;
} queue_td;

int queue_init(queue_td *q, int capacity) {
	if (q == 0 ) {
		return -1;
	}

	if (capacity <= 0) {
		return -2;
	}

	// Allocate memory in heap 
	q->start = (short*)malloc(capacity *sizeof(short));
	// If malloc fails
	if (q->start == 0) {
		return -3;
	}

	q->eq = q->start;
	q->dq = q->start;
	q->capacity = capacity;

	return 0;

}

int enqueue (queue_td *q, short element){
	// if q is null
	if (q == 0) {
		return -1;
	}

	//if eq address meets the end of the q struct space in heap
	if (q->eq == q->start + q->capacity*sizeof(short)){
		return -2;
	}

	// assign the element to the address q->eq is pointing to
	// q->eq holds heap address ie. 0xff00. *(q->eq) points to 0xff00
	*(q->eq) = element;
	printf("\nq->eq: %p | %p\n",&q->eq, q->eq );
	printf("*(q->eq): %d | %p\n",*(q->eq), (q->eq) );

	// increment address using pointer arithmetic.
	q->eq ++;
	return 0;
}

int dequeue (queue_td *q, short* element) {
	if (q == 0) {
		return -1;
	}
	if (element == 0) {
		return -2;
	}

	// if eq == dq that means queue is at the end
	if (q->dq == q->eq) {
		return -3;
	}

	// remember element is stored in stack, we must get its 
	// address and assign the value q->dq is pointing at.
	*element = *(q->dq);

	q->dq ++; //increment the address space in heap
	return 0;
}

int queue_destroy( queue_td * q) 
{
	if (q == 0){
		return -1;
	}

	free(q->start);
	q->dq = 0;
	q->eq = 0;
	q->start = 0;

	return 0;
}

int main() {
	queue_td q;
	short element;

	queue_init(&q,5);
	enqueue(&q, 31);
	enqueue(&q, 42);
	enqueue(&q, 88);
	enqueue(&q, 71);
	enqueue(&q, 99);
	
	dequeue(&q, &element);
	printf("element: %d\n", element);
	queue_destroy(&q)
}