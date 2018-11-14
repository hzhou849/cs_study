#include <iostream>
#include "ICollection.hpp"
#include "LinkedList.hpp"
#include "Dictionary.hpp"

using namespace std;

bool CollectionContainsAllShorts(short* a, int size, ICollection* c)
{
	for (int i = 0; i < size; i++)
	{
		if (!(c->Contains(a[i])))
		{
			return false;
		}
	}

	return true;
}

void main()
{
	ICollection* i = new Dictionary();
	i->Add(2);
	i->Add(4);
	i->Add(6);

	short a[3];
	a[0] = 2;
	a[1] = 4;
	a[2] = 5;
	cout << CollectionContainsAllShorts(a, 3, i) << endl;
	delete i;
}