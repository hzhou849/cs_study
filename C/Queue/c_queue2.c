#include <stdio.h>
#include <stdlib.h>




/*c_queue.h*/
typedef struct cqueue_t {
	short* start;
	int capacity;
	short* eq;
	short* dq;
	int eq_counter; // count the enqueued items
}cqueue_t;

int q_init (cqueue_t *q, int capacity) {
	if (capacity == 0) {
		return -1;
	}
	if (q == 0) { // q == null
		return -2;
	}

	// initialize the eq_counter
	q->eq_counter = 0;

	q->capacity = capacity;

	// allocate memory in heap space
	q->start = (short*)malloc(capacity * sizeof(short));
	q->dq = q->start;
	q->eq = q->start;

	return 0;
}

int enqueue (cqueue_t *q, int element) {
	if (element == 0) {
		return -1;
	}
	if (q == 0) {
		return -3;
	}

	//Check if the queue is full
	if (q->eq_counter == q->capacity ) { 
		// printf("Queue is at Max capacity %d / %d\n", q->eq_counter, q->capacity);
		return -2;
	}

	// write the data into the queue
	*(q->eq) = element;
	// printf("address %p  enqueued: %d, eq_counter: %d,  ", (void*)q->eq, *(q->eq),q->eq_counter);
	q->eq++;

	if (q->eq >= (q->start + q->capacity)) {
		q->eq = q->start;
		// printf("eq wrapped q->eq: %p, q->start: %p ", (void*)q->eq, (void*)q->start);
	}
	// Handle the eq increments
	// wrap the eq pointer back to start once it has reached the bottom
	// if (q->eq == (q->start + q->capacity)) {
	// 	q->eq = q->start;
	// 	printf("eq wrapped q->eq: %p, q->start: %p ", (void*)q->eq, (void*)q->start);
	// } else {
	// 	q->eq++;
	// }

	q->eq_counter++;

	// printf("new address %p, eq_counter: %d\n", (void*)q->eq,q->eq_counter);
	display(q);
	return 0;
}

int dequeue (cqueue_t *q, int* element) {
	if (q == 0) {
		return -1;
	}
	if (element == 0) {
		return -2;
	}

	// dequeue the queue
	*element = *(q->dq);
	// printf("address: %p  Dequeued: %d, eq_counter: %d/ %d, ", (void*)q->dq, *(q->dq), q->eq_counter, q->capacity);

	*(q->dq) = 0;		// give it a null value to demostrate empty
	// check how many items in the queue, if s->eq_counter is 0, nothing to do.
	if (q->eq_counter == 0) {
		// printf("Queue is empty: %d / %d\n", q->eq_counter, q->capacity);
		return -3;
	
	}
	q->dq++;

	if (q->dq >= q->start + q->capacity) {
		q->dq = q->start;
	}

	// decrement the eq_counter
	q->eq_counter--;

	// printf("new address: %p  eq_counter: %d/ %d\n", (void*)q->dq, q->eq_counter, q->capacity);
	display(q);
	return 0;
}

void display(cqueue_t *q) {
	short* temp_addr= q->start;
	printf("*************\n");
	printf("\033[2J");		// clear the screen
	printf("\033[7A");
	sleep(1);
	while (temp_addr != (q->start + q->capacity)) {
		if (temp_addr == q->eq) {
			printf("eq>> ");
		}

		if (temp_addr == q->dq) {
			printf("dq>> ");
		}
		
		if (temp_addr != q->dq || temp_addr != q->eq) {
			printf("\t  ");
		}
		printf("address: %p  - %d;  eq_counter: %d\n",(void*)temp_addr, *temp_addr, q->eq_counter );
		temp_addr ++;
	}
	// printf("last address: %p\n", q->start + q->capacity);
	// printf("dq: %p\n", q->dq);
	printf("*************\n");
}

//add a snprintf to print to buffer.
void display_buffer() {

}

int main() {
	cqueue_t q;
	int element;


	q_init(&q, 5);
	enqueue(&q, 31);
	enqueue(&q, 42);
	enqueue(&q, 56);
	dequeue(&q, &element);
	enqueue(&q, 66);
	enqueue(&q, 78);
	enqueue(&q, 88);
	enqueue(&q, 91);
	dequeue(&q, &element);
	enqueue(&q, 101);
	enqueue(&q, 102);
	enqueue(&q, 103);
	enqueue(&q, 101);
	enqueue(&q, 102);
	enqueue(&q, 103);
	dequeue(&q, &element);
	dequeue(&q, &element);
	dequeue(&q, &element);
	enqueue(&q, 102);



	return 0;
}
