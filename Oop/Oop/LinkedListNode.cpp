#include "LinkedListNode.hpp"

LinkedListNode::LinkedListNode(short value)
{
	this->value = value;
	this->next = 0;
}

short LinkedListNode::GetValue()
{
	return this->value;
}

LinkedListNode* LinkedListNode::GetNext()
{
	return this->next;
}

void LinkedListNode::SetNext(LinkedListNode* next)
{
	this->next = next;
}