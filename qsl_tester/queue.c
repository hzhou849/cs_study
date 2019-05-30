#include <stdio.h>
#include <stdlib.h>


typedef struct queue_t {
	short *start;
	short *eq;
	short *dq;
	int capacity
} queue_td;


int queue_init (queue_td *q, int capacity) {
	if (q == 0) {
		return -1;
	}
	if (capacity == 0) {
		return -2;
	}

	q->start = (short*)malloc(capacity * sizeof(short));
	q->eq = q->start;
	q->dq = q->start;
	q->capacity = capacity;

	return 0;
}

int enqueue (queue_td *q, int data){
	if (q->eq > q->start + q->capacity) {
		return -1; // queue is full
	}

	*(q->eq) = data;
	printf("\nq->eq: %p | %p\n",&q->eq, q->eq );
	printf("*(q->eq): %d | %p\n",*(q->eq), (q->eq) );
	q->eq++; //increment pointer
	return 0;
}

int dequeue (queue_td *q, short *data) {
	if (q->dq  == q->eq) {		// nothing to dequeue
		printf("queue empty");
	}

	*data = *(q->dq);
	q->dq ++; //increment pointer in heap
}


int main(){
	queue_td q;
	int data;

	queue_init(&q, 5);
	enqueue (&q, 31);
	enqueue (&q, 45);
	dequeue (&q, &data);
	printf("element: %d\n", data);
}