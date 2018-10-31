#include <stdio.h>
#include <stdlib.h>

typedef struct queue_td {
	short * start;
	int capacity;
	short *eq;
	short *dq;
} queue_td;

/* Initialize the queue */
int queue_init(queue_td * q, int capacity) {
	if (q == 0) {
		return -1;
	}

	if (capacity <= 0 ) {
		return -2;
	}

	// allocate memory in heap
	//*q.start??
	q->start = (short*)malloc(capacity * sizeof(short));
	if (q->start == 0) {
		return -3;
	}

	q->eq = q->start;
	q->dq = q->start;
	q->capacity = capacity;
}

int enqueue (queue_td *q, short element) {
	// printf("dq occupying start position: %p. dq address: %p\n\n\n", q->start, q->dq );
	// int *max_address = q->start + q->capacity * sizeof(short);
	// int *temp_address = q->start +1; 
	if (q == 0) {
		return -1;
	}
	// if eq position equals the start+capacity (last address)
	// and dq is blocking the start position preventing a wrap, exit.
	if (q->eq == q->start+q ->capacity  && q->dq == q->start) {
		// printf("q-eq: %p | q_max: %p\n", q->eq, (q->start + q->capacity * sizeof(short)));
		printf("dq occupying start position: %p. dq address: %p\n\n\n", q->start, q->dq );
		return -2;
	}
	// if eq is in the end position and dq is not in the start position
	// set eq to wrap back at start.
	if ((q->eq == q->start + q->capacity) && (q->dq != q->start)) {	
		printf("*******eq Wrapped\n");
		q->eq = q->start;
	}

	//if eq is not equal to dq, then safe to write element

	*(q->eq) = element;
	printf("element printed: %d \n", element );

	// printf("\nq->eq: %p | %p\n",q->eq, q->eq );
	// printf("q-eq: %p | q_max: %p\n", q->eq, (q->start + q->capacity ));
	// printf("*(q->eq): %d | %p\n\n",*(q->eq), (q->eq) );
	
	// increment address
	q->eq++;
	
	return 0;
}

int dequeue (queue_td *q, short * element) {
	// printf("Current dq position: %p\n", q->dq);
	if (q == 0) {
		return -1;
	}
	if (element == 0) {
		return -2;
	}
	//if eq == dq that means nothing to dequeue
	if (q->dq == q->eq) {
		printf("****dequeue limit reached: %p\n", q->dq);
		return -3;
	}

	*element = *(q->dq);
	printf("Dequeued: %d\n", *element);
	q->dq ++ ; // increment dq
	printf("new Dq position: %p\n", q->dq);
	return 0;
}

void print_queue(queue_td *q) {
	
	short* temp_address = q->start;
	short *max_address = q->start + q->capacity * sizeof(short);

	printf("max_address: %p\n", max_address);

	for (int i=0; i < q->capacity; i++){
		printf("[%d][%p]:  value: %d; q->eq: %p; q-dq: %p\n", i,temp_address,  *temp_address, q->eq, q->dq);
		
		temp_address ++;
	}
}

int main() {
	queue_td q;
	short element;

	queue_init(&q, 5);
	
	enqueue(&q, 1);
	enqueue(&q, 2);
	dequeue(&q, &element);
	dequeue(&q, &element);
	dequeue(&q, &element);
	dequeue(&q, &element);
	dequeue(&q, &element);
	dequeue(&q, &element);

	enqueue(&q, 3);
	enqueue(&q, 4);
	enqueue(&q, 5);
	enqueue(&q, 6);
	enqueue(&q, 7);
	enqueue(&q, 8);
	print_queue(&q);


}
