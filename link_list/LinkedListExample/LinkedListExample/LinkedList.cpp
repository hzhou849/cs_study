#include "LinkedList.h"
#include <stdlib.h>

void LinkedListAdd(LinkedList * list, short value)
{
	LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	newNode->next = 0;
	newNode->value = value;

	if (list->head == 0)
	{
		list->head = newNode;
	}
	else
	{
		LinkedListNode* lastNode = list->head;
		while (lastNode->next != 0)
		{
			lastNode = lastNode->next;
		}

		lastNode->next = newNode;
	}
}

void LinkedListRemove(LinkedList* list, short value)
{
	if (list->head == 0)
	{
		return;
	}

	if (list->head->value == value)
	{
		LinkedListNode* newHeadNode = list->head->next;
		free(list->head);
		list->head = newHeadNode;
	}

	LinkedListNode* iterNode = list->head;
	while (iterNode->next != 0)
	{
		if (iterNode->next->value == value)
		{
			LinkedListNode* nodeAfter = iterNode->next->next;
			free(iterNode->next);
			iterNode->next = nodeAfter;
			return;
		}

		iterNode = iterNode->next;
	}
}

void LinkedListClear(LinkedList* list)
{
	LinkedListNode* iterNode = list->head;
	while (iterNode != 0)
	{
		LinkedListNode* next = iterNode->next;
		free(iterNode);
		iterNode = next;
	}

	list->head = 0;
}

void LinkedListDestroy(LinkedList* list)
{
	LinkedListClear(list);
}