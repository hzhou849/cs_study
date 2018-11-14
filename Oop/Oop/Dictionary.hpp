#pragma once
#include "ICollection.hpp"
#include <unordered_set>

class Dictionary : public ICollection
{
private:
	std::unordered_multiset<short> set;
public:
	void Add(short s) override;
	bool Contains(short s) override;
	void Clear() override;
	void Remove(short s) override;
};