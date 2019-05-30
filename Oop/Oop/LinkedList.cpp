#include "LinkedList.hpp"
#include "LinkedListNode.hpp"

LinkedList::LinkedList(bool b)
{
	this->head = 0;
}

void LinkedList::Add(short value)
{
	if (this->head == 0)
	{
		this->head = new LinkedListNode(value);
	}
	else
	{
		LinkedListNode* n = this->head;
		while (n->GetNext() != 0)
		{
			n = n->GetNext();
		}

		LinkedListNode* newNode = new LinkedListNode(value);
		n->SetNext(newNode);
	}
}

bool LinkedList::Contains(short value)
{
	LinkedListNode* n = this->head;

	while (n != 0)
	{
		if (n->GetValue() == value)
		{
			return true;
		}
		n = n->GetNext();
	}

	return false;
}

void LinkedList::Remove(short value)
{
	LinkedListNode* n = this->head;
	if (n->GetValue() == value)
	{
		this->head = n->GetNext();
		delete n;
	}

	LinkedListNode* next = n->GetNext();
	while (next != 0)
	{
		if (next->GetValue() == value)
		{
			n->SetNext(next->GetNext());
			delete next;
		}
	}
}

void LinkedList::Clear()
{
	LinkedListNode* n = this->head;
	while (n != 0)
	{
		LinkedListNode* next = n->GetNext();
		delete n;
		n = next;
	}
	this->head = 0;
}

LinkedList::~LinkedList()
{
	Clear();
}