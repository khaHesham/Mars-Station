#pragma once
template <class T>
class Pair
{
	T value;
	float key;
public:
	Pair(T v, float k)
	{
		value = v;
		key = k;
	}
	Pair(){}

	int getKey() { return key; }
	T getValue() { return value; }

	bool operator<(Pair<T> p) { return key < p.key; }
	bool operator>(Pair<T> p) { return key > p.key; }
};

