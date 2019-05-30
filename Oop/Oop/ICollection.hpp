#pragma once

class ICollection
{
public:
	virtual void Add(short s) = 0;
	virtual bool Contains(short s) = 0;
	virtual void Clear() = 0;
	virtual void Remove(short s) = 0;
};