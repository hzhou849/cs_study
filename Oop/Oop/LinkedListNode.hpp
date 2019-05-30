#pragma once

class LinkedListNode
{
private:
	short value;
	LinkedListNode* next;
public:
	LinkedListNode(short value);
	short GetValue();
	LinkedListNode* GetNext();
	void SetNext(LinkedListNode* next);
};