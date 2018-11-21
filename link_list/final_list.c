#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode {
	struct LinkedListNode *next;
	short value;
} LinkedListNode;

typedef struct LinkedList {
	struct LinkedListNode *head;
}LinkedList;

void listhead_init(LinkedList *list) {
	list->head = 0;

}
void LinkedListAdd (LinkedList *list, short  value) {
	LinkedListNode *newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	newNode->next = 0;
	newNode->value = value;

	if (list->head == 0) {
		list->head = newNode;
	} else {
		LinkedListNode* lastNode = list->head;
		while(lastNode->next != 0){
			lastNode = lastNode->next;
		}
		lastNode->next = newNode;
	}
}

void LinkedListRemove(LinkedList *list, short value) {
	if (list->head == 0) {
		return ;
	}
	if (list->head->value == value) {
		LinkedListNode* newHeadNode = list->head->next;
		free(list->head);
		list->head = newHeadNode;
	}
}

void printList(LinkedList *list) {
	LinkedListNode* iterNode = list->head;
	while(iterNode != 0) {
		LinkedListNode *next = iterNode->next;
		printf("address %p, ->next: %p, ->value: %d\n", iterNode, iterNode->next, iterNode->value);
		iterNode = next;
	}
}

int main(){
	LinkedList list;
	list.head =0;
	LinkedListAdd (&list, 31);
	LinkedListAdd (&list, 44);
	
	printList(&list);
	return 0;
}