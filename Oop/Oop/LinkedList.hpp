#include "ICollection.hpp"
#include "LinkedListNode.hpp"

class LinkedList : public ICollection
{
private:
	LinkedListNode* head;
public:
	LinkedList(bool b);
	virtual ~LinkedList();
	void Add(short s) override;
	bool Contains(short s) override;
	void Clear() override;
	void Remove(short s) override;
};