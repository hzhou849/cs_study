

#ifndef _QUEUE_H_
#define _QUEUE_H_
class Queue {
	friend class Access;
private:
	int capacity;
	short *start;
	short *eq;
	short *dq;
	int ret_value;
	int counter;
	bool qfull;
public:
	// Constructors
	Queue(int capacity);
	~Queue();

	int enqueue(int element);
	int dequeue();
	void display();
	bool has_work();

};
#endif //_QUEUE_H_
