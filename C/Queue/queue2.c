#include <stdio.h>
#include <stdlib.h>
// #include "queue.h"


//queue.h
typedef struct queue_t {
	short *start;
	int capacity;
	short *eq;
	short *dq;
} queue_t;

int q_init(queue_t *q, int capacity) {
	if (capacity == 0) { 
		return -1;
	}
	if (q == 0) {
		return -2;
	}

	q->start = (short*)malloc(capacity * sizeof(short));
	q->eq = q->start;
	q->dq = q->start;
	q->capacity = capacity;

	printf(" q->start: %p\n", q->start);
}

int enqueue(queue_t *q, short element) {
	if (q->eq == (q->start + q->capacity)) {
		printf("capacity full\n");
		return -1;
	}
	*(q->eq) = element;
	printf("added %p - %d\n", q->eq, *(q->eq));
	q->eq++;
	return 0;
}

int dequeue (queue_t *q, short *element) { // passing ptr to element, therefore doesn't need return
	if (q->dq == q->eq) { 
		printf("queue is empty.\n");
	}
	*element = *(q->dq);
	printf("dequeued: %p -  %d\n",q->dq, *(q->dq));
	q->dq++;
}

void display (queue_t *q) {
	// create a temporary pointer to hold the current position of q->dq
	// so we can increment this ptr and not affect the actual q->dq
	short *temp = q->dq;

	while (temp != q->eq) {
		printf("address: %p - %d\n", temp, *temp);
		temp++;
	}


}
// We cannot use q->dq directly as the incrementation will mess up the pointer position of dq 
void display2 (queue_t *q) {
	printf("called - %p", q->dq);
	while (q->dq != q->eq) {
		printf("address: %p - %d\n", q->dq, *q->dq);
		q->dq++;
	}


}


int main() {
	queue_t m_queue;
	short element;
	q_init(&m_queue, 5);
	enqueue (&m_queue, 31);
	enqueue (&m_queue, 45);
	enqueue (&m_queue, 58);
	enqueue (&m_queue, 66);
	display(&m_queue);
	dequeue (&m_queue, &element);
	display(&m_queue);

	return 0;
}