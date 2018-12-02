#include <stdio.h>
#include <stdlib.h>

typedef struct q_td {
    short * start;
    int capacity;
    short *eq;
    short *dq;
} q_td;

/*initialize the queue*/
int q_init (q_td *q, int capacity) {
    if (q == 0) {
        return -1;
    }
    if (capacity == 0) {
        return -2;
    }

    /*allocate memory */
    q->start = (short*)malloc(capacity * sizeof(short));
    *(q->start) = 31;

    printf("q->start: %p | %p\n", q->start, &q->start);
    printf("q->start[value]: %d \n",  *(q->start));

    return 0;
}

int main(){
    q_td q1;
    q_init(&q1, 5);
}