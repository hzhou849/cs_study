#pragma once

typedef struct LinkedListNode
{
	LinkedListNode* next;
	short value;
} LinkedListNode;

typedef struct LinkedList
{
	LinkedListNode* head;
} LinkedList;

void LinkedListAdd(LinkedList* list, short value);
void LinkedListRemove(LinkedList* list, short value);
void LinkedListClear(LinkedList* list);
void LinkedListDestroy(LinkedList* list);