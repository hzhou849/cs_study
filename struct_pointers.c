#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 4

typedef struct {
	int a;		// 4 bytes
	int c;		// 4 bytes
	double b; // 8bytes
	long long int d; //8 bytes
} MYSTRUCT;

int main() {
	MYSTRUCT *p, *q;
	void *v;

	printf("size of MYSTRUCT = %d\n", sizeof(MYSTRUCT));

	p = (MYSTRUCT*)calloc(COUNT, 24);


	for (int i = 0; i < COUNT; i++) {
		p[i].a = i;
		p[i].b = 100000.0 + i;
		p[i].c = i * 20;
		p[i].d = 4000+i;
	}

	q = p;

	printf("[0] values: \na is %d\nb is %f\nc is %d\nd is %lld\n", q->a, q->b, q->c, q->d);
	printf("addresses: \n a is %p\n b is %p\n c is %p \n d is %p\n", &q[0].a, &q->b, &q->c, q->d);
	


}