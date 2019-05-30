#include "Dictionary.hpp"
#include <unordered_set>

void Dictionary::Add(short value)
{
	this->set.insert(value);
}

void Dictionary::Clear()
{
	this->set.clear();
}

bool Dictionary::Contains(short value)
{
	return this->set.find(value) != this->set.end();
}

void Dictionary::Remove(short value)
{
	std::unordered_multiset<short>::iterator iter = this->set.find(value);
	if (iter != this->set.end())
	{
		this->set.erase(iter);
	}
}