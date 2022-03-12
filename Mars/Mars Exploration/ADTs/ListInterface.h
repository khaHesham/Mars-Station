#pragma once
template<class type>
class ListInterface
{
public:
	virtual bool isEmpty()const = 0;
	virtual int getLength() const = 0;
	virtual bool insert(int position, type entry) = 0;
	virtual bool remove(int position) = 0;
	virtual type getEntry(int position) = 0;
	//virtual type replace(int position, type entry) = 0;
	virtual void clear() = 0;
};